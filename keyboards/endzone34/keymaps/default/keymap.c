/* Copyright 2021 takashicompany
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        LT(3, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_A, KC_S, LT(2, KC_D), KC_F, KC_G, KC_H, KC_J, LT(2, KC_K), KC_L, KC_ENT, 
        SFT_T(KC_Z), GUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, CTL_T(KC_DOT), KC_BSPC, 
        ALT_T(KC_LANG2), SFT_T(KC_TAB), KC_SPC, LT(1, KC_LANG1)),

    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        KC_EQL, KC_LBRC, KC_SLSH, KC_MINS, KC_RO, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_JYEN, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_LSFT, KC_SPC, KC_LANG1, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, 
        KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_TRNS, KC_NO, KC_LANG1, KC_NO, KC_NO, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    LAYOUT(
        KC_NO, KC_TAB, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 
        KC_NO, KC_NO,KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, MO(4), MO(5), 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_M_T, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

// キーを押した回数を格納する変数
static uint16_t press_count = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

     // キーが押されたら、カウンターをインクリメントする
    if (record->event.pressed) {
        press_count++;
    }

    return true;
}

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    
    static const char PROGMEM my_logo[] = {
        // Paste the code from the previous step below this line!
        0x00, 0x00, 0x00, 0xff, 0x01, 0x01, 0x39, 0x29, 0x29, 0x29, 0x29, 0x29, 0xe9, 0x0f, 0x00, 0x00, 
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf8, 0x08, 0xf8, 0x00, 0x00, 0x00, 0x00, 
        0x80, 0x80, 0x80, 0xbf, 0xa0, 0xa0, 0xa7, 0xa5, 0xa5, 0xa5, 0xa5, 0x25, 0x25, 0x3c, 0x00, 0x1f, 
        0x20, 0x3e, 0x02, 0x3e, 0x20, 0x1f, 0x20, 0x2e, 0x2a, 0x2e, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 
        0x87, 0x44, 0x24, 0x14, 0x0c, 0x00, 0xc0, 0xa0, 0x90, 0x88, 0x87, 0x00, 0xe0, 0x10, 0xd0, 0x50, 
        0xd0, 0x10, 0xe0, 0x10, 0xd0, 0x50, 0xd0, 0x10, 0xe0, 0x10, 0xd0, 0x50, 0x50, 0x10, 0xf0, 0x00, 
        0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x03, 0x04, 0x05, 0x05, 
        0x05, 0x04, 0x03, 0x04, 0x07, 0x00, 0x07, 0x04, 0x03, 0x04, 0x05, 0x05, 0x05, 0x05, 0x07, 0x00
    };

    oled_write_raw_P(my_logo, sizeof(my_logo));
}

void oled_task_user(void) {

    // ロゴを表示
    render_logo();

    // カーソルを移動
    oled_set_cursor(0, 5);

     // 現在のレイヤーを表示する
    oled_write_ln_P(PSTR("Layer"), false);
    char layer_str[12];
    snprintf(layer_str, sizeof(layer_str), "%d", get_highest_layer(layer_state));
    oled_write_ln(layer_str, false);

    // 改行を入れる
    oled_write_ln_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(" "), false);

    // キーを押した回数を表示する
    oled_write_ln_P(PSTR("Count"), false);
    char count_str[24];
    snprintf(count_str, sizeof(count_str), "%d", press_count);
    oled_write_ln(count_str, false);
    
}
#endif