// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define KCN KC_NO

#define LAYOUT( \
                   l04, l05, l06, l07,     r01, r02, r03, r04,                \
    l08, l09, l10, l11, l12, l13, l14,     r08, r09, r10, r11, r12, r13, r14, \
    l15, l16, l17, l18, l19, l20, l21,     r15, r16, r17, r18, r19, r20, r21, \
    l22, l23, l24, l25, l26, l27, l28,     r22, r23, r24, r25, r26, r27,      \
    l29,      l31,      l33,      l35,          r30,      r32, r33, r34, r35  \
) { \
    { KCN, KCN, KCN, l04, l05, l06, l07 }, \
    { l08, l09, l10, l11, l12, l13, l14 }, \
    { l15, l16, l17, l18, l19, l20, l21 }, \
    { l22, l23, l24, l25, l26, l27, l28 }, \
    { l29, KCN, l31, KCN, l33, KCN, l35 }, \
    { r01, r02, r03, r04, KCN, KCN, KCN }, \
    { r08, r09, r10, r11, r12, r13, r14 }, \
    { r15, r16, r17, r18, r19, r20, r21 }, \
    { r22, r23, r24, r25, r26, r27, KCN }, \
    { KCN, r30, KCN, r32, r33, r34, r35 }  \
}
