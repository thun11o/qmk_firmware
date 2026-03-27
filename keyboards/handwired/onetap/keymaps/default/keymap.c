// // Copyright 2025 QMK
// // SPDX-License-Identifier: GPL-2.0-or-later
//
#include QMK_KEYBOARD_H

#include "../../tap_dance.h"

tap_dance_action_t tap_dance_actions[] = {
    [OSLMO1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_oslmo1_finished, NULL),
    [OSLMO2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_oslmo2_finished, NULL),
    [TABESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
    [ALTLR]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_RALT),
};

static uint8_t keys_down = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed) {
        keys_down++;
    }
    else {
        if(oslmo1 == OSLMO_HELD && keycode == TD(OSLMO1)) {
            layer_off(1);
            oslmo1 = OSLMO_NONE;
        }

        if(oslmo2 == OSLMO_HELD && keycode == TD(OSLMO2)) {
            layer_off(2);
            oslmo2 = OSLMO_NONE;
        }

        if(keys_down > 0) {
            keys_down--;
        }
    }

    if(keys_down == 0) {
        if(oslmo1 == OSLMO_ONESHOT && keycode != TD(OSLMO1)) {
            layer_off(1);
            oslmo1 = OSLMO_NONE;
        }

        if(oslmo2 == OSLMO_ONESHOT && keycode != TD(OSLMO2)) {
            layer_off(2);
            oslmo2 = OSLMO_NONE;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_4(
        KC_TAB,     KC_Q,    KC_W,    KC_E,       KC_R,       KC_T,           KC_Y,    KC_U,   KC_I,     KC_O,    KC_P,    KC_BSPC,
        KC_LCTL,    KC_A,    KC_S,    KC_D,       KC_F,       KC_G,           KC_H,    KC_J,   KC_K,     KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,       KC_V,       KC_B,           KC_N,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
                                      TD(OSLMO1), KC_SPC,     TD(ALTLR),      KC_ESC, KC_ENT, TD(OSLMO2)
    ),

    [1] = LAYOUT_split_3x6_4(
        _______,    KC_F1,   KC_F2,   KC_F3,      KC_F4,      KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______,    KC_1,    KC_2,    KC_3,       KC_4,       KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______,    KC_ESC,  XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_GRAVE,KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
                                      KC_LWIN,    _______,    _______,        _______, _______, _______
    ),

    [2] = LAYOUT_split_3x6_4(
        _______,    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LWIN, KC_DEL,
        _______,    XXXXXXX, KC_VOLD, KC_MUTE,    KC_VOLU,    XXXXXXX,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F12,  KC_PSCR,
        _______,    XXXXXXX, KC_MPRV, KC_MPLY,    KC_MNXT,    XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                      _______,    _______,    _______,        _______, _______, _______
    )
};

