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

#include <fcntl.h>
#include <cortexm/cortexm.h>
#include <mcu/pio.h>
#include <mcu/debug.h>
#include <mcu/core.h>
#include "uart_local.h"

#if MCU_UART_PORTS > 0

#include "uart_local.h"


uart_local_t m_uart_local[MCU_UART_PORTS] MCU_SYS_MEM;
USART_TypeDef * const uart_regs_table[MCU_UART_PORTS] = MCU_UART_REGS;
u8 const uart_irqs[MCU_UART_PORTS] = MCU_UART_IRQS;

static void handle_bytes_received(uart_local_t * local);

int uart_local_open(const devfs_handle_t * handle){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);
	if ( local->ref_count == 0 ){

		local->hal_handle.Instance = uart_regs_table[port];

		switch(port){
			case 0:
				__HAL_RCC_USART1_CLK_ENABLE();
				break;
#if defined USART2
			case 1:
				__HAL_RCC_USART2_CLK_ENABLE();
				break;
#endif
#if defined USART3
			case 2:
				__HAL_RCC_USART3_CLK_ENABLE();
				break;
#endif
#if defined UART4
			case 3:
				__HAL_RCC_UART4_CLK_ENABLE();
				break;
#endif
#if defined UART5
			case 4:
				__HAL_RCC_UART5_CLK_ENABLE();
				break;
#endif
#if defined USART6
			case 5:
				__HAL_RCC_USART6_CLK_ENABLE();
				break;
#endif

		}
		//reset HAL UART
		cortexm_enable_irq(uart_irqs[port]);

	}
	local->ref_count++;

	return 0;
}

int uart_local_close(const devfs_handle_t * handle){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);

	if ( local->ref_count > 0 ){
		if ( local->ref_count == 1 ){
			cortexm_disable_irq(uart_irqs[port]);
			switch(port){
				case 0:
					__HAL_RCC_USART1_CLK_DISABLE();
					break;
#if defined USART2
				case 1:
					__HAL_RCC_USART2_CLK_DISABLE();
					break;
#endif
#if defined USART3
				case 2:
					__HAL_RCC_USART3_CLK_DISABLE();
					break;
#endif
#if defined UART4
				case 3:
					__HAL_RCC_UART4_CLK_DISABLE();
					break;
#endif
#if defined UART5
				case 4:
					__HAL_RCC_UART5_CLK_DISABLE();
					break;
#endif
#if defined USART6
				case 5:
					__HAL_RCC_USART6_CLK_DISABLE();
					break;
#endif

			}
			local->hal_handle.Instance = 0;
		}
		local->ref_count--;
	}
	return 0;
}

int uart_local_getinfo(const devfs_handle_t * handle, void * ctl){

	uart_info_t * info = ctl;

	info->o_flags = UART_FLAG_IS_PARITY_NONE |
			UART_FLAG_IS_PARITY_ODD |
			UART_FLAG_IS_PARITY_EVEN |
			UART_FLAG_IS_STOP1 |
			UART_FLAG_IS_STOP2 |
			UART_FLAG_IS_RX_FIFO;

	return 0;
}

int uart_local_setattr(const devfs_handle_t * handle, void * ctl){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);
	u32 o_flags;
	u32 freq;

	const uart_attr_t * attr = mcu_select_attr(handle, ctl);
	if( attr == 0 ){
		return SYSFS_SET_RETURN(EINVAL);
	}

	const uart_config_t * config = handle->config;
	if( config ){
		local->fifo_config = config->fifo_config;
	} else {
		local->fifo_config = 0;
	}

	o_flags = attr->o_flags;

	if( o_flags & UART_FLAG_SET_LINE_CODING ){
		freq = attr->freq;
		if( freq == 0 ){
			freq = 115200;
		}

		local->hal_handle.Init.BaudRate = freq;

		local->hal_handle.Init.WordLength = UART_WORDLENGTH_8B;
		if( attr->width == 9 ){
			local->hal_handle.Init.WordLength = UART_WORDLENGTH_9B;
		}

		local->hal_handle.Init.StopBits = UART_STOPBITS_1;
		if( o_flags & UART_FLAG_IS_STOP2 ){
			local->hal_handle.Init.StopBits = UART_STOPBITS_2;
		}

		local->hal_handle.Init.Parity = UART_PARITY_NONE;
		if( o_flags & UART_FLAG_IS_PARITY_EVEN ){
			local->hal_handle.Init.Parity = UART_PARITY_EVEN;
		} else if( o_flags & UART_FLAG_IS_PARITY_ODD ){
			local->hal_handle.Init.Parity = UART_PARITY_ODD;
		}

		local->hal_handle.Init.Mode = UART_MODE_TX_RX;
		local->hal_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		local->hal_handle.Init.OverSampling = UART_OVERSAMPLING_16;

		//pin assignments
		if( mcu_set_pin_assignment(
				 &(attr->pin_assignment),
				 MCU_CONFIG_PIN_ASSIGNMENT(uart_config_t, handle),
				 MCU_PIN_ASSIGNMENT_COUNT(uart_pin_assignment_t),
				 CORE_PERIPH_UART, port, 0, 0, 0) < 0 ){
			return SYSFS_SET_RETURN(EINVAL);
		}

		if( HAL_UART_Init(&local->hal_handle) != HAL_OK ){
			return SYSFS_SET_RETURN(EIO);
		}

		//enable the idle interrupt
		if( local->fifo_config ){
			SET_BIT(local->hal_handle.Instance->CR1, USART_CR1_IDLEIE);
		}

	}

	return SYSFS_RETURN_SUCCESS;
}

int uart_local_setaction(const devfs_handle_t * handle, void * ctl){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);
	mcu_action_t * action = (mcu_action_t*)ctl;

	if( action->handler.callback == 0 ){
		//if there is an ongoing operation -- cancel it
		if( action->o_events & MCU_EVENT_FLAG_DATA_READY ){
			//execute the read callback if not null
			fifo_cancel_async_read(&local->fifo_state);
		}

		if( action->o_events & MCU_EVENT_FLAG_WRITE_COMPLETE ){
#if defined STM32F4
			if( local->o_flags & UART_LOCAL_IS_DMA ){
				//stop the DMA write but not the DMA read -- there isn't a simple call to do this
			} else {
				HAL_UART_AbortTransmit_IT(&local->hal_handle);
			}
#endif
			devfs_execute_write_handler(&local->transfer_handler, 0, SYSFS_SET_RETURN(EIO), MCU_EVENT_FLAG_CANCELED);
		}
	}

	cortexm_set_irq_priority(uart_irqs[port], action->prio, action->o_events);
	return 0;
}

int uart_local_put(const devfs_handle_t * handle, void * ctl){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);
	u8 c = (u32)ctl;

	if( HAL_UART_Transmit(&local->hal_handle, &c, 1, HAL_MAX_DELAY) != HAL_OK ){
		return SYSFS_SET_RETURN(EIO);
	}

	return SYSFS_RETURN_SUCCESS;
}

int uart_local_flush(const devfs_handle_t * handle, void * ctl){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);
	fifo_flush(&local->fifo_state);
	return SYSFS_RETURN_SUCCESS;
}


int uart_local_get(const devfs_handle_t * handle, void * ctl){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);

	if( local->fifo_config == 0 ){ return SYSFS_SET_RETURN(ENOSYS); }

	//is there a byte on the FIFO to read?
	int result = fifo_read_buffer(local->fifo_config, &local->fifo_state, ctl, 1);
	if( result == 1 ){
		return SYSFS_RETURN_SUCCESS;
	}

	return SYSFS_SET_RETURN(ENODATA);
}

int uart_local_read(const devfs_handle_t * handle, devfs_async_t * async){
	DEVFS_DRIVER_DECLARE_LOCAL(uart, MCU_UART_PORTS);

	if( local->fifo_config == 0 ){ return SYSFS_SET_RETURN(ENOSYS); }

	//read the fifo, block if no bytes are available
	return fifo_read_local(local->fifo_config, &local->fifo_state, async, 1);
}

void handle_bytes_received(uart_local_t * local){

	//increment the head by the number of bytes received
	for(u16 i=0; i < local->bytes_received; i++){
		fifo_inc_head(&local->fifo_state, local->fifo_config->size);
	}

	//now tell the fifo the head has been updated so it can return data to the user asynchronously
	fifo_data_received(local->fifo_config, &local->fifo_state);

}

void HAL_UART_RxIdleCallback(UART_HandleTypeDef *huart){
	uart_local_t * local = (uart_local_t*)huart;
	u16 head = local->fifo_state.atomic_position.access.head;
	if( huart->hdmarx ){
		local->bytes_received = local->fifo_config->size - __HAL_DMA_GET_COUNTER(huart->hdmarx) - head;
	} else {
		local->bytes_received = (huart->RxXferSize - huart->RxXferCount) - head;
	}
	handle_bytes_received(local);
	mcu_debug_printf("idle %d from %d\n", local->bytes_received, head);
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){
	MCU_UNUSED_ARGUMENT(huart);
}

//called when RX IT is complete or when DMA does full transfer
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	uart_local_t * local = (uart_local_t*)huart;

	local->bytes_received = local->fifo_config->size - local->fifo_state.atomic_position.access.head;
	handle_bytes_received(local);

	if( local->hal_handle.hdmarx == 0 ){
		//if not in circular DMA mode -- start the next interrupt based read
		HAL_UART_Receive_IT(&local->hal_handle,
								  (u8*)local->fifo_config->buffer,
								  local->fifo_config->size);
	}
	mcu_debug_printf("cplt\n");
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
	uart_local_t * local = (uart_local_t*)huart;
	devfs_execute_read_handler(&local->transfer_handler, 0, SYSFS_SET_RETURN(EIO), MCU_EVENT_FLAG_ERROR | MCU_EVENT_FLAG_CANCELED);

	mcu_debug_printf("e:0x%X\n", huart->ErrorCode);

	if( local->hal_handle.hdmarx == 0 ){

		local->bytes_received = local->fifo_config->size - huart->RxXferCount - local->fifo_state.atomic_position.access.head;
		handle_bytes_received(local);

		//reset the head
		fifo_flush(&local->fifo_state);


		//if not in circular DMA mode -- start the next interrupt based read
		HAL_UART_Receive_IT(&local->hal_handle,
								  (u8*)local->fifo_config->buffer,
								  local->fifo_config->size);
	} else {
		local->bytes_received = local->fifo_config->size - __HAL_DMA_GET_COUNTER(huart->hdmarx) - local->fifo_state.atomic_position.access.head;
		handle_bytes_received(local);

		//reset the head
		fifo_flush(&local->fifo_state);


		//if not in circular DMA mode -- start the next interrupt based read
		HAL_UART_Receive_DMA(&local->hal_handle,
								  (u8*)local->fifo_config->buffer,
								  local->fifo_config->size);
	}
}

void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart){
	//this does not need to do anything
}

void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart){

}

void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart){

}

void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart){

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	uart_local_t * local = (uart_local_t*)huart;
	int nbyte = 0;
	//when transfer is complete, count is 0 and size is the original async->nbyte value
	nbyte = huart->TxXferSize - huart->TxXferCount;
	devfs_execute_write_handler(&local->transfer_handler, 0, nbyte, MCU_EVENT_FLAG_DATA_READY);
}


void mcu_uart_isr(int port){
	uart_local_t * local = m_uart_local + port;
	HAL_UART_IRQHandler(&local->hal_handle);

#if defined USART_SR_IDLE
	if(  READ_REG(local->hal_handle.Instance->SR) & USART_SR_IDLE ){
		local->hal_handle.Instance->DR; //this will clear the idle bit
#elif defined USART_ISR_IDLE
	if(  READ_REG(local->hal_handle.Instance->ISR) & USART_ISR_IDLE ){
		local->hal_handle.Instance->RDR; //this will clear the idle bit
#endif
		HAL_UART_RxIdleCallback((UART_HandleTypeDef*)local);
		return;
	}
}

void mcu_core_usart1_isr(){
	mcu_uart_isr(0);
}

#if MCU_UART_PORTS > 1
void mcu_core_usart2_isr(){
	mcu_uart_isr(1);
}
#endif

#if MCU_UART_PORTS > 2
void mcu_core_usart3_isr(){
	mcu_uart_isr(2);
}
#endif

#if MCU_UART_PORTS > 3
void mcu_core_uart4_isr(){
	mcu_uart_isr(3);
}
#endif

#if MCU_UART_PORTS > 4
void mcu_core_uart5_isr(){
	mcu_uart_isr(4);
}
#endif

#if MCU_UART_PORTS > 5
void mcu_core_usart6_isr(){
	mcu_uart_isr(5);
}
#endif

#if MCU_UART_PORTS > 6
void mcu_core_uart7_isr(){
	mcu_uart_isr(6);
}
#endif


#if MCU_UART_PORTS > 7
void mcu_core_uart8_isr(){
	mcu_uart_isr(7);
}
#endif

#endif
