#pragma once

#include "quantum.h"

#define LAYOUT( \
    KA1, KA2, KA3, \
    KB1, KB2, KB3, \
    KC1, KC2, KC3, \
	KD1, KD2, KD3 \
) \
{ \
    { KA1, KA2, KA3 }, \
    { KB1, KB2, KB3 }, \
    { KC1, KC2, KC3 }, \
	{ KD1, KD2, KD3 } \
}
