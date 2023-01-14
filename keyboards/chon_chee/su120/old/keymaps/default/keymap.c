#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    LAYOUT(
        KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
        KC_1, KC_2, KC_Q, KC_W, KC_E, KC_R, KC_T,
        KC_3, KC_4, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_5, KC_6, KC_Z, KC_X, KC_C, KC_V, KC_B,
        KC_7, KC_8, KC_9, KC_0, KC_1, KC_2, KC_3
    )
};
