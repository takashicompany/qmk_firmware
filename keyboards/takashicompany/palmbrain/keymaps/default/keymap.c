// Copyright 2025 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_split_3x5_2(
        LT(4, KC_Q), KC_W, KC_E, LT(3, KC_R), KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, LT(4, KC_D), KC_F, KC_G, KC_H, KC_J, LT(3, KC_K), KC_L, KC_ENT,
        LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC,
        LALT_T(KC_LNG2), LSFT_T(KC_TAB), LT(2, KC_SPC), LT(1, KC_LNG1)
    ),
    
    [1] = LAYOUT_split_3x5_2(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        LCTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_INT1, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_INT3,
        LSFT_T(KC_PLUS), KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_INT1), KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_INT3),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    [2] = LAYOUT_split_3x5_2(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, LGUI(KC_INT3),
        KC_PLUS, KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_INT1), KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_INT3),
        KC_LSFT, KC_LGUI, KC_LALT, KC_LNG2, KC_LSFT, KC_SPC, KC_LNG1, KC_TRNS, KC_TRNS, KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    [3] = LAYOUT_split_3x5_2(
        KC_ESC, KC_TAB, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LNG2, KC_TRNS, KC_NO, KC_LNG1, KC_NO, KC_NO, KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ), 
    
    [4] = LAYOUT_split_3x5_2(
        KC_NO, KC_TAB, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, MO(5), MO(6),
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    [5] = LAYOUT_split_3x5_2(
        UG_TOGG, UG_NEXT, UG_HUEU, UG_SATU, UG_VALU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
