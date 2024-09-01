/*
This is the c configuration file for the keymap

Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#define WS2812_PIO_USE_PIO1 // RP2040用に追加
#define WS2812_DI_PIN GP0 // D-inをつなぐTX0の端子
#endif

#define TAP_CODE_DELAY 5

//#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
//#define AUTO_MOUSE_DEFAULT_LAYER 1
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define KEYBALL_CPI_DEFAULT 800
#define KEYBALL_SCROLL_DIV_DEFAULT 7

#define BONGO_ENABLE

#define LAYER_STATE_8BIT

/* define RP2040 boot用 */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
/* define RP2040 PC起動時認識用（SPLIT_USB_DETECTが有効となっているため） */
#define SPLIT_USB_TIMEOUT 2500 //Default 2000
#define SPLIT_USB_TIMEOUT_POLL 25 //Default 10
/* OLED driver and pins */
#define HAL_USE_I2C TRUE
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MOSI_PIN GP23
#define SPI_MISO_PIN GP20
#define PMW33XX_CS_PIN GP21 // SPI CS pin.
//#define POINTING_DEVICE_INVERT_Y
//#define POINTING_DEVICE_ROTATION_270

/* Optional. */
#define PMW33XX_CPI 1600      // The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.
#define PMW33XX_CLOCK_SPEED 2000000 // Sets the clock speed that the sensor runs at. Defaults to 2000000
#define MOUSE_EXTENDED_REPORT // Use -32767 to 32767, instead of just -127 to 127.
// #define POINTING_DEVICE_TASK_THROTTLE_MS 10
