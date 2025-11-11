#include "tap_dance.h"

oslmo_state_t oslmo1 = OSLMO_NONE;
oslmo_state_t oslmo2 = OSLMO_NONE;

void td_oslmo1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(1);
        oslmo1 = OSLMO_HELD;
    } else if (state->count == 1) {
        set_oneshot_layer(1, ONESHOT_START);
        oslmo1 = OSLMO_ONESHOT;
    }
}

void td_oslmo2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        layer_on(2);
        oslmo2 = OSLMO_HELD;
    } else if (state->count == 1) {
        set_oneshot_layer(2, ONESHOT_START);
        oslmo2 = OSLMO_ONESHOT;
    }
}
