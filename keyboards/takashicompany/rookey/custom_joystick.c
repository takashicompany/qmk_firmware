
#include "custom_joystick.h"


#include QMK_KEYBOARD_H

#include "analog.h"
#include "gpio.h"
#include "wait.h"
#include "timer.h"
#include <stdlib.h>
#include "print.h"

int16_t xOrigin, yOrigin;
uint16_t lastCursor = 0;

int16_t axisCoordinate_custom(pin_t pin, uint16_t origin) {
    int8_t  direction;              // 符号
    int16_t distanceFromOrigin;     // 原点からの距離。負数にはならない
    // int16_t range;                  // 原点からの最大の移動量

    int16_t position = analogReadPin(pin);  // 多分だけどデフォルトだと512が中心に来るようになっている

    // uprintf("position %d\n", position);

    if (origin == position) {   // 原点と同じなら0とする
        return 0;
    } else if (origin > position) {     // 原点よりマイナス方向の場合の処理
         distanceFromOrigin = origin - position;
        // range              = origin - minAxisValue;
        direction          = -1;
    } else {                            // 原点よりプラス方向の処理
        distanceFromOrigin = position - origin;
        // range              = maxAxisValue - origin;
        direction          = 1;
    }
    
    return distanceFromOrigin * direction;

    // float   percent    = (float)distanceFromOrigin / range; // 原点からの距離の割合。 0~1の範囲に収まるはず。
    // int16_t coordinate = (int16_t)(percent * 100);          // coordinateは座標という英単語。0~1を100%表記に直している。
    // if (coordinate < 0) {                                   // この分岐に入ることってあるのか？
    //     return 0;
    // } else if (coordinate > 100) {
    //     return 100 * direction;                             // 100%を超える場合は-100か+100を返す
    // } else {
    //     return coordinate * direction;                      // 100%を超えない場合は-100　~　+100の間で返す
    // }
}

void           pointing_device_driver_init(void) {
        xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);
}
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {


    if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {    // 多分、指定のミリ秒経過したかを見て処理を走らせている
        lastCursor = timer_read();
        mouse_report.x = axisCoordinate_custom(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin) / 100;
        mouse_report.y = axisCoordinate_custom(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin) / 100;
    }
// #ifdef ANALOG_JOYSTICK_CLICK_PIN
//     report.button = !readPin(ANALOG_JOYSTICK_CLICK_PIN);
// #endif
//     return report;
// }
    return mouse_report;
}

uint16_t       pointing_device_driver_get_cpi(void) { return 0; }
void           pointing_device_driver_set_cpi(uint16_t cpi) {}



