#pragma once

#include QMK_KEYBOARD_H

enum {
    UM_LNX = SAFE_RANGE,
    UM_MAC,
    UM_WCP,
    UM_TGL,
};

bool set_unicode_mode(os_variant_t os);
bool process_unicode_mode(uint16_t keycode);
bool process_special_char(uint16_t keycode);
