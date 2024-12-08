// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │ K │ L │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x12(
        KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L,
        KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R,
        KC_S, KC_T, KC_U, KC_V, KC_W, KC_X, KC_S, KC_T, KC_U, KC_V, KC_W, KC_X
    )
};
