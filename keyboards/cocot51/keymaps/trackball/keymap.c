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

#include "paw3204.h"
#include "pointing_device.h"
// extern keymap_config_t keymap_config;
// extern uint8_t is_master;
bool isScrollMode;

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY = 0,
    _LOWER = 1,
    _RAISE = 2,
    _ADJUST = 3,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MBTN1,
  MBTN2,
  MBTN3,
  SCRL
};


#define KC_L_MHEN LT(1,KC_MHEN)  // lower
#define KC_R_HENK LT(2,KC_HENK)  // raise



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
  //,-------------------------------------------------------.            ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,      KC_R,    KC_T,               KC_Y,      KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
       KC_TAB,    KC_A,    KC_S,    KC_D,      KC_F,    KC_G,               KC_H,      KC_J,    KC_K,    KC_L, KC_SCLN, KC_AMPR,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,      KC_V,    KC_B,               KC_N,      KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, KC_L_MHEN,  KC_SPC,             KC_ENT, KC_R_HENK, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
                                                  KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2
                                      //`-----------------------'  `-----------------------'
    ),
    [1] = LAYOUT(
  //,-------------------------------------------------------.            ,-----------------------------------------------------.
       KC_ESC, KC_EXLM, KC_LBRC, KC_HASH,    KC_DLR, KC_PERC,             KC_EQL,   KC_CIRC, KC_DQUO, KC_ASTR, KC_LPRN, KC_BSPC,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,            KC_RCBR,   KC_PIPE, KC_RBRC, KC_BSLS, KC_QUOT,   KC_AT,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      KC_LSFT, KC_LCBR, KC_PLUS,   KC_RO,S(KC_JYEN), XXXXXXX,            KC_UNDS,   KC_COLN,   KC_LT,   KC_GT, KC_QUES, S(KC_RO),
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      KC_LCTL, KC_LGUI, KC_LALT,  KC_DEL, KC_L_MHEN,  KC_SPC,             KC_ENT,     TT(3), KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
                                                  KC_MS_BTN4, KC_MS_BTN3, KC_MS_BTN5
                                      //`-----------------------'  `-----------------------'
    ),
    [2] = LAYOUT(
  //,-------------------------------------------------------.            ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,      KC_4,    KC_5,               KC_6,      KC_7,    KC_8,    KC_9,   KC_0,  KC_BSPC,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
       KC_TAB,   KC_F1,   KC_F2,   KC_F3,     KC_F4,   KC_F5,             KC_APP,     KC_UP,S(KC_RO), KC_UNDS, KC_DQUO, KC_COLN,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      KC_LSFT,   KC_F6,   KC_F7,   KC_F8,     KC_F9,  KC_F10,            KC_LEFT,   KC_DOWN, KC_RGHT,  KC_DOT, KC_SLSH, KC_MINS,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      KC_LCTL, KC_LGUI, KC_LALT,  KC_DEL,     TT(3),  KC_SPC,             KC_ENT,   KC_TRNS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
                                                  KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2
                                      //`-----------------------'  `-----------------------'
    ),
    [3] = LAYOUT(
  //,-------------------------------------------------------.            ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,            RGB_TOG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,            RGB_MOD,   RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,           RGB_RMOD,   RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,            XXXXXXX,   KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|-------------------------------------------------------|            |-----------------------------------------------------|
                                                     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`-----------------------'  `-----------------------'
    )
};

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};

  switch (keycode) {
    case MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      return false;
    case MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      return false;
    case MBTN3:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN3;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN3;
      }
      pointing_device_set_report(currentReport);
      return false;
    case SCRL:
      if (record->event.pressed) {
        isScrollMode = true;
        dprint("scroll ON\n");
      }
      else {
        isScrollMode = false;
        dprint("scroll OFF\n");
      }
      return false;
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
        int8_t degree = 45;
        r_x =  x * cos(degree) + y * sin(degree);
        r_y = -x * sin(degree) + y * cos(degree);
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
        isScrollMode = true;
        break;
    case _RAISE:
        isScrollMode = true;
        break;
    default:
        isScrollMode = false;
        break;
    }
  return state;
}
