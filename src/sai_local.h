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

#ifndef sai_local_H_
#define sai_local_H_

#include <sos/dev/i2s.h>
#include "stm32_dma.h"

#if MCU_SAI_PORTS > 0

typedef struct {
	SAI_HandleTypeDef hal_handle;
	devfs_transfer_handler_t transfer_handler;
    mcu_event_handler_t special_event_handler;
	u16 o_flags;
	u8 ref_count;
	u8 size_mult;
} sai_local_t;

enum {
	SAI_LOCAL_IS_DMA = (1<<0),
	SAI_LOCAL_IS_I2S = (1<<1),
    SAI_LOCAL_IS_FULL_DUPLEX = (1<<2),
    SAI_LOCAL_IS_TX = (1<<3),
    SAI_LOCAL_IS_RX = (1<<4),
};

//each SAI block is half duplex -- two blocks (one SAI unit) can be full duplex
typedef struct {
	sai_local_t sai;
	stm32_dma_channel_t dma_channel;
} sai_dma_local_t;

extern sai_local_t sai_local[MCU_SAI_PORTS] MCU_SYS_MEM;
extern sai_dma_local_t sai_dma_local[MCU_SAI_PORTS] MCU_SYS_MEM;
extern SAI_Block_TypeDef * const sai_regs[MCU_SAI_PORTS];
extern u8 const sai_irqs[MCU_SAI_PORTS];
extern mcu_callback_t read_cb,send_cb;
int sai_local_open(sai_local_t * local, const devfs_handle_t * handle);
int sai_local_close(sai_local_t * local, const devfs_handle_t * handle);
int sai_local_setattr(sai_local_t * local, const devfs_handle_t * handle, void * ctl);
int sai_local_setaction(sai_local_t * local, const devfs_handle_t * handle, void * ctl, int interrupt_number);
int sai_local_mute(sai_local_t * local, const devfs_handle_t * handle, void * ctl);
int sai_local_unmute(sai_local_t * local, const devfs_handle_t * handle, void * ctl);

#endif


#endif /* sai_local_H_ */
