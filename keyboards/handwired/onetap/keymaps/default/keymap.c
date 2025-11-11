// // Copyright 2025 QMK
// // SPDX-License-Identifier: GPL-2.0-or-later
//
#include QMK_KEYBOARD_H

#include "../../tap_dance.h"

tap_dance_action_t tap_dance_actions[] = {
    [OSLMO1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_oslmo1_finished, NULL),
    [OSLMO2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_oslmo2_finished, NULL),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        switch (oslmo1) {
            case OSLMO_HELD:
                if (keycode == TD(OSLMO1)) {
                    layer_off(1);
                    oslmo1 = OSLMO_NONE;
                }
                break;
            case OSLMO_ONESHOT:
                if (keycode != TD(OSLMO1)) {
                    layer_off(1);
                    oslmo1 = OSLMO_NONE;
                }
                break;
            case OSLMO_NONE:
                break;
        }
        switch (oslmo2) {
            case OSLMO_HELD:
                if (keycode == TD(OSLMO2)) {
                    layer_off(2);
                    oslmo2 = OSLMO_NONE;
                }
                break;
            case OSLMO_ONESHOT:
                if (keycode != TD(OSLMO2)) {
                    layer_off(2);
                    oslmo2 = OSLMO_NONE;
                }
                break;
            case OSLMO_NONE:
                break;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_5(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,           KC_Y,    KC_U,   KC_I,     KC_O,    KC_P,    KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,       KC_G,           KC_H,    KC_J,   KC_K,     KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,           KC_N,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
                                   KC_ESC,  KC_SPC,     KC_LGUI,        KC_F12,  KC_ENT, KC_BSPC,
                                            TD(OSLMO1), KC_LALT,        KC_RALT, TD(OSLMO2)
    ),

    [1] = LAYOUT_split_3x6_5(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_1,    KC_2,    KC_3,    KC_4,       KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,        KC_GRAVE,KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
                                   _______, _______,    _______,        _______, _______, KC_DEL,
                                            _______,    _______,        _______, _______
    ),

    [2] = LAYOUT_split_3x6_5(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,        KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU,    XXXXXXX,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_PSCR,
        _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT,    XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                   _______, _______,    _______,        _______, _______, _______,
                                            _______,    _______,        _______, _______
    )
};

