// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_ENT,
        KC_LCTL, KC_A, KC_S, KC_RSFT
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
