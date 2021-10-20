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
#define LAYOUT( \
    k001, k002, k003, k004, k005, k006, k007, k008, \
    k201, k009, k010, k011, k012, k013, k901,       \
    k301, k014, k015, k016, k017, k018,             \
    k401, k019, k020, k021, k022, k023, k024,       \
    k025, k101, k102, k026, k103, k104, k027        \
) { \
    { k001, k002, k003, k004, k005, k006, k007 },   \
    { k201, k009, k010, k011, k012, k013, k008 },   \
    { k301, k014, k015, k016, k017, k018, k901 },   \
    { k401, k019, k020, k021, k022, k023, k024 },   \
    { k025, k101, k102, k026, k103, k104, k027 }    \
}