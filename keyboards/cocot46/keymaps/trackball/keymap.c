/* Copyright 2021 aki27
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <math.h>

#include "paw3204.h"
#include "pointing_device.h"

bool isScrollMode;

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY = 0,
    _LOWER = 1,
    _RAISE = 2,
    _ADJUST = 3,
};


#define LW_MHEN LT(1,KC_MHEN)  // lower
#define RS_HENK LT(2,KC_HENK)  // raise


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                              KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                              KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_MS_BTN1,               KC_MS_BTN2,      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
                        KC_LGUI, KC_LALT, LW_MHEN,  KC_SPC,      KC_PGUP,  KC_MS_BTN3,   KC_PGDOWN,    KC_ENT, RS_HENK, KC_BSPC,  KC_DEL
                                                    //`-----------------------'  `-----------------------'
    ),
    [1] = LAYOUT(
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                                           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_COLN, KC_DQUO,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
      KC_LSFT,  KC_GRV, KC_TILD, KC_NUBS, KC_PIPE, XXXXXXX,   KC_MS_BTN4,               KC_MS_BTN5,    KC_EQL, KC_PLUS, KC_LABK, KC_RABK, KC_QUES, KC_UNDS,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
                        KC_LGUI, KC_LALT, KC_TRNS,  KC_SPC,      KC_PGUP,  KC_MS_BTN3,   KC_PGDOWN,    KC_ENT,   TT(3), KC_BSPC,  KC_DEL
                                                    //`-----------------------'  `-----------------------'
    ),
    [2] = LAYOUT(
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                              KC_6,    KC_7,    KC_8,    KC_9,   KC_0,  KC_BSPC,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
       KC_TAB,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                           KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
      KC_LSFT,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_MS_BTN4,               KC_MS_BTN5,   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
                        KC_LGUI, KC_LALT,   TT(3),  KC_SPC,      KC_PGUP,  KC_MS_BTN3,   KC_PGDOWN,    KC_ENT, KC_TRNS, KC_BSPC,  KC_DEL
                                                    //`-----------------------'  `-----------------------'
    ),
    [3] = LAYOUT(
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           RGB_TOG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           RGB_MOD,   RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_MS_BTN1,               KC_MS_BTN2,  RGB_RMOD,   RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|                                       |-------------------------------------------------------|
                        XXXXXXX, XXXXXXX, KC_TRNS, XXXXXXX,      KC_PGUP,  KC_MS_BTN3,   KC_PGDOWN,   XXXXXXX,   KC_TRNS, XXXXXXX, XXXXXXX
                                                    //`-----------------------'  `-----------------------'
    )
};



keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 3, .col = 6},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 2, .col = 6},
    .pressed = false
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    }

    return true;
}


void matrix_init_user(void) {
    init_paw3204();
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;

    report_mouse_t mouse_rep = pointing_device_get_report();

    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;
        int8_t r_x, r_y;

        read_paw3204(&stat, &x, &y);

        // 45-degree angle
        int8_t deg = 45;
        double rad = deg * (M_PI / 180);
        r_x =  + x * cos(rad) + y * sin(rad);
        r_y =  - x * sin(rad) + y * cos(rad);
        // int8_t degree = -45;
        // r_x =  - x * cos(rad) - y * sin(rad);
        // r_y =  + x * sin(rad) - y * cos(rad);
        /* normal angle
        r_x = y;
        r_y = x;
        */

        if (isScrollMode) {
            if (cnt % 5 == 0) {
                mouse_rep.v = -r_y;
                mouse_rep.h = r_x;
            }
        } else {
            mouse_rep.x = r_x;
            mouse_rep.y = r_y;
        }

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
    case _RAISE:
        isScrollMode = true;
        break;
    default:
        isScrollMode = false;
        break;
    }
  return state;
}
