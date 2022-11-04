// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

#define MATRIX_ROWS 4
#define MATRIX_COLS 5 * 2

#define MATRIX_ROW_PINS { GP3, GP4, GP2, GP1}
#define MATRIX_COL_PINS { GP26, GP27, GP28, GP29, GP0 }

#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD2
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
