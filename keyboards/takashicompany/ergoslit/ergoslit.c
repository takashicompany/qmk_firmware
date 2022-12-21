// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef MEISHI_TRACKBALL

#include "quantum.h"
#include <math.h>
#include "ergoslit.h"
#include "wait.h"
#include "debug.h"
#include <stdio.h>



// Invert vertical scroll direction
#ifndef ERGOSLIT_SCROLL_INV_DEFAULT
#    define ERGOSLIT_SCROLL_INV_DEFAULT 1
#endif

#ifndef ERGOSLIT_CPI_OPTIONS
#    define ERGOSLIT_CPI_OPTIONS { 250, 500, 750, 1000, 1250 }
#    ifndef ERGOSLIT_CPI_DEFAULT
#       define ERGOSLIT_CPI_DEFAULT 3
#    endif
#endif
#ifndef ERGOSLIT_CPI_DEFAULT
#    define ERGOSLIT_CPI_DEFAULT 3
#endif

#ifndef ERGOSLIT_SCROLL_DIVIDERS
#    define ERGOSLIT_SCROLL_DIVIDERS { 1, 2, 3, 4, 5, 6 }
#    ifndef ERGOSLIT_SCROLL_DIV_DEFAULT
#       define ERGOSLIT_SCROLL_DIV_DEFAULT 4
#    endif
#endif
#ifndef ERGOSLIT_SCROLL_DIV_DEFAULT
#    define ERGOSLIT_SCROLL_DIV_DEFAULT 4
#endif


#ifndef ERGOSLIT_ROTATION_ANGLE
#    define ERGOSLIT_ROTATION_ANGLE { -60, -45, -30, -15, 0, 15, 30, 45, 60 }
#    ifndef ERGOSLIT_ROTATION_DEFAULT
#       define ERGOSLIT_ROTATION_DEFAULT 1
#    endif
#endif
#ifndef ERGOSLIT_ROTATION_DEFAULT
#    define ERGOSLIT_ROTATION_DEFAULT 1
#endif


ergoslit_config_t ergoslit_config;
uint16_t cpi_array[] = ERGOSLIT_CPI_OPTIONS;
uint16_t scrl_div_array[] = ERGOSLIT_SCROLL_DIVIDERS;
uint16_t angle_array[] = ERGOSLIT_ROTATION_ANGLE;
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define SCRL_DIV_SIZE (sizeof(scrl_div_array) / sizeof(uint16_t))
#define ANGLE_SIZE (sizeof(angle_array) / sizeof(uint16_t))


// Trackball State
bool     BurstState        = false;  // init burst state for Trackball module
uint16_t MotionStart       = 0;      // Timer for accel, 0 is resting state

// Scroll Accumulation
static int16_t h_acm       = 0;
static int16_t v_acm       = 0;


void pointing_device_init_kb(void) {
    // set the CPI.
    pointing_device_set_cpi(cpi_array[ergoslit_config.cpi_idx]);
}


report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    double rad = angle_array[ergoslit_config.rotation_angle] * (M_PI / 180) * -1;
    int8_t x_rev =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    int8_t y_rev =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    if (ergoslit_get_scroll_mode()) {
        // rock scroll direction
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        // accumulate scroll
        h_acm += x_rev * ergoslit_config.scrl_inv;
        v_acm += y_rev * ergoslit_config.scrl_inv * -1;

        int8_t h_rev = h_acm >> scrl_div_array[ergoslit_config.scrl_div];
        int8_t v_rev = v_acm >> scrl_div_array[ergoslit_config.scrl_div];

        // clear accumulated scroll on assignment

        if (h_rev != 0) {
            if (mouse_report.h + h_rev > 127) {
                h_rev = 127 - mouse_report.h;
            } else if (mouse_report.h + h_rev < -127) {
                h_rev = -127 - mouse_report.h;
            }
            mouse_report.h += h_rev;
            h_acm -= h_rev << scrl_div_array[ergoslit_config.scrl_div];
        }
        if (v_rev != 0) {
            if (mouse_report.v + v_rev > 127) {
                v_rev = 127 - mouse_report.v;
            } else if (mouse_report.v + v_rev < -127) {
                v_rev = -127 - mouse_report.v;
            }
            mouse_report.v += v_rev;
            v_acm -= v_rev << scrl_div_array[ergoslit_config.scrl_div];
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        mouse_report.x = x_rev;
        mouse_report.y = y_rev;
    }

    return pointing_device_task_user(mouse_report);
}



bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    
    if (!process_record_user(keycode, record)) return false;

    switch (keycode) {
#ifndef MOUSEKEY_ENABLE
        // process KC_MS_BTN1~8 by myself
        // See process_action() in quantum/action.c for details.
        case KC_MS_BTN1 ... KC_MS_BTN8: {
            extern void register_button(bool, enum mouse_buttons);
            register_button(record->event.pressed, MOUSE_BTN_MASK(keycode - KC_MS_BTN1));
            return false;
        }
#endif

    }

    if (keycode == CPI_SW && record->event.pressed) {
        ergoslit_config.cpi_idx = (ergoslit_config.cpi_idx + 1) % CPI_OPTION_SIZE;
        eeconfig_update_kb(ergoslit_config.raw);
        pointing_device_set_cpi(cpi_array[ergoslit_config.cpi_idx]);
    }

    if (keycode == SCRL_SW && record->event.pressed) {
        ergoslit_config.scrl_div = (ergoslit_config.scrl_div + 1) % SCRL_DIV_SIZE;
        eeconfig_update_kb(ergoslit_config.raw);
    }
    
    if (keycode == ROT_R15 && record->event.pressed) {
        ergoslit_config.rotation_angle = (ergoslit_config.rotation_angle + 1) % ANGLE_SIZE;
        eeconfig_update_kb(ergoslit_config.raw);
    }

    if (keycode == ROT_L15 && record->event.pressed) {
        ergoslit_config.rotation_angle = (ANGLE_SIZE + ergoslit_config.rotation_angle - 1) % ANGLE_SIZE;
        eeconfig_update_kb(ergoslit_config.raw);
    }

    if (keycode == SCRL_IN && record->event.pressed) {
        ergoslit_config.scrl_inv = - ergoslit_config.scrl_inv;
        eeconfig_update_kb(ergoslit_config.raw);
    }

    if (keycode == SCRL_TO && record->event.pressed) {
        { ergoslit_config.scrl_mode ^= 1; }
    }

    if (keycode == SCRL_MO) {
        { ergoslit_config.scrl_mode ^= 1; }
    }

    return true;
}


void eeconfig_init_kb(void) {
    ergoslit_config.cpi_idx = ERGOSLIT_CPI_DEFAULT;
    ergoslit_config.scrl_div = ERGOSLIT_SCROLL_DIV_DEFAULT;
    ergoslit_config.rotation_angle = ERGOSLIT_ROTATION_DEFAULT;
    ergoslit_config.scrl_inv = ERGOSLIT_SCROLL_INV_DEFAULT;
    ergoslit_config.scrl_mode = false;
    eeconfig_update_kb(ergoslit_config.raw);
    eeconfig_init_user();
}


void matrix_init_kb(void) {
    // is safe to just read CPI setting since matrix init
    // comes before pointing device init.
    ergoslit_config.raw = eeconfig_read_kb();
    if (ergoslit_config.cpi_idx > CPI_OPTION_SIZE) // || ergoslit_config.scrl_div > SCRL_DIV_SIZE || ergoslit_config.rotation_angle > ANGLE_SIZE)
    {
        eeconfig_init_kb();
    }
    matrix_init_user();
}


bool ergoslit_get_scroll_mode(void) {
    return ergoslit_config.scrl_mode;
}

void ergoslit_set_scroll_mode(bool mode) {
    ergoslit_config.scrl_mode = mode;
}

#endif