// #include <stdio.h>
#include "quantum.h"
#include "ergomaneuver.h"
#include "custom_joystick.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    
    switch (keycode) {
        case KC_OLED:
            break;

        case KC_JS_INC:
            if  (record->event.pressed) {
                joystick_ratio = joystick_ratio + 10;
            }
            break;

        case KC_JS_DEC:
            if  (record->event.pressed) {
                joystick_ratio = joystick_ratio - 10;
            }
            break;

        case KC_SAVE:
            break;

        default:
            return process_record_user(keycode, record);
    }

    return true;
}

bool oled_task_kb(void) {
    char buf[16];
    itoa(joystick_ratio, buf, 10);  // int16_t to char
    oled_write_P(PSTR("Joy Stick:"), false);
    oled_write(buf, false);
    oled_write("   ", false);
    return false;
}


