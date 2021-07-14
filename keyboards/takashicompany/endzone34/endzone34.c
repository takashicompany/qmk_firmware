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

#include "endzone34.h"
#include <stdio.h>

uint16_t press_count = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     // キーが押されたら、カウンターをインクリメントする
    if (record->event.pressed) {
        press_count++;
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

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