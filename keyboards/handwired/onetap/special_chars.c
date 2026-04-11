#include "special_chars.h"

#define ACTIVATE_MIN_DELAY 200
#define ACTIVATE_MAX_DELAY 1000

static bool enabled             = true;
static bool unicode_mode_manual = false;

static bool     pending_shifted = false;
static uint16_t pending_keycode = KC_NO;
static uint16_t pending_timer   = 0;

enum unicode_names {
    DE_ADIA_LOWER,
    DE_ADIA_UPPER,
    DE_ODIA_LOWER,
    DE_ODIA_UPPER,
    DE_UDIA_LOWER,
    DE_UDIA_UPPER,
    SZ_SIGN_LOWER,
    SZ_SIGN_UPPER,
    EURO_SIGN,
};

// clang-format off
const uint32_t PROGMEM unicode_map[] = {
    [DE_ADIA_LOWER] = 0x00E4,
    [DE_ADIA_UPPER] = 0x00C4,
    [DE_ODIA_LOWER] = 0x00F6,
    [DE_ODIA_UPPER] = 0x00D6,
    [DE_UDIA_LOWER] = 0x00FC,
    [DE_UDIA_UPPER] = 0x00DC,
    [SZ_SIGN_LOWER] = 0x00DF,
    [SZ_SIGN_UPPER] = 0x1E9E,
    [EURO_SIGN]     = 0x20AC,
};
// clang-format on

static bool keycode_is_candidate(uint16_t keycode) {
    switch (keycode) {
        case KC_A:
        case KC_O:
        case KC_U:
        case KC_S:
        case KC_E:
            return true;
        default:
            return false;
    }
}

static bool has_non_shift_mods(void) {
    const uint8_t mods = get_mods() | get_oneshot_mods();
    return (mods & ~(MOD_MASK_SHIFT)) != 0;
}

static bool is_shift_active(void) {
    return (get_mods() | get_oneshot_mods() | get_weak_mods()) & MOD_MASK_SHIFT;
}

static void clear_pending(void) {
    pending_shifted = false;
    pending_keycode = KC_NO;
    pending_timer   = 0;
}

typedef struct {
    uint8_t mods;
    uint8_t weak_mods;
    uint8_t oneshot_mods;
} saved_mod_state_t;

static saved_mod_state_t save_and_clear_mod_state(void) {
    saved_mod_state_t state = {
        .mods         = get_mods(),
        .weak_mods    = get_weak_mods(),
        .oneshot_mods = get_oneshot_mods(),
    };

    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();

    return state;
}

static void restore_mod_state(saved_mod_state_t state) {
    set_mods(state.mods);
    set_weak_mods(state.weak_mods);
    add_oneshot_mods(state.oneshot_mods);
    send_keyboard_report();
}

static void send_key_sequence(uint16_t keycode) {
    saved_mod_state_t state = save_and_clear_mod_state();
    tap_code16(keycode);
    restore_mod_state(state);
}

static void send_macos_dead_key_sequence(uint16_t accent_keycode, uint16_t base_keycode, bool shifted) {
    saved_mod_state_t state = save_and_clear_mod_state();

    tap_code16(accent_keycode);

    if (shifted) {
        register_code(KC_LSFT);
    }

    tap_code(base_keycode);

    if (shifted) {
        unregister_code(KC_LSFT);
    }

    restore_mod_state(state);
}

static void send_macos_umlaut(uint16_t keycode, bool shifted) {
    send_macos_dead_key_sequence(LGUI(KC_U), keycode, shifted);
}

static void send_macos_special(uint16_t keycode, bool shifted) {
    if (keycode == KC_E) {
        send_key_sequence(LGUI(LSFT(KC_2)));
        return;
    }

    if (keycode == KC_S) {
        send_key_sequence(LGUI(KC_S));
        return;
    }

    send_macos_umlaut(keycode, shifted);
}

static bool send_windows_special(uint16_t keycode, bool shifted) {
    switch (keycode) {
        case KC_A:
            send_key_sequence(shifted ? RALT(S(KC_Q)) : RALT(KC_Q));
            return true;
        case KC_O:
            send_key_sequence(shifted ? RALT(S(KC_P)) : RALT(KC_P));
            return true;
        case KC_U:
            send_key_sequence(shifted ? RALT(S(KC_Y)) : RALT(KC_Y));
            return true;
        case KC_S:
            if (shifted) {
                return false;
            }
            send_key_sequence(RALT(KC_S));
            return true;
        case KC_E:
            send_key_sequence(RALT(KC_5));
            return true;
        default:
            return false;
    }
}

static bool send_linux_special(uint16_t keycode, bool shifted) {
    switch (keycode) {
        case KC_A:
            send_key_sequence(shifted ? RALT(S(KC_A)) : RALT(KC_A));
            return true;
        case KC_O:
            send_key_sequence(shifted ? RALT(S(KC_O)) : RALT(KC_O));
            return true;
        case KC_U:
            send_key_sequence(shifted ? RALT(S(KC_U)) : RALT(KC_U));
            return true;
        case KC_S:
            send_key_sequence(shifted ? RALT(S(KC_S)) : RALT(KC_S));
            return true;
        case KC_E:
            send_key_sequence(RALT(KC_E));
            return true;
        default:
            return false;
    }
}

static void enable(void) {
    enabled = true;
}

static void toggle_enabled(void) {
    enabled = !enabled;

    if (!enabled) {
        clear_pending();
    }
}

bool set_unicode_mode(os_variant_t os) {
    if (unicode_mode_manual) {
        return false;
    }

    switch (os) {
        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            break;
        case OS_MACOS:
        case OS_IOS:
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        case OS_LINUX:
        case OS_UNSURE:
        default:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
    }

    enable();
    return true;
}

bool process_unicode_mode(uint16_t keycode) {
    switch (keycode) {
        case UM_LNX:
            unicode_mode_manual = true;
            enable();
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            return true;
        case UM_MAC:
            unicode_mode_manual = true;
            enable();
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            return true;
        case UM_WCP:
            unicode_mode_manual = true;
            enable();
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            return true;
        case UM_TGL:
            toggle_enabled();
            return true;
    }

    return false;
}

bool process_special_char(uint16_t keycode) {
    if (!enabled) {
        return false;
    }

    if (pending_keycode != KC_NO && pending_shifted != is_shift_active()) {
        clear_pending();
    }

    if (pending_keycode != KC_NO && timer_elapsed(pending_timer) > ACTIVATE_MAX_DELAY) {
        clear_pending();
    }

    if (has_non_shift_mods() || !keycode_is_candidate(keycode)) {
        clear_pending();
        return false;
    }

    if (pending_keycode != keycode) {
        pending_shifted = is_shift_active();
        pending_keycode = keycode;
        pending_timer   = timer_read();
        return false;
    }

    const uint16_t elapsed = timer_elapsed(pending_timer);
    if (elapsed >= ACTIVATE_MIN_DELAY && elapsed <= ACTIVATE_MAX_DELAY) {
        tap_code(KC_BSPC);
        switch (get_unicode_input_mode()) {
            case UNICODE_MODE_MACOS:
                send_macos_special(keycode, pending_shifted);
                break;
            case UNICODE_MODE_LINUX:
                send_linux_special(keycode, pending_shifted);
                break;
            case UNICODE_MODE_WINCOMPOSE:
                send_windows_special(keycode, pending_shifted);
                break;
            default:
                clear_pending();
                return false;
        }

        clear_pending();
        return true;
    }

    if (elapsed < ACTIVATE_MIN_DELAY) {
        clear_pending();
    } else {
        pending_shifted = is_shift_active();
        pending_timer   = timer_read();
    }

    return false;
}
