/* Copyright 2011-2018 Tyler Gilbert;
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

#include <mcu/mmc.h>
#include "mmc_local.h"

//STM32H7 has built in DMA inside the MMC -- DMA is automatic
#if MCU_SDIO_PORTS > 0 && defined MMC_TypeDef

DEVFS_MCU_DRIVER_IOCTL_FUNCTION(mmc_dma, MMC_VERSION, MMC_IOC_IDENT_CHAR, I_MCU_TOTAL + I_SDIO_TOTAL, mcu_mmc_dma_getcid, mcu_mmc_dma_getcsd, mcu_mmc_dma_getstatus)

static int configure_dma(const devfs_handle_t * handle);

int mcu_mmc_dma_open(const devfs_handle_t * handle){
	//mmc_local[handle->port].o_flags = MMC_LOCAL_IS_DMA;
	return mmc_local_open(handle);
}

int mcu_mmc_dma_close(const devfs_handle_t * handle){

	DEVFS_DRIVER_DECLARE_LOCAL(mmc, MCU_SDIO_PORTS);

	if( local->ref_count == 1 ){
		//disable the DMA
		if( local->transfer_handler.read || local->transfer_handler.write ){
			return SYSFS_SET_RETURN(EBUSY);
		}

		const stm32_mmc_dma_config_t * config;
		config = handle->config;

		if( config ){
			stm32_dma_clear_handle(config->dma_config.rx.dma_number, config->dma_config.rx.stream_number);
			stm32_dma_clear_handle(config->dma_config.tx.dma_number, config->dma_config.tx.stream_number);
		}

	}

	//do the opposite of mcu_mmc_dma_open() -- ref_count is zero -- turn off interrupt
	return mmc_local_close(handle);
}

int mcu_mmc_dma_getinfo(const devfs_handle_t * handle, void * ctl){
	return mmc_local_getinfo(handle, ctl);
}


int configure_dma(const devfs_handle_t * handle){

#if MCU_SDIO_API == 0
	DEVFS_DRIVER_DECLARE_LOCAL(mmc, MCU_SDIO_PORTS);

	const stm32_mmc_dma_config_t * config = handle->config;
	if( config == 0 ){ return SYSFS_SET_RETURN(ENOSYS); }

	stm32_dma_channel_t * rx_channel = stm32_dma_setattr(&config->dma_config.rx);
	if( rx_channel == 0 ){
		return SYSFS_SET_RETURN(EIO);
	}

	stm32_dma_channel_t * tx_channel = stm32_dma_setattr(&config->dma_config.tx);
	if( tx_channel == 0 ){
		return SYSFS_SET_RETURN(EIO);
	}

	__HAL_LINKDMA((&local->hal_handle), hdmatx, tx_channel->handle);
	__HAL_LINKDMA((&local->hal_handle), hdmarx, rx_channel->handle);
#endif

	return 0;
}

int mcu_mmc_dma_setattr(const devfs_handle_t * handle, void * ctl){
	const mmc_attr_t * attr = mcu_select_attr(handle, ctl);
	if( attr == 0 ){ return SYSFS_SET_RETURN(ENOSYS); }

	u32 o_flags = attr->o_flags;
	DEVFS_DRIVER_DECLARE_LOCAL(mmc, MCU_SDIO_PORTS);

	if( o_flags & MMC_FLAG_SET_INTERFACE ){

		local->o_flags |= MMC_LOCAL_FLAG_IS_DMA;

		int result = configure_dma(handle);
		if( result < 0 ){
			return result;

		}

	}

	return mmc_local_setattr(handle, ctl);
}


int mcu_mmc_dma_setaction(const devfs_handle_t * handle, void * ctl){
	return mmc_local_setaction(handle, ctl);
}

int mcu_mmc_dma_getcid(const devfs_handle_t * handle, void * ctl){
	return mmc_local_getcid(handle, ctl);
}

int mcu_mmc_dma_getcsd(const devfs_handle_t * handle, void * ctl){
	return mmc_local_getcsd(handle, ctl);
}

int mcu_mmc_dma_getstatus(const devfs_handle_t * handle, void * ctl){
	return mmc_local_getstatus(handle, ctl);
}


int mcu_mmc_dma_write(const devfs_handle_t * handle, devfs_async_t * async){
	DEVFS_DRIVER_DECLARE_LOCAL(mmc, MCU_SDIO_PORTS);
	DEVFS_DRIVER_IS_BUSY(local->transfer_handler.write, async);

	int result;
	local->hal_handle.ErrorCode = 0;
	int loc;
	if( local->o_flags & MMC_LOCAL_FLAG_IS_BYTE_ADDRESSING ){
		loc = async->loc*512;
	} else {
		loc = async->loc;
	}

#if MCU_SDIO_API == 0
	if( local->hal_handle.hdmatx == 0 ){
		//driver unlinked the DMA object -- relink it here
		configure_dma(handle);
	}
#endif

	local->hal_handle.TxXferSize = async->nbyte; //used by the callback but not set by HAL_SD_WriteBlocks_DMA
	if( (result = HAL_MMC_WriteBlocks_DMA(&local->hal_handle, async->buf, loc, async->nbyte / BLOCKSIZE)) == HAL_OK ){
		//check the state to make sure the transfer is underway
		return 0;
	}

	local->transfer_handler.write = 0;
	mcu_debug_log_error(MCU_DEBUG_DEVICE, "W->HAL Not OK  %d, 0x%lX (%d + %d > %d?)",
							  result,
							  local->hal_handle.ErrorCode,
							  async->loc,
							  async->nbyte / BLOCKSIZE,
							  local->hal_handle.MmcCard.LogBlockNbr);
	return SYSFS_SET_RETURN(EIO);
}

int mcu_mmc_dma_read(const devfs_handle_t * handle, devfs_async_t * async){
	DEVFS_DRIVER_DECLARE_LOCAL(mmc, MCU_SDIO_PORTS);
	int hal_result;
	DEVFS_DRIVER_IS_BUSY(local->transfer_handler.read, async);

	local->hal_handle.RxXferSize = async->nbyte; //used by the callback but not set by HAL_SD_ReadBlocks_DMA
	int loc;
	if( local->o_flags & MMC_LOCAL_FLAG_IS_BYTE_ADDRESSING ){
		loc = async->loc*512;
	} else {
		loc = async->loc;
	}

#if MCU_SDIO_API == 0
	if( local->hal_handle.hdmarx == 0 ){
		//driver unlinked the DMA object -- relink it here
		configure_dma(handle);
	}
#endif

	if( (hal_result = HAL_MMC_ReadBlocks_DMA(&local->hal_handle, async->buf, loc, async->nbyte / BLOCKSIZE)) == HAL_OK ){
		return 0;
	}

	mcu_debug_log_warning(
				MCU_DEBUG_DEVICE,
				"R->HAL Not OK %d %d %d 0x%lX",
				async->loc, async->nbyte,
				hal_result,
				local->hal_handle.ErrorCode
			);

	local->transfer_handler.read = 0;
	return SYSFS_SET_RETURN(EIO);
}


#endif

