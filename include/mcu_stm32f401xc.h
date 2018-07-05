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
 * along with Stratify OS.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef MCU_STM32F401XC_H_
#define MCU_STM32F401XC_H_

#include <mcu/types.h>
#include "cmsis/stm32f4xx.h"
#include "cmsis/stm32f401xC.h"


#define MCU_NO_HARD_FAULT 1

#define MCU_ADC_API 0
#define MCU_ADC_PORTS 1
#define MCU_ADC_REGS { ADC1 }
#define MCU_ADC_IRQS { ADC_IRQn }
#define MCU_ADC_CHANNELS 21

#define MCU_ENET_PORTS 1
#define MCU_FLASH_PORTS 1
#define MCU_MEM_PORTS 1

#define MCU_I2C_API 0
#define MCU_I2C_PORTS 3
#define MCU_I2C_REGS { I2C1, I2C2, I2C3 }
#define MCU_I2C_IRQS { I2C1_EV_IRQn, I2C2_EV_IRQn, I2C3_EV_IRQn }
#define MCU_I2C_ER_IRQS { I2C1_ER_IRQn, I2C2_ER_IRQn, I2C3_ER_IRQn }

#define MCU_CORE_PORTS 1
#define MCU_EEPROM_PORTS 0
#define MCU_SPI_API 0
#define MCU_SPI_PORTS 4
#define MCU_SPI_REGS { SPI1, SPI2, SPI3, SPI4 }
#define MCU_SPI_IRQS { SPI1_IRQn, SPI2_IRQn, SPI3_IRQn, SPI4_IRQn }

//I2S is available on 2 SPI ports SPI2 and SPI3
#define MCU_I2S_ON_SPI1 0
#define MCU_I2S_ON_SPI2 1
#define MCU_I2S_ON_SPI3 1
#define MCU_I2S_ON_SPI4 0

#define MCU_SAI_API 0
#define MCU_SAI_PORTS 0

#define MCU_SDIO_API 0
#define MCU_SDIO_PORTS 1
#define MCU_SDIO_REGS { SDIO }
#define MCU_SDIO_IRQS { SDIO_IRQn }

#define MCU_TMR_PORTS 11
#define MCU_TMR_REGS { TIM1, TIM2, TIM3, TIM4, TIM5, 0, 0, 0, TIM9, TIM10, TIM11 }
#define MCU_TMR_IRQS { -1, TIM2_IRQn, TIM3_IRQn, TIM4_IRQn, TIM5_IRQn, -1, -1, -1, TIM1_BRK_TIM9_IRQn, TIM1_UP_TIM10_IRQn, TIM1_TRG_COM_TIM11_IRQn }

#define MCU_PIO_PORTS 8
#define MCU_PIO_REGS { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, 0, 0, GPIOH }
#define MCU_PIO_IRQS { 0 }

#define MCU_UART_PORTS 6
#define MCU_UART_REGS { USART1, USART2, 0, 0, 0, USART6 }
#define MCU_UART_IRQS { USART1_IRQn, USART2_IRQn, -1, -1, -1, USART6_IRQn }

#define MCU_USB_PORTS 1
#define MCU_USB_REGS { USB_OTG_FS }
#define MCU_USB_IRQS { OTG_FS_IRQn }

#define MCU_DMA_PORTS 2


#define MCU_RTC_PORTS 1
#define MCU_RTC_REGS { RTC }
#define MCU_RTC_IRQS { RTC_Alarm_IRQn }

#define DEV_USB_LOGICAL_ENDPOINT_COUNT 4

#define MCU_LAST_IRQ SPI4_IRQn
#define MCU_MIDDLE_IRQ_PRIORITY 8


#define MCU_RAM_PAGES 48
#define MCU_DELAY_FACTOR 12
#define MCU_TOTAL_PINS (7*16+2)


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif


#endif /* MCU_STM32F401XC_H_ */
