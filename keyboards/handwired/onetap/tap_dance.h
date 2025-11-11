#pragma once

#include QMK_KEYBOARD_H

typedef enum {
    OSLMO_NONE,
    OSLMO_ONESHOT,
    OSLMO_HELD,
} oslmo_state_t;
extern oslmo_state_t oslmo1;
extern oslmo_state_t oslmo2;

enum {
    OSLMO1 = 0,
    OSLMO2,
};

void td_oslmo1_finished(tap_dance_state_t *state, void *user_data);
void td_oslmo2_finished(tap_dance_state_t *state, void *user_data);
