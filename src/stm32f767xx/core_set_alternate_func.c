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

#include <mcu/core.h>
#include <mcu/debug.h>
#include "stm32_local.h"
#include "stm32_pin_local.h"

const alternate_function_entry_t alternate_function_table[MCU_TOTAL_PINS] = {
    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, E_TMR_(2), E_TMR_(5), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, E_USRT(2), E_USRT(4), RESERVED_, RESERVED_, E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA0
    {{ RESERVED_, E_TMR_(2), E_TMR_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), E_USRT(4), RESERVED_, RESERVED_, E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA1
    {{ RESERVED_, E_TMR_(2), E_TMR_(5), E_TMR_(9), RESERVED_, RESERVED_, RESERVED_, E_USRT(2), RESERVED_, RESERVED_, RESERVED_, E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA2
    {{ RESERVED_, E_TMR_(2), E_TMR_(5), E_TMR_(9), RESERVED_, RESERVED_, RESERVED_, E_USRT(2), RESERVED_, RESERVED_, E_USB_(1), E_ENET(1), RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PA3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(1), E_SPI_(3), E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PA4
    {{ RESERVED_, E_TMR_(2), RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA5
    {{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, E_SPI_(1), RESERVED_, RESERVED_, RESERVED_, E_TMR(13), RESERVED_, RESERVED_, RESERVED_, E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PA6
    {{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, E_SPI_(1), RESERVED_, RESERVED_, RESERVED_, E_TMR(14), RESERVED_, E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA7
    {{ E_MCO_(1), E_TMR_(1), RESERVED_, RESERVED_, E_I2C_(3), RESERVED_, RESERVED_, E_USRT(1), RESERVED_, RESERVED_, E_USB_(1), RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PA8
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, E_I2C_(3), RESERVED_, RESERVED_, E_USRT(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PA9
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(1), RESERVED_, RESERVED_, E_USB_(1), RESERVED_, RESERVED_, E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PA10
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(1), RESERVED_, E_CAN_(1), E_USB_(1), RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PA11
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(1), RESERVED_, E_CAN_(1), E_USB_(1), RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PA12
    {{ E_JTAG(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA13
    {{ E_JTAG(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA14
    {{ E_JTAG(1), E_TMR_(2), RESERVED_, RESERVED_, RESERVED_, E_SPI_(1), E_SPI_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PA15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_USB_(1), E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PB0
    {{ RESERVED_, E_TMR_(1), E_TMR_(3), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_USB_(1), E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PB1
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PB2
    {{ E_JTAG(1), E_TMR_(2), RESERVED_, RESERVED_, RESERVED_, E_SPI_(1), E_SPI_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PB3
    {{ E_JTAG(1), RESERVED_, E_TMR_(3), RESERVED_, RESERVED_, E_SPI_(1), E_SPI_(3), E_I2S_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PB4
    {{ RESERVED_, RESERVED_, E_TMR_(3), RESERVED_, E_I2C_(1), E_SPI_(1), E_SPI_(3), RESERVED_, RESERVED_, E_CAN_(2), E_USB_(1), E_ENET(1), E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PB5
    {{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, E_I2C_(1), RESERVED_, RESERVED_, E_USRT(1), RESERVED_, E_CAN_(2), RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PB6
    {{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, E_I2C_(1), RESERVED_, RESERVED_, E_USRT(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PB7
    {{ RESERVED_, RESERVED_, E_TMR_(4), E_TMR(10), E_I2C_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, E_ENET(1), E_SDIO(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PB8
    {{ RESERVED_, RESERVED_, E_TMR_(4), E_TMR(11), E_I2C_(1), E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PB9
    {{ RESERVED_, E_TMR_(2), RESERVED_, RESERVED_, E_I2C_(2), E_SPI_(2), RESERVED_, E_USRT(1), RESERVED_, RESERVED_, E_USB_(1), E_ENET(1), RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PB10
    {{ RESERVED_, E_TMR_(2), RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, E_USRT(1), RESERVED_, RESERVED_, E_USB_(1), E_ENET(1), RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PB11
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, E_I2C_(2), E_SPI_(2), RESERVED_, E_USRT(1), RESERVED_, E_CAN_(2), E_USB_(1), E_ENET(1), E_USB_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PB12
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, E_USRT(1), RESERVED_, E_CAN_(2), E_USB_(1), E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PB13
    {{ RESERVED_, E_TMR_(1), RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(2), E_I2S_(2), E_USRT(1), RESERVED_, E_TMR(12), RESERVED_, RESERVED_, E_USB_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PB14
    {{ E_RTC_(1), E_TMR_(1), RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, E_TMR(12), RESERVED_, RESERVED_, E_USB_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PB15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(1), RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PC0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PC1
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), E_I2S_(2), RESERVED_, RESERVED_, RESERVED_, E_USB_(1), E_ENET(1), E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PC2
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(1), E_ENET(1), E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PC3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PC4
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PC5
    {{ RESERVED_, RESERVED_, E_TMR_(3), E_TMR_(8), RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PC6
    {{ RESERVED_, RESERVED_, E_TMR_(3), E_TMR_(8), RESERVED_, RESERVED_, E_SPI_(3), RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PC7
    {{ RESERVED_, RESERVED_, E_TMR_(3), E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PC8
    {{ E_MCO_(2), RESERVED_, E_TMR_(3), E_TMR_(8), E_SYS_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PC9
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_SPI_(3), E_USRT(3), E_USRT(4), RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PC10
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(3), E_SPI_(3), E_SPI_(3), E_USRT(3), E_USRT(4), RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PC11
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_SPI_(3), E_USRT(3), E_USRT(4), RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PC12
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PC13
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PC14
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PC15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD1
    {{ RESERVED_, RESERVED_, E_TMR_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(5), RESERVED_, RESERVED_, RESERVED_, E_SDIO(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PD2
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PD3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD4
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD5
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(3), E_I2S_(1), E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PD6
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD7
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD8
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD9
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD10
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD11
    {{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD12
    {{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD13
    {{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD14
    {{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PD15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, E_TMR_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(8), RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PE0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(8), RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PE1
    {{ E_TRAC(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE2
    {{ E_TRAC(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE3
    {{ E_TRAC(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PE4
    {{ E_TRAC(1), RESERVED_, RESERVED_, E_TMR_(9), RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PE5
    {{ E_TRAC(1), RESERVED_, RESERVED_, E_TMR_(9), RESERVED_, E_SPI_(4), E_I2S_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PE6
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(7), RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE7
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(7), RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE8
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE9
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE10
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE11
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE12
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE13
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, E_SPI_(4), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE14
    {{ RESERVED_, E_TMR_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PE15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF1
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF2
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF4
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF5
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_TMR(10), RESERVED_, E_SPI_(5), E_I2S_(1), RESERVED_, E_USRT(7), RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF6
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_TMR(11), RESERVED_, E_SPI_(5), E_I2S_(1), RESERVED_, E_USRT(7), RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF7
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(5), E_I2S_(1), RESERVED_, RESERVED_, E_TMR(13), RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF8
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(5), E_I2S_(1), RESERVED_, RESERVED_, E_TMR(14), RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF9
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PF10
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PF11
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF12
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF13
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF14
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PF15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG1
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG2
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG4
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG5
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PG6
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PG7
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(6), RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG8
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PG9
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PG10
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PG11
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(6), RESERVED_, RESERVED_, E_USRT(6), E_LCD_(1), RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG12
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(6), RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG13
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(6), RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), RESERVED_, RESERVED_, RESERVED_ }}, //PG14
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USRT(6), RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, RESERVED_ }}, //PG15


    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PH0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PH1
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PH2
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PH3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PH4
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), E_SPI_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PH5
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(2), E_SPI_(5), RESERVED_, RESERVED_, RESERVED_, E_TMR(12), RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PH6
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(3), E_SPI_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), E_DCMI(1), RESERVED_, E_SYS_(1) }}, //PH7
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PH8
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_I2C_(3), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_TMR(12), RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PH9
    {{ RESERVED_, RESERVED_, E_TMR_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PH10
    {{ RESERVED_, RESERVED_, E_TMR_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PH11
    {{ RESERVED_, RESERVED_, E_TMR_(5), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PH12
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PH13
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PH14
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), E_DCMI(1), E_LCD_(1), E_SYS_(1) }}, //PH15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, E_TMR_(5), RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI1
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(2), E_I2S_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI2
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, E_SPI_(2), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, RESERVED_, E_SYS_(1) }}, //PI3
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI4
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI5
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI6
    {{ RESERVED_, RESERVED_, RESERVED_, E_TMR_(8), RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI7
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PI8
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_CAN_(1), RESERVED_, RESERVED_, E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI9
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_ENET(1), E_FMC_(1), RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI10
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_USB_(1), RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PI11
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI12
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI13
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI14
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PI15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ1
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ2
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ4
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ5
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ6
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ7
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ8
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ9
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ10
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ11
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ12
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ13
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ14
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PJ15

    //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK0
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK1
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK2
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK3
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK4
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK5
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK6
    {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_LCD_(1), E_SYS_(1) }}, //PK7

    /*
                //   0           1          2          3          4         5           6         7          8           9          10        11         12          13        14          15
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX0
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX1
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX2
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX3
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX4
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX5
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX6
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX7
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX8
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX9
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX10
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX11
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX12
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX13
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX14
                {{ RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, RESERVED_, E_SYS_(1) }}, //PX15
             */


};

