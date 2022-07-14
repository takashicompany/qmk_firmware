// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "pointing_device.h"
#include "paw3204.h"

enum custom_keycodes {
    KC_MY_BTN1 = SAFE_RANGE,
    KC_MY_BTN2,
    KC_MY_BTN3,
    KC_MY_SCR,
};

// BLE Micro Pro用の記述 ここから
/*
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"

const key_string_map_t custom_keys_user = {.start_kc = KC_MY_BTN1, .end_kc = KC_MY_SCR, .key_strings = "MY_BTN1\0MY_BTN2\0MY_BTN3\0MY_SCR\0"};
uint32_t keymaps_len() { return 38; }
*/
// BLE Micro Pro用の記述 ここまで

report_mouse_t mouse_rep;

enum click_state {
    NONE = 0,
    WAITING,    // マウスレイヤーが有効になるのを待つ
    CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる
    CLICKING,   // クリックをしている
    SCROLLING   // スクロール中
};

enum click_state state;     // 現在のクリック入力受付の状態
uint16_t click_timer;       // タイマー。状態に応じて時間で判定する

uint16_t to_clickable_time = 10;   // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる
uint16_t to_reset_time = 1000; // この秒数(千分の一秒)、CLICKABLE状態ならクリックレイヤーが無効になる

uint16_t click_layer = 9;   // マウス入力が可能になった際に有効になるレイヤー

int16_t scroll_v_counter;   // 垂直スクロールの入力をカウントする
int16_t scroll_h_counter;   // 水平スクロールの入力をカウントする

int16_t scroll_v_threshold = 30;    // この閾値を超える度に垂直スクロールが実行される
int16_t scroll_h_threshold = 30;    // この閾値を超える度に水平スクロールが実行される

int16_t after_click_lock_movement = 0;      // クリック入力後の移動量を測定する変数


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        LT(7, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_A, KC_S, LT(6, KC_D), KC_F, KC_G, KC_H, KC_J, LT(6, KC_K), KC_L, KC_ENT, 
        LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, 
        KC_LCTL, KC_LGUI, LALT_T(KC_LANG2), LSFT_T(KC_TAB), LT(2, KC_SPC), LT(1, KC_LANG1), KC_PGUP, KC_PGDN
    ),
    
    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        LCTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_RO, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_JYEN, 
        LSFT_T(KC_PLUS), KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_RO), KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_JYEN), 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, LGUI(KC_JYEN), 
        KC_PLUS, KC_LCBR, KC_QUES, KC_UNDS, LSFT(KC_RO), KC_COLN, KC_DQUO, KC_RCBR, LSFT(KC_NUHS), LSFT(KC_JYEN), 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_LSFT, KC_SPC, KC_LANG1, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        LT(7, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_A, KC_S, LT(6, KC_D), KC_F, KC_G, KC_H, KC_J, LT(6, KC_K), KC_L, KC_ENT, 
        LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, 
        KC_LCTL, KC_LGUI, LALT_T(KC_LANG2), LSFT_T(KC_TAB), LT(5, KC_SPC), LT(4, KC_LANG1), KC_PGUP, KC_PGDN
    ),
        
    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        KC_CIRC, KC_AT, KC_SLSH, KC_MINS, KC_UNDS, KC_SCLN, KC_COLN, KC_LBRC, KC_RBRC, KC_JYEN, 
        LT(5, KC_TILD), KC_GRV, KC_QUES, KC_EQL, KC_UNDS, KC_PLUS, KC_ASTR, KC_LCBR, KC_RCBR, KC_PIPE, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_EXLM, KC_DQUO, KC_HASH, KC_DLR, KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN, KC_BSLS, 
        KC_TILD, KC_GRV, KC_QUES, KC_EQL, KC_UNDS, KC_PLUS, KC_ASTR, KC_LCBR, KC_RCBR, KC_PIPE, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_LSFT, KC_SPC, KC_LANG1, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, 
        KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_TRNS, KC_NO, KC_LANG1, KC_NO, KC_NO, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ), 
    
    LAYOUT(
        KC_NO, KC_TAB, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, MO(8), MO(9), 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    
    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, DF(0), DF(3), 
        RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ), 
    
    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MY_BTN1, KC_MY_SCR, KC_MY_BTN2, KC_MY_BTN3, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_MY_SCR, KC_MY_BTN1, KC_TRNS, KC_MY_SCR, KC_MY_BTN2, KC_MY_BTN3, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// クリック用のレイヤーを有効にする
void enable_click_layer(void) {
    layer_on(click_layer);
    click_timer = timer_read();
    state = CLICKABLE;
}

// クリック用のレイヤーを無効にする
void disable_click_layer(void) {
    state = NONE;
    layer_off(click_layer);
    scroll_v_counter = 0;
    scroll_h_counter = 0;
}

// 自前の絶対数を返す関数
int16_t my_abs(int16_t num) {
    if (num < 0) {
        num = -num;
    }

    return num;
}

// 現在クリックが可能な状態か
bool is_clickable_mode(void) {
    return state == CLICKABLE || state == CLICKING || state == SCROLLING;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
    // BLE Micro Pro用の実装
    /*
    bool continue_process = process_record_user_bmp(keycode, record);
    if (continue_process == false)
    {
        return false;
    }
    */
    
    switch (keycode) {
        case KC_MY_BTN1:
        case KC_MY_BTN2:
        case KC_MY_BTN3:
        {
            report_mouse_t currentReport = pointing_device_get_report();

            // どこのビットを対象にするか
            uint8_t btn = 1 << (keycode - KC_MY_BTN1);
            
            if (record->event.pressed) {
                // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
                currentReport.buttons |= btn;
                mouse_rep.buttons |= btn;
                state = CLICKING;
                after_click_lock_movement = 30;
            } else {
                // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
                currentReport.buttons &= ~btn;
                mouse_rep.buttons &= ~btn;
                enable_click_layer();
            }

            pointing_device_set_report(currentReport);
            return false;
        }

        case KC_MY_SCR:
            if (record->event.pressed) {
                state = SCROLLING;
            } else {
                // disable_click_layer(); // スクロールキーを離したらクリックレイヤーを無効にする

                enable_click_layer();   // スクロールキーを離した時に再度クリックレイヤーを有効にする
            }
         return false;

         default:
            if  (record->event.pressed) {
                disable_click_layer();
            }
        
    }
   
    return true;
}

void matrix_init_user() { init_paw3204(); }

void matrix_scan_user() {
    static int  cnt;
    static bool paw_ready;
    if (cnt++ % 50 == 0) {
        
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            //dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            //dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
        
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;

        read_paw3204(&stat, &x, &y);
        //mouse_rep.buttons = 0;    // ボタンの状態はここでは上書きしない       
        mouse_rep.h       = 0;
        mouse_rep.v       = 0;
        mouse_rep.x       = y;
        mouse_rep.y       = -x;

        if (stat & 0x80) {
            // dprintf("x:%4d y:%4d \n", mouse_rep.x,  mouse_rep.y);

            switch (state) {
                case CLICKABLE:
                    click_timer = timer_read();
                    break;

                case CLICKING:
                    after_click_lock_movement -= my_abs(mouse_rep.x) + my_abs(mouse_rep.y);

                    if (after_click_lock_movement > 0) {
                        mouse_rep.x = 0;
                        mouse_rep.y = 0;
                    }

                    break;

                case SCROLLING:
                {
                    int8_t rep_v = 0;
                    int8_t rep_h = 0;

                    // 垂直スクロールの方の感度を高める
                    if (my_abs(mouse_rep.y) * 2 > my_abs(mouse_rep.x)) {

                        scroll_v_counter += mouse_rep.y;
                        while (my_abs(scroll_v_counter) > scroll_v_threshold) {
                            if (scroll_v_counter < 0) {
                                //tap_code16(KC_WH_U);
                                scroll_v_counter += scroll_v_threshold;
                                rep_v += scroll_v_threshold;
                            } else {
                                //tap_code16(KC_WH_D);
                                scroll_v_counter -= scroll_v_threshold;
                                rep_v -= scroll_v_threshold;
                            }
                            
                        }
                    } else {

                        scroll_h_counter += mouse_rep.x;

                        while (my_abs(scroll_h_counter) > scroll_h_threshold) {
                            if (scroll_h_counter < 0) {
                                // tap_code16(KC_WH_L);
                                scroll_h_counter += scroll_h_threshold;
                                rep_h += scroll_h_threshold;
                            } else {
                                // tap_code16(KC_WH_R);
                                scroll_h_counter -= scroll_h_threshold;
                                rep_h -= scroll_h_threshold;
                            }
                        }
                    }

                    mouse_rep.h = rep_h / scroll_h_threshold;
                    mouse_rep.v = -rep_v / scroll_v_threshold;
                    mouse_rep.x = 0;
                    mouse_rep.y = 0;
                }
                    break;

                case WAITING:
                    if (timer_elapsed(click_timer) > to_clickable_time) {
                        enable_click_layer();
                    }
                    break;

                default:
                    click_timer = timer_read();
                    state = WAITING;
            }

            pointing_device_set_report(mouse_rep);
        }
        else
        {
            switch (state) {
                case CLICKING:
                case SCROLLING:

                    break;

                case CLICKABLE:
                    if (timer_elapsed(click_timer) > to_reset_time) {
                        disable_click_layer();
                    }
                    break;

                default:
                    state = NONE;
            }
        }
    }
}