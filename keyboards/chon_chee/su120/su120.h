// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    l01, l02, l03, l04, l05, l06, l07, \
    l08, l09, l10, l11, l12, l13, l14, \
    l15, l16, l17, l18, l19, l20, l21, \
    l22, l23, l24, l25, l26, l27, l28, \
    l29, l30, l31, l32, l33, l34, l35  \

) { \
    { l01, l02, l03, l04, l05, l06, l07 }, \
    { l08, l09, l10, l11, l12, l13, l14 }, \
    { l15, l16, l17, l18, l19, l20, l21 }, \
    { l22, l23, l24, l25, l26, l27, l28 }, \
    { l29, l30, l31, l32, l33, l34, l35 }  \
}
