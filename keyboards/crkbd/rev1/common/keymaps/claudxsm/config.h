/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

//#define USE_MATRIX_I2C
// #ifdef KEYBOARD_crkbd_rev1_legacy
// #    undef USE_I2C
// #    define USE_SERIAL
// #endif

/* Select hand configuration */

//#define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

//#define USE_SERIAL_PD2
#undef USE_I2C
#undef SSD1306OLED

#define USE_SERIAL_PD2

#define OLED_FONT_H "keyboards/crkbd/rev1/common/keymaps/claudxsm/glcdfont.c"

//#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define OLED_DISABLE_TIMEOUT
#define TAPPING_TERM 250
#define TAPPING_TERM_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
