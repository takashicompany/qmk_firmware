/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCEEB
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    leafcutterlabs
#define PRODUCT         3x3plus3
#define DESCRIPTION     9 key/3rotary  board

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *                  NO_DIODE = switches are directly connected to AVR pins
 *
*/
// #define MATRIX_ROW_PINS { D0, D5 }
// #define MATRIX_COL_PINS { F1, F0, B0 }
#define DIRECT_PINS { \
    { B4, F7, F4 }, \
    { B5, F6, F1 }, \
    { B6, F0, E6 }, \
	{ D3, D5, B0 } \
}

#define ENCODERS_PAD_B { D2, D0, B3 }
#define ENCODERS_PAD_A { D1, B1, B2 }