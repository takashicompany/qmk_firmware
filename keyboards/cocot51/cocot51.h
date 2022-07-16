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
    k00, k70, k01, k71, k02, k72,      k03, k73, k04, k74, k05, k75, \
    k10, k60, k11, k61, k12, k62,      k13, k63, k14, k64, k15, k65, \
    k20, k50, k21, k51, k22, k52,      k23, k53, k24, k54, k25, k55, \
    k30, k40, k31, k41, k32, k42,      k33, k43, k34, k44, k35, k45, \
                             k06, k16, k26 \
) { \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, KC_NO }, \
    { k40, k41, k42, k43, k44, k45, KC_NO }, \
    { k50, k51, k52, k53, k54, k55, KC_NO }, \
    { k60, k61, k62, k63, k64, k65, KC_NO }, \
    { k70, k71, k72, k73, k74, k75, KC_NO }, \
}
