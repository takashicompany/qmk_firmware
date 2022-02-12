// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "paw3204.h"
#include "pointing_device.h"

report_mouse_t mouse_rep;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        LT(2, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, LT(2, KC_D), KC_F, KC_G, KC_H, KC_J, LT(2, KC_K), KC_L, KC_ENT,
        SFT_T(KC_Z), GUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, CTL_T(KC_DOT), KC_BSPC,
        KC_LCTL, KC_LGUI, ALT_T(KC_LANG2), SFT_T(KC_TAB), KC_SPC, LT(1, KC_LANG1), KC_RALT, KC_RGUI),

    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        CTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_RO, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_JYEN,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_LSFT, KC_SPC, KC_LANG1, KC_TRNS, KC_TRNS, KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO,
        KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_TRNS, KC_TRNS, KC_LANG1, KC_NO, MO(3), KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,
        RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_M_T, KC_F11, KC_F12, KC_CAPS, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

void matrix_init_user() { init_paw3204(); }

void matrix_scan_user() {
    static int  cnt;
    static bool paw_ready;
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

        read_paw3204(&stat, &x, &y);
        mouse_rep.buttons = 0;
        mouse_rep.h       = 0;
        mouse_rep.v       = 0;
        mouse_rep.x       = y;
        mouse_rep.y       = -x;

        dprintf("stat:0x%02x x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
}