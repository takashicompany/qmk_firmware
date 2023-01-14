// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { B3, F6, F7, B1, B2 }
#define MATRIX_COL_PINS { D1, D0, D4, C6, D7, E6, B4}

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6