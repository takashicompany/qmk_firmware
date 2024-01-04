/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "analog_joystick.h"
#include "analog.h"
#include "gpio.h"
#include "wait.h"
#include "timer.h"
#include <stdlib.h>
#include "print.h"

// Set Parameters
uint16_t minAxisValue = ANALOG_JOYSTICK_AXIS_MIN;
uint16_t maxAxisValue = ANALOG_JOYSTICK_AXIS_MAX;

uint8_t maxCursorSpeed = ANALOG_JOYSTICK_SPEED_MAX;
uint8_t speedRegulator = ANALOG_JOYSTICK_SPEED_REGULATOR; // Lower Values Create Faster Movement

int16_t xOrigin, yOrigin;

uint16_t lastCursor = 0;

int16_t axisCoordinate(pin_t pin, uint16_t origin) {
    int8_t  direction;              // 符号
    int16_t distanceFromOrigin;     // 原点からの距離。負数にはならない
    int16_t range;                  // 原点からの最大の移動量

    int16_t position = analogReadPin(pin);  // 多分だけどデフォルトだと512が中心に来るようになっている

    // uprintf("position %d\n", position);

    if (origin == position) {   // 原点と同じなら0とする
        return 0;
    } else if (origin > position) {     // 原点よりマイナス方向の場合の処理
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue;
        direction          = -1;
    } else {                            // 原点よりプラス方向の処理
        distanceFromOrigin = position - origin;
        range              = maxAxisValue - origin;
        direction          = 1;
    }

    float   percent    = (float)distanceFromOrigin / range; // 原点からの距離の割合。 0~1の範囲に収まるはず。
    int16_t coordinate = (int16_t)(percent * 100);          // coordinateは座標という英単語。0~1を100%表記に直している。
    if (coordinate < 0) {                                   // この分岐に入ることってあるのか？
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;                             // 100%を超える場合は-100か+100を返す
    } else {
        return coordinate * direction;                      // 100%を超えない場合は-100　~　+100の間で返す
    }
}

int8_t axisToMouseComponent(pin_t pin, int16_t origin, uint8_t maxSpeed) {
    int16_t coordinate = axisCoordinate(pin, origin);
    if (coordinate != 0) {
        float percent = (float)coordinate / 100;    // なんでここでまた0~1に戻しているんだろう
        return percent * maxCursorSpeed * (abs(coordinate) / speedRegulator);   // (0~1) x 2 x (0~100) / 20
    } else {
        return 0;
    }
}

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

report_analog_joystick_t analog_joystick_read(void) {
    report_analog_joystick_t report = {0};

    if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {    // 多分、指定のミリ秒経過したかを見て処理を走らせている
        lastCursor = timer_read();
        report.x   = axisToMouseComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, maxCursorSpeed);
        report.y   = axisToMouseComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, maxCursorSpeed);
        // report.x = axisCoordinate_custom(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin) / 100;
        // report.y = axisCoordinate_custom(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin) / 100;
    }
#ifdef ANALOG_JOYSTICK_CLICK_PIN
    report.button = !readPin(ANALOG_JOYSTICK_CLICK_PIN);
#endif
    return report;
}

void analog_joystick_init(void) {
#ifdef ANALOG_JOYSTICK_CLICK_PIN
    setPinInputHigh(ANALOG_JOYSTICK_CLICK_PIN);
#endif
    // Account for drift
    xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);
}
