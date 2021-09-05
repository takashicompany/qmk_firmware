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

/*
#define LAYOUT( \
    l01, l02, l03, l04, l05, l16, \
    l06, l07, l08, l09, l10, l17, \
    l11, l12, l13, l14, l15, l18  \
) { \
    { l01, l03, l05, l02, l04, l06}, \
    { l16, l08, l02, l06, l04, l05 }, \
    { l11, l12, l13, l14, l15, l18 }  \
}

{ l01, l04, l02, l05, l03, l06 }, \
*/


/*
#define LAYOUT( \
    l01, l02, l03, l04, l05, l16, \
    l06, l07, l08, l09, l10, l17, \
    l11, l12, l13, l14, l15, l18  \
) { \
    { l01, l02, l03, l04, l05, l16}, \
    { l06, l07, l08, l09, l10, l17 }, \
    { l11, l12, l13, l14, l15, l18 }  \
}
*/


/*
#define LAYOUT( \
    l01, l02, l03, l04, l05, l16, \
    l06, l07, l08, l09, l10, l17, \
    l11, l12, l13, l14, l15, l18  \
) { \
    { l01, l03, l05, l02, l04, l12 }, \
    { l16, l06, l08, l10, l07, l14}, \
    { l09, l17, l11, l13, l15, l18}  \
}

*/

/*
#define LAYOUT( \
    l01, l02, l03, l04, l05, l06, \
    l07, l08, l09, l10, l11, l12, \
    l13, l14, l15, l16, l17, l18  \
) { \
    { l01, l02, l03, l04, l05, l06 }, \
    { l07, l08, l09, l10, l11, l12 }, \
    { l13, l14, l15, l16, l17, l18 }  \
}
*/

#define LAYOUT( \
    l01, l02, l03, l04, l05, r01, r02, r03, r04, r05, \
    l06, l07, l08, l09, l10, r06, r07, r08, r09, r10, \
    l11, l12, l13, l14, l15, r11, r12, r13, r14, r15,\
    l16, l17, l18, r16, r17, r18  \
) { \
    { l01, l03, l05, l02, l04, l16, r01, r02, r03, r04, r05, r16 }, \
    { l06, l08, l10, l07, l09, l17, r06, r07, r08, r09, r10, r17 }, \
    { l11, l13, l15, l12, l14, l18, r11, r12, r13, r14, r15, r18 },  \
    { l01, l03, l05, l02, l04, l16, r01, r02, r03, r04, r05, r16 }, \
    { l06, l08, l10, l07, l09, l17, r06, r07, r08, r09, r10, r17 }, \
    { l11, l13, l15, l12, l14, l18, r11, r12, r13, r14, r15, r18}  \
}
