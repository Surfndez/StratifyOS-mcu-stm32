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

#include "hal.h"

#include <mcu/core.h>

#if defined __stm32f446xx

#define TOTAL_ENTRIES 16

typedef struct {
	u16 entry[TOTAL_ENTRIES];
} alternate_function_entry_t;

#define ENTRY(function, port) (port<<8|function)
#define RESERVED_ (ENTRY(CORE_PERIPH_RESERVED, 0))
#define ENTRY_GET_FUNCTION(entry) (entry & 0xFF)
#define ENTRY_GET_PORT(entry) ( entry >> 8)

#define E_TMR_(port) ENTRY(CORE_PERIPH_TMR,port)
#define E_TMR(port) ENTRY(CORE_PERIPH_TMR,port)
#define E_UART(port) ENTRY(CORE_PERIPH_UART,port)
#define E_USRT(port) ENTRY(CORE_PERIPH_UART,port)
#define E_I2S_(port) ENTRY(CORE_PERIPH_I2S,port)
#define E_SYS_(port) ENTRY(CORE_PERIPH_SYS,port)
#define E_QSPI(port) ENTRY(CORE_PERIPH_QSPI,port)
#define E_SPI_(port) ENTRY(CORE_PERIPH_SPI,port)
#define E_USB_(port) ENTRY(CORE_PERIPH_USB,port)
#define E_LCD_(port) ENTRY(CORE_PERIPH_LCD,port)
#define E_FMC_(port) ENTRY(CORE_PERIPH_LCD,port)
#define E_MCO_(port) ENTRY(CORE_PERIPH_LCD,port)
#define E_I2C_(port) ENTRY(CORE_PERIPH_I2C,port)
#define E_HDMI(port) ENTRY(CORE_PERIPH_I2C,port)
#define E_CAN_(port) ENTRY(CORE_PERIPH_CAN,port)
#define E_JTAG(port) ENTRY(CORE_PERIPH_JTAG,port)
#define E_RTC_(port) ENTRY(CORE_PERIPH_RTC,port)
#define E_SPDF(port) ENTRY(CORE_PERIPH_RTC,port)
#define E_SDIO(port) ENTRY(CORE_PERIPH_RTC,port)
#define E_TRAC(port) ENTRY(CORE_PERIPH_TRACE,port)
#define E_FMP_(port) ENTRY(CORE_PERIPH_I2C,port)


#define TOTAL_PINS (7*16+2)

const alternate_function_entry_t alternate_function_table[TOTAL_PINS] = {
		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, E_TMR_(2), E_TMR_(5), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, E_USRT(2), E_USRT(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA0
		{{ RESERVED_, E_TMR_(2), E_TMR_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), E_USRT(4), E_QSPI(4), E_I2S_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA1
		{{ RESERVED_, E_TMR_(2), E_TMR_(5), E_TMR_(9), RESERVED_, RESERVED_, RESERVED_, E_USRT(2), E_I2S_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA2
		{{ RESERVED_, E_TMR_(2), E_TMR_(5), E_TMR_(8), RESERVED_, RESERVED_, E_I2S_(1), E_USRT(2), RESERVED_, RESERVED_, E_USB_(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA3
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(1), RESERVED_, E_SPI_(3), E_USRT(4), E_QSPI(4), E_I2S_(4), RESERVED_, E_USB_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PA4
		{{ RESERVED_, E_TMR_(2), RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(1), RESERVED_, E_USRT(2), E_I2S_(2), RESERVED_, E_USB_(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA5
		{{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, E_SPI_(1), E_I2S_(2), RESERVED_, RESERVED_, E_TMR(13), RESERVED_, RESERVED_, RESERVED_, E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PA6
		{{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, E_SPI_(1), RESERVED_, RESERVED_, RESERVED_, E_TMR(14), RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PA7
		{{ E_MCO_(1), E_TMR_(1), RESERVED_, RESERVED_, E_I2C_(3), RESERVED_, RESERVED_, E_USRT(1), RESERVED_, RESERVED_, E_USB_(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA8
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, E_I2C_(3), E_SPI_(2), E_I2S_(1), E_USRT(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PA9
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(1), RESERVED_, RESERVED_, E_USB_(0), RESERVED_, RESERVED_, E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PA10
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(1), RESERVED_, E_CAN_(1), E_USB_(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA11
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(1), E_I2S_(2), E_CAN_(1), E_USB_(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA12
		{{ E_JTAG(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA13
		{{ E_JTAG(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA14
		{{ E_JTAG(0), E_TMR_(2), RESERVED_, RESERVED_, E_HDMI(0), E_SPI_(1), E_SPI_(3), RESERVED_, E_UART(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PA15

		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_UART(4), RESERVED_, E_USB_(0), RESERVED_, E_SDIO(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PB0
		{{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(0), RESERVED_, E_SDIO(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PB1
		{{ RESERVED_, E_TMR_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(1), E_SPI_(3), RESERVED_, E_QSPI(0), E_USB_(0), RESERVED_, E_SDIO(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PB2
		{{ E_JTAG(0), E_TMR_(2), RESERVED_, RESERVED_, E_I2C_(2), E_SPI_(1), E_SPI_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PB3
		{{ E_JTAG(0), RESERVED_, E_TMR_(3), RESERVED_, E_I2C_(2), E_SPI_(1), E_SPI_(3), E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PB4
		{{ RESERVED_, RESERVED_, E_TMR_(3), RESERVED_, E_I2C_(1), E_SPI_(1), E_SPI_(3), RESERVED_, RESERVED_, E_CAN_(2), E_USB_(0), RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PB5
		{{ RESERVED_, RESERVED_, E_TMR_(4), E_HDMI(0), E_I2C_(1), RESERVED_, RESERVED_, E_USRT(1), RESERVED_, E_CAN_(2), E_USB_(0), RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PB6
		{{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, E_I2C_(1), RESERVED_, RESERVED_, E_USRT(1), E_SPDF(0), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PB7
		{{ RESERVED_, E_TMR_(2), E_TMR_(4), E_TMR(10), E_I2C_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PB8
		{{ RESERVED_, E_TMR_(2), E_TMR_(4), E_TMR(11), E_I2C_(1), E_SPI_(2), E_I2S_(1), RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PB9
		{{ RESERVED_, E_TMR_(2), RESERVED_, RESERVED_, E_I2C_(2), E_SPI_(2), E_I2S_(1), E_USRT(3), RESERVED_, RESERVED_, E_USB_(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PB10
		{{ RESERVED_, E_TMR_(2), RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, E_USRT(3), E_I2S_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PB11
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, E_I2C_(2), E_SPI_(2), E_I2S_(1), E_USRT(3), RESERVED_, E_CAN_(2), E_USB_(0), RESERVED_, E_USB_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PB12
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, E_USRT(3), RESERVED_, E_CAN_(2), E_USB_(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PB13
		{{ RESERVED_, E_TMR_(1), RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(2), RESERVED_, E_USRT(3), RESERVED_, E_TMR(12), RESERVED_, RESERVED_, E_USB_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PB14
		{{ E_RTC_(0), E_TMR_(1), RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, E_TMR(12), RESERVED_, RESERVED_, E_USB_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PB15

		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, E_USB_(0), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PC0
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_I2S_(1), E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PC1
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(0), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PC2
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(0), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PC3
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, E_SPDF(0), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PC4
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), E_SPDF(0), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PC5
		{{ RESERVED_, RESERVED_, E_TMR_(3), E_TMR_(8), E_FMP_(1), E_I2S_(2), RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PC6
		{{ RESERVED_, RESERVED_, E_TMR_(3), E_TMR_(8), E_FMP_(1), E_SPI_(2), E_I2S_(3), E_SPDF(0), E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PC7
		{{ E_TRAC(0), RESERVED_, E_TMR_(3), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, E_UART(5), E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PC8
		{{ E_MCO_(2), RESERVED_, E_TMR_(3), E_TMR_(8), E_I2C_(3), E_I2S_(0), RESERVED_, E_UART(5), RESERVED_, E_QSPI(0), RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PC9
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_USRT(3), E_UART(4), E_QSPI(0), RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PC10
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_USRT(3), E_UART(4), E_QSPI(0), RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PC11
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, E_SPI_(3), E_USRT(3), E_UART(4), RESERVED_, RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PC12
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PC13
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PC14
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PC15

		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), E_SPI_(3), RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD0
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD1
		{{ RESERVED_, RESERVED_, E_TMR_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_UART(5), RESERVED_, RESERVED_, RESERVED_, E_SDIO(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PD2
		{{ E_TRAC(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, E_USRT(2), RESERVED_, E_QSPI(0), RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PD3
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD4
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD5
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_I2S_(1), E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PD6
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), E_SPDF(0), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD7
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), E_SPDF(0), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD8
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD9
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD10
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, E_USRT(3), RESERVED_, E_QSPI(0), E_I2S_(2), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD11
		{{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, E_USRT(3), RESERVED_, E_QSPI(0), E_I2S_(2), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD12
		{{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_QSPI(0), E_I2S_(2), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD13
		{{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD14
		{{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PD15

		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PE0
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PE1
		{{ E_TRAC(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, E_QSPI(0), RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE2
		{{ E_TRAC(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE3
		{{ E_TRAC(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PE4
		{{ E_TRAC(0), RESERVED_, RESERVED_, E_TMR_(9), RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PE5
		{{ E_TRAC(0), RESERVED_, RESERVED_, E_TMR_(9), RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PE6
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_UART(5), RESERVED_, E_QSPI(0), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE7
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_UART(5), RESERVED_, E_QSPI(0), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE8
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_QSPI(0), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE9
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_QSPI(0), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE10
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE11
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE12
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE13
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE14
		{{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PE15

		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF0
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF1
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF2
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF3
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF4
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF5
		{{ RESERVED_, RESERVED_, RESERVED_, E_TMR(10), RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, E_QSPI(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PF6
		{{ RESERVED_, RESERVED_, RESERVED_, E_TMR(11), RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, E_QSPI(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PF7
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, E_TMR(13), E_QSPI(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PF8
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, E_TMR(14), E_QSPI(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PF9
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PF10
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PF11
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF12
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF13
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF14
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMP_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PF15

		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG0
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG1
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG2
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG3
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG4
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG5
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_QSPI(0), RESERVED_, RESERVED_, E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PG6
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PG7
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPDF(0), E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG8
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPDF(0), E_USRT(6), E_QSPI(0), E_I2S_(2), RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PG9
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(2), RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PG10
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), E_SPDF(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PG11
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), E_SPDF(0), E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG12
		{{ E_TRAC(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG13
		{{ E_TRAC(0), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, E_USRT(6), E_QSPI(0), RESERVED_, RESERVED_, E_FMC_(0), RESERVED_, RESERVED_, E_SYS_(0) }}, //PG14
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(0), E_LCD_(0), RESERVED_, E_SYS_(0) }}, //PG15


		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PH0
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }} //PH1

		/*
		//   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX0
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX1
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX2
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX3
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX4
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX5
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX6
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX7
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX8
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX9
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX10
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX11
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX12
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX13
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX14
		{{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(0) }}, //PX15
		 */


};


int hal_get_alternate_function(int gpio_port, int pin, core_periph_t function, int periph_port){
	int i;
	alternate_function_entry_t entry;
	u16 value = gpio_port * 16 + pin;
	i = -1;
	if( value < TOTAL_PINS ){
		entry = alternate_function_table[value];
		value = -1;
		for(i = 0; i < TOTAL_ENTRIES; i++){
			if ( (function == ENTRY_GET_FUNCTION(entry.entry[i])) &&
					(periph_port == ENTRY_GET_PORT(entry.entry[i])) ){
				//this is a valid pin
				value = i;
				break;
			}
		}
	}
	return i;
}

int hal_set_alternate_pin_function(mcu_pin_t pin, core_periph_t function, int periph_port, int mode){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_TypeDef * gpio_regs;
	int alternate_function;

	gpio_regs = hal_get_pio_regs(pin.port);
	if( gpio_regs == 0 ){
		return -1;
	}

	alternate_function =	hal_get_alternate_function(pin.port, pin.pin,
			CORE_PERIPH_UART, periph_port);

	if( alternate_function < 0 ){
		return -1;
	}


	GPIO_InitStruct.Pin = (1<<pin.pin);
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = alternate_function;
	HAL_GPIO_Init(gpio_regs, &GPIO_InitStruct);
	return 0;
}

int mcu_core_set_pinsel_func(const mcu_pin_t * pin, core_periph_t function, int periph_port){
	return 0;
}

#endif
