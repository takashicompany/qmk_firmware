// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi_idx;
        uint8_t scrl_div;
        uint8_t rotation_angle;
        int8_t scrl_inv;
        bool scrl_mode;
        report_mouse_t last_mouse;
    };
} ergoslit_config_t;



extern ergoslit_config_t ergoslit_config;

enum ergoslit_keycodes {

    ERGOSLIT_KB_SAFE_RANGE = SAFE_RANGE,
    CPI_SW,
    SCRL_SW,
    ROT_R15,
    ROT_L15,
    SCRL_MO,
    SCRL_TO,
    SCRL_IN,
    ERGOSLIT_SAFE_RANGE,
};

#define CPI_SW USER00
#define SCRL_SW USER01
#define ROT_R15 USER02
#define ROT_L15 USER03
#define SCRL_MO USER04
#define SCRL_TO USER05
#define SCRL_IN USER06


bool encoder_update_user(uint8_t index, bool clockwise);
bool encoder_update_kb(uint8_t index, bool clockwise);
bool ergoslit_get_scroll_mode(void);
void ergoslit_set_scroll_mode(bool mode);
