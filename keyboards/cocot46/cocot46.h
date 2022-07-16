/* Copyright 2021 aki27
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

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    ka00,   ka01,   ka02,   ka03,   ka04,   ka05,                            ka08,   ka09,   ka10,   ka11,   ka12,   ka13,  \
    kb00,   kb01,   kb02,   kb03,   kb04,   kb05,                            kb08,   kb09,   kb10,   kb11,   kb12,   kb13,  \
    kc00,   kc01,   kc02,   kc03,   kc04,   kc05,    ka06,           ka07,   kc08,   kc09,   kc10,   kc11,   kc12,   kc13,  \
                    kd02,   kd03,   kd04,   kd05,    kc06,   kb06,   kd06,   kd08,   kd09,   kd10,   kd11                   \
) { \
    { ka00,   ka01,   ka02,   ka03,   ka04,   ka05,   ka06,   ka13,   ka12,   ka11,   ka10,   ka09,   ka08,   ka07   }, \
    { kb00,   kb01,   kb02,   kb03,   kb04,   kb05,   kb06,   kb13,   kb12,   kb11,   kb10,   kb09,   kb08,   KC_NO  }, \
    { kc00,   kc01,   kc02,   kc03,   kc04,   kc05,   kc06,   kc13,   kc12,   kc11,   kc10,   kc09,   kc08,   KC_NO  }, \
    { KC_NO,  KC_NO,  kd02,   kd03,   kd04,   kd05,   kd06,   KC_NO,  KC_NO,  kd11,   kd10,   kd09,   kd08,   KC_NO  }  \
}

