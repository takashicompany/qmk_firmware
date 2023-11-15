// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R,
        KC_A, KC_S, KC_D, KC_F,
        KC_V,
        KC_9, KC_0
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {

    keypos_t key;
    if (index==0) {
        
        if (clockwise) {
            key.row = 0;
            key.col = 10;
        } else {
            key.row = 0;
            key.col = 10;
        }

        tap_code(keymap_key_to_keycode(layer_switch_get_layer(key),key));
    }

    return false;
}
