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


#include "stm32_dma.h"

#define MCU_DMA_PORTS 2
#define MCU_DMA_STREAM_COUNT 8
#define MCU_DMA_CHANNEL_COUNT 8
#define MCU_DMA0_REGS { DMA1_Stream0, DMA1_Stream1, DMA1_Stream2, DMA1_Stream3, DMA1_Stream4, DMA1_Stream5, DMA1_Stream6, DMA1_Stream7 }
#define MCU_DMA1_REGS { DMA2_Stream0, DMA2_Stream1, DMA2_Stream2, DMA2_Stream3, DMA2_Stream4, DMA2_Stream5, DMA2_Stream6, DMA2_Stream7 }


#if MCU_DMA_PORTS > 0

typedef struct {
    stm32_dma_channel_t * stream[MCU_DMA_STREAM_COUNT];
} stm32_dma_streams_t;

stm32_dma_streams_t stm32_dma_handle[MCU_DMA_PORTS];

DMA_Stream_TypeDef * const stm32_dma0_regs[MCU_DMA_STREAM_COUNT] = MCU_DMA0_REGS;
DMA_Stream_TypeDef * const stm32_dma1_regs[MCU_DMA_STREAM_COUNT] = MCU_DMA1_REGS;

const u32 stm32_dma_channels[8] = {
    DMA_CHANNEL_0, DMA_CHANNEL_1, DMA_CHANNEL_2, DMA_CHANNEL_3, DMA_CHANNEL_4, DMA_CHANNEL_5, DMA_CHANNEL_6, DMA_CHANNEL_7
};

u32 stm32_dma_decode_channel(u32 channel_number){
    return stm32_dma_channels[channel_number];
}

DMA_Stream_TypeDef * stm32_dma_get_stream_instance(u32 dma_number, u32 stream_number){
    if( dma_number ){
        return stm32_dma1_regs[stream_number];
    }

    return stm32_dma0_regs[stream_number];
}

void stm32_dma_set_handle(stm32_dma_channel_t * channel, u32 dma_number, u32 stream_number){
    if( dma_number < MCU_DMA_PORTS ){
        if( stream_number < MCU_DMA_STREAM_COUNT ){
            channel->next = 0;
            stm32_dma_channel_t * current_channel = stm32_dma_handle[dma_number].stream[stream_number];
            if( current_channel == 0 ){
                stm32_dma_handle[dma_number].stream[stream_number] = channel;
            } else {
                while( current_channel->next != 0 ){
                    current_channel = current_channel->next;
                }
                current_channel->next = channel;
            }
        }
    }
}

void stm32_dma_clear_handle(stm32_dma_channel_t * channel, u32 dma_number, u32 stream_number){
    //remove a handle that is in the list
}


static void mcu_core_dma_handler(int dma_number, int stream_number){
    stm32_dma_channel_t * channel = stm32_dma_handle[dma_number].stream[stream_number];
    while( channel != 0 ){
        HAL_DMA_IRQHandler(&channel->handle);
        channel = channel->next;
    }
}

void mcu_core_dma1_stream0_isr(){ mcu_core_dma_handler(0, 0); }
void mcu_core_dma1_stream1_isr(){ mcu_core_dma_handler(0, 1); }
void mcu_core_dma1_stream2_isr(){ mcu_core_dma_handler(0, 2); }
void mcu_core_dma1_stream3_isr(){ mcu_core_dma_handler(0, 3); }
void mcu_core_dma1_stream4_isr(){ mcu_core_dma_handler(0, 4); }
void mcu_core_dma1_stream5_isr(){ mcu_core_dma_handler(0, 5); }
void mcu_core_dma1_stream6_isr(){ mcu_core_dma_handler(0, 6); }
void mcu_core_dma1_stream7_isr(){ mcu_core_dma_handler(0, 7); }


#if MCU_DMA_PORTS > 1

void mcu_core_dma2_stream0_isr(){ mcu_core_dma_handler(0, 0); }
void mcu_core_dma2_stream1_isr(){ mcu_core_dma_handler(0, 1); }
void mcu_core_dma2_stream2_isr(){ mcu_core_dma_handler(0, 2); }
void mcu_core_dma2_stream3_isr(){ mcu_core_dma_handler(0, 3); }
void mcu_core_dma2_stream4_isr(){ mcu_core_dma_handler(0, 4); }
void mcu_core_dma2_stream5_isr(){ mcu_core_dma_handler(0, 5); }
void mcu_core_dma2_stream6_isr(){ mcu_core_dma_handler(0, 6); }
void mcu_core_dma2_stream7_isr(){ mcu_core_dma_handler(0, 7); }

#endif

#endif