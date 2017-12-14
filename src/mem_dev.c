/* Copyright 2011-2016 Tyler Gilbert; 
 * This file is part of Stratify OS.
 *
 * Stratify OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stratify OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 */

#include <errno.h>
#include <cortexm/cortexm.h>
#include <mcu/mem.h>
#include <mcu/debug.h>
#include <mcu/core.h>
#include <mcu/wdt.h>
#include <mcu/bootloader.h>

#include "stm32_flash.h"


static int get_last_boot_page();

static int is_ram(int addr, int size);
static int get_ram_page(int addr);
static int get_ram_page_size(int page);
static int get_ram_page_addr(int page);

void mcu_mem_dev_power_on(const devfs_handle_t * handle){}
void mcu_mem_dev_power_off(const devfs_handle_t * handle){}
int mcu_mem_dev_is_powered(const devfs_handle_t * handle){
	return 1;
}

//this is used by appfs
int mcu_mem_getsyspage(){
	return 0; //system memory starts on the first page at SRAM_START
}


int mcu_mem_getinfo(const devfs_handle_t * handle, void * ctl){
	mem_info_t * info = ctl;
	info->flash_pages = (u32)&_flash_pages;
	info->flash_size = FLASH_SIZE;
	info->ram_pages = (u32)&_flash_pages;
	info->ram_size = SRAM_SIZE;
	return 0;
}
int mcu_mem_setattr(const devfs_handle_t * handle, void * ctl){
	return 0;
}

int mcu_mem_setaction(const devfs_handle_t * handle, void * ctl){
	errno = ENOTSUP;
	return -1;
}

int mcu_mem_getpageinfo(const devfs_handle_t * handle, void * ctl){
	u32 size = 0;
	int32_t addr = 0;
	mem_pageinfo_t * ctlp = ctl;


	if( ctlp->o_flags & MEM_FLAG_IS_RAM ){

		size = get_ram_page_size(ctlp->num);
		addr = get_ram_page_addr(ctlp->num);
		if ( addr < 0 ){
			return -1;
		}

	} else if( ctlp->o_flags & MEM_FLAG_IS_FLASH ){

		size = stm32_flash_get_sector_size(ctlp->num);
		addr = stm32_flash_get_sector_addr(ctlp->num);
		if ( (addr + size) > (FLASH_SIZE + FLASH_START) ){
			return -1; //this page does not exist on this part
		}

	} else if( ctlp->o_flags & MEM_FLAG_IS_QUERY ){

		//Query needs to see if addr is RAM or FLASH
		if ( is_ram(ctlp->addr, DEVICE_RAM_PAGE_SIZE) ){
			ctlp->num = get_ram_page(ctlp->addr);
			ctlp->size = get_ram_page_size(ctlp->num);
			ctlp->o_flags = MEM_FLAG_IS_RAM;
			return 0;
		} else if ( stm32_flash_is_flash(ctlp->addr, 0) ){
			ctlp->num = stm32_flash_get_sector(ctlp->addr);
			ctlp->size = stm32_flash_get_sector_size(ctlp->num);
			ctlp->o_flags = MEM_FLAG_IS_FLASH;
			return 0;
		} else {
			return -1;
		}

	} else {
		return -1;
	}



	ctlp->size = size;
	ctlp->addr = addr;
	return 0;
}



int mcu_mem_erasepage(const devfs_handle_t * handle, void * ctl){
	int err;
	int addr;
	int page;
	page = (u32)ctl;
	addr = stm32_flash_get_sector_addr(page);  //this gets the beginning of the page
	int last_boot_page = get_last_boot_page();
	int page_size;

	page_size = stm32_flash_get_sector_size(page);

	//protect the OS and the bootloader from being erased
	if( page <= last_boot_page ){
		mcu_debug_root_printf("Can't erase page (BOOT) %d in 0x%lX %d\n", page, addr, page_size);
		errno = EROFS;
		return -1;
	}

	if( stm32_flash_is_flash(addr, page_size) == 0 ){
		mcu_debug_root_printf("Can't erase page (FLASH) %d in 0x%lX %d\n", page, addr, page_size);
		errno = EROFS;
		return -1;
	}

	if( stm32_flash_is_code(addr, page_size) ){
		mcu_debug_root_printf("Can't erase page (CODE) %d in 0x%lX %d\n", page, addr, page_size);
		errno = EROFS;
		return -1;
	}


	err = stm32_flash_erase_sector(page);
	if( err < 0 ){
		errno = EIO;
	}
	return err;
}


int mcu_mem_writepage(const devfs_handle_t * handle, void * ctl){
	int err;
	int nbyte;
	mem_writepage_t * wattr = ctl;
	int last_boot_page;
	int write_page;

	nbyte = wattr->nbyte;
	if( nbyte > 256 ){
		nbyte = 256;
	}

	if ( is_ram(wattr->addr, nbyte) ){
		memcpy((void*)wattr->addr, wattr->buf, nbyte);
		return nbyte;
	}

	last_boot_page = get_last_boot_page();
	write_page = stm32_flash_get_sector(wattr->addr);

	if ( write_page <= last_boot_page ){
		mcu_debug_root_printf("Can't write to 0x%lX boot page %d %d\n", wattr->addr, write_page, last_boot_page);
		errno = EROFS;
		return -1;
	}

	if( ((wattr->addr + nbyte >= FLASH_CODE_START) && (wattr->addr <= FLASH_CODE_END)) ){
		errno = EROFS;
		return -1;
	}

	if ( wattr->addr >= (FLASH_SIZE + FLASH_START) ){
		errno = EINVAL;
		return -11;
	}

	if ( wattr->addr + nbyte > (FLASH_SIZE + FLASH_START) ){
		nbyte = FLASH_SIZE - wattr->addr; //update the bytes read to not go past the end of the disk
	}


	if ( stm32_flash_blank_check(wattr->addr,  nbyte) ){
		mcu_debug_root_printf("not blank 0x%lX\n", wattr->addr);
		errno = EROFS;
		return -1;
	}

	err = stm32_flash_write(wattr->addr, wattr->buf, nbyte);

	if( err == 0 ){
		err = nbyte;
	}
	return nbyte;
}

int mcu_mem_dev_write(const devfs_handle_t * cfg, devfs_async_t * wop){

	if ( is_ram(wop->loc, wop->nbyte) ){
		memcpy((void*)wop->loc, wop->buf, wop->nbyte);
		return wop->nbyte;
	}

	errno = EINVAL;
	return -1;
}

int mcu_mem_dev_read(const devfs_handle_t * cfg, devfs_async_t * rop){
	if ( (stm32_flash_is_flash(rop->loc, rop->nbyte) ) ||
			( is_ram(rop->loc, rop->nbyte) ) 	){
		memcpy(rop->buf, (const void*)rop->loc, rop->nbyte);
		return rop->nbyte;
	}
	errno = EINVAL;
	return -1;
}

//RAM paging
int get_ram_page(int addr){
	int ret;
	if ( (addr >= SRAM_START) && (addr < SRAM_END) ){
		ret = ((addr - SRAM_START) / DEVICE_RAM_PAGE_SIZE);
	} else {
		ret = -1;
	}
	return ret;
}

int get_ram_page_size(int page){
	return DEVICE_RAM_PAGE_SIZE;
}

int get_ram_page_addr(int page){
	if ( page < SRAM_PAGES ){
		return SRAM_START + page*DEVICE_RAM_PAGE_SIZE;
	}

	return -1;
}

int is_ram(int addr, int size){
	if ( (addr >= SRAM_START) && ((addr + size) <= SRAM_END) ){
		return 1;
	}

	return 0;
}



int get_last_boot_page(){
	bootloader_api_t api;
	mcu_core_get_bootloader_api(&api);

	if( api.code_size > 0 ){ //zero means there is no bootloader installed
		return stm32_flash_get_sector(api.code_size);
	}

	return -1;

}
