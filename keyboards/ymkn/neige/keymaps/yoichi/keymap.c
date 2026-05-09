/* SPDX-License-Identifier: GPL-2.0-or-later */
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum layer_number {
    _BASE = 0,
    _NUMBER = 1,
    _SYMBOL = 2,
    _FUNC = 3,
    _MEDIA = 4,
    _CONFIG = 5,
};

enum custom_user_keycodes {
    MS_RST = QK_USER_0,
    IME_TGL = QK_USER_1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  CTL_T(KC_SPC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_MINS,  KC_ENT,
KC_LSFT, KC_Z, GUI_T(KC_X), LT(_NUMBER, KC_C), KC_V,    KC_B,    KC_N,    KC_M, LT(_SYMBOL, KC_COMM), ALT_T(KC_DOT), KC_SLSH, KC_RSFT
    ),
    [_NUMBER] = LAYOUT(
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
        KC_QUOT, KC_MINS,  KC_EQL,  KC_GRV, KC_LBRC, KC_RBRC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_SCLN, KC_BSLS,
        _______, KC_INT1, KC_INT3, _______, KC_HOME,  KC_END, _______,C(KC_SPC),TG(_FUNC),KC_DOT, KC_SLSH, _______
    ),
    [_SYMBOL] = LAYOUT(
      S(KC_INS), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), IME_TGL,
S(KC_QUOT),S(KC_MINS),S(KC_EQL),S(KC_GRV),S(KC_LBRC),S(KC_RBRC), S(KC_LEFT), S(KC_DOWN), S(KC_UP), S(KC_RGHT), S(KC_SCLN), S(KC_BSLS),
_______,S(KC_INT1),S(KC_INT3),MO(_MEDIA),S(KC_HOME),S(KC_END), _______, _______, _______, _______, KC_CAPS, _______
    ),
    [_FUNC] = LAYOUT(
      TG(_FUNC),   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, MS_WHLL, MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, MS_WHLR,  MS_RST,
    _______, _______, _______, MO(_CONFIG), _______, _______, MS_WHLD, MS_BTN1, _______, MS_BTN2, MS_WHLU, _______
    ),
    [_MEDIA] = LAYOUT(
        _______, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5), G(KC_6), G(KC_7), G(KC_8), G(KC_9), KC_BRIU, KC_VOLU,
_______,LCA(KC_DEL),LCA(KC_HOME),S(G(KC_4)),_______, _______, C(KC_LEFT), C(KC_DOWN), C(KC_UP), C(KC_RGHT), KC_BRID, KC_VOLD,
        _______, _______, _______, _______, _______, _______, LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_UP), LCA(KC_RGHT), _______, KC_MUTE
    ),
    [_CONFIG] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EE_CLR,
        QK_BOOT, _______, _______, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

static bool use_pseudo_us_keymap = false;
static bool reverse_wheel_direction = true;
#if defined(OS_DETECTION_ENABLE)
static os_variant_t host_os;
bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
            uprintf("detected_os = %d -> OS_MACOS\n", detected_os);
            host_os = OS_MACOS;
            use_pseudo_us_keymap = false;
            reverse_wheel_direction = true;
            break;
        case OS_WINDOWS:
        default:
            uprintf("detected_os = %d -> OS_WINDOWS\n", detected_os);
            host_os = OS_WINDOWS;
            use_pseudo_us_keymap = true;
            reverse_wheel_direction = false;
            break;
    }
    return 0;
}
#endif

void register_mouse(uint8_t mouse_keycode, bool pressed);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("process_record_user: 0x%04x\n", keycode);
#endif
    switch (keycode) {
        case KC_CAPS:
            if (use_pseudo_us_keymap) {
                uint16_t kc = JP_CAPS; // (CapsLock)
                if (record->event.pressed) {
                    register_code16(kc);
                } else {
                    unregister_code16(kc);
                }
                return false;
            }
            break;
        case KC_2:
        case S(KC_2):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_2) || mod_state & MOD_MASK_SHIFT) {
                    static uint16_t kc;
                    if (record->event.pressed) {
                        kc = JP_AT; // @
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(kc);
                        set_mods(mod_state);
                        return false;
                    } else if (kc) {
                        del_mods(MOD_MASK_SHIFT);
                        unregister_code16(kc);
                        set_mods(mod_state);
                        kc = 0;
                        return false;
                    }
                }
            }
            break;
        case KC_6:
        case S(KC_6):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_6) || mod_state & MOD_MASK_SHIFT) {
                    static uint16_t kc;
                    if (record->event.pressed) {
                        kc = JP_CIRC; // ^
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(kc);
                        set_mods(mod_state);
                        return false;
                    } else if (kc) {
                        del_mods(MOD_MASK_SHIFT);
                        unregister_code16(kc);
                        set_mods(mod_state);
                        kc = 0;
                        return false;
                    }
                }
            }
            break;
        case KC_7:
        case S(KC_7):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_7) || mod_state & MOD_MASK_SHIFT) {
                    uint16_t kc = JP_AMPR; // &
                    if (record->event.pressed) {
                        register_code16(kc);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
                }
            }
            break;
        case KC_8:
        case S(KC_8):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_8) || mod_state & MOD_MASK_SHIFT) {
                    uint16_t kc = JP_ASTR; // *
                    if (record->event.pressed) {
                        register_code16(kc);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
                }
            }
            break;
        case KC_9:
        case S(KC_9):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_9) || mod_state & MOD_MASK_SHIFT) {
                    uint16_t kc = JP_LPRN; // (
                    if (record->event.pressed) {
                        register_code16(kc);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
                }
            }
            break;
        case KC_0:
        case S(KC_0):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_0) || mod_state & MOD_MASK_SHIFT) {
                    uint16_t kc = JP_RPRN; // )
                    if (record->event.pressed) {
                        register_code16(kc);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
                }
            }
            break;
        case KC_MINS:
        case S(KC_MINS):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_MINS) || mod_state & MOD_MASK_SHIFT) {
                    static uint16_t kc;
                    if (record->event.pressed) {
                        kc = JP_UNDS; // _
                        register_code16(kc);
                    } else if (kc) {
                        unregister_code16(kc);
                        kc = 0;
                    }
                    return false;
                }
            }
            break;
        case KC_QUOT:
        case S(KC_QUOT):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                uint8_t mod_state = get_mods();
                if (record->event.pressed) {
                    if (keycode == S(KC_QUOT) || mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        kc = JP_DQUO; // "
                    } else {
                        kc = JP_QUOT; // '
                    }
                    register_code16(kc);
                    set_mods(mod_state);
                    return false;
                } else if (kc) {
                    if (kc == JP_DQUO) {
                        del_mods(MOD_MASK_SHIFT);
                    }
                    unregister_code16(kc);
                    set_mods(mod_state);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_GRV:
        case S(KC_GRV):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                uint8_t mod_state = get_mods();
                if (record->event.pressed) {
                    if (keycode == S(KC_GRV) || mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        kc = JP_TILD; // ~
                    } else {
                        kc = JP_GRV; // `
                    }
                    register_code16(kc);
                    set_mods(mod_state);
                    return false;
                } else if (kc) {
                    if (kc == JP_TILD) {
                        del_mods(MOD_MASK_SHIFT);
                    }
                    unregister_code16(kc);
                    set_mods(mod_state);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_SCLN:
        case S(KC_SCLN):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_SCLN) || mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    uint16_t kc = JP_COLN; // :
                    if (record->event.pressed) {
                        register_code16(kc);
                    } else {
                        unregister_code16(kc);
                    }
                    set_mods(mod_state);
                    return false;
                }
            }
            break;
        case KC_EQL:
        case S(KC_EQL):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                uint8_t mod_state = get_mods();
                if (record->event.pressed) {
                    if (keycode == S(KC_EQL) || mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        kc = JP_PLUS;
                    } else if (mod_state & MOD_MASK_CTRL) {
                        // treat Ctrl+= as Zoom-in like US layout (=, + are on the same key)
                        // cf. Ctrl+= is treated as Zoom-out in JP layout (-, = are on the same key)
                        del_mods(MOD_MASK_SHIFT);
                        kc = JP_SCLN; // ;, + are on the same key in JIS layout
                    } else {
                        kc = JP_EQL; // =
                    }
                    register_code16(kc);
                    set_mods(mod_state);
                    return false;
                } else if (kc) {
                    if (kc == JP_PLUS || kc == JP_SCLN) {
                        del_mods(MOD_MASK_SHIFT);
                    }
                    unregister_code16(kc);
                    set_mods(mod_state);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_BSLS:
        case S(KC_BSLS):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                uint8_t mod_state = get_mods();
                if (record->event.pressed) {
                    if (keycode == S(KC_BSLS) || mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        kc = JP_PIPE; // |
                    } else {
                        kc = JP_BSLS; // (backslash)
                    }
                    register_code16(kc);
                    set_mods(mod_state);
                    return false;
                } else if (kc) {
                    if (kc == JP_PIPE) {
                        del_mods(MOD_MASK_SHIFT);
                    }
                    unregister_code16(kc);
                    set_mods(mod_state);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_LBRC:
        case S(KC_LBRC):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                uint8_t mod_state = get_mods();
                if (record->event.pressed) {
                    if (keycode == S(KC_LBRC) || mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        kc = JP_LCBR; // {
                    } else {
                        kc = JP_LBRC; // [
                    }
                    register_code16(kc);
                    set_mods(mod_state);
                    return false;
                } else if (kc) {
                    if (kc == JP_LCBR) {
                        del_mods(MOD_MASK_SHIFT);
                    }
                    unregister_code16(kc);
                    set_mods(mod_state);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_RBRC:
        case S(KC_RBRC):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                uint8_t mod_state = get_mods();
                if (record->event.pressed) {
                    if (keycode == S(KC_RBRC) || mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_SHIFT);
                        kc = JP_RCBR; // }
                    } else {
                        kc = JP_RBRC; // ]
                    }
                    register_code16(kc);
                    set_mods(mod_state);
                    return false;
                } else if (kc) {
                    if (kc == JP_RCBR) {
                        del_mods(MOD_MASK_SHIFT);
                    }
                    unregister_code16(kc);
                    set_mods(mod_state);
                    kc = 0;
                    return false;
                }
            }
            break;
#if defined(OS_DETECTION_ENABLE)
        case IME_TGL:
            if (host_os == OS_WINDOWS) {
                if (record->event.pressed) {
                    if (use_pseudo_us_keymap) {
                        tap_code16(JP_ZKHK);
                    } else {
                        register_code16(KC_RALT);
                        wait_ms(10);
                        tap_code16(KC_GRV);
                        unregister_code16(KC_RALT);
                    }
                }
                return false;
            } else {
                if (record->event.pressed) {
                    register_code16(KC_LGUI);
                    wait_ms(10);
                    tap_code16(KC_SPC);
                    unregister_code16(KC_LGUI);
                }
                return false;
            }
            break;
        case CTL_T(KC_SPC):
            if (host_os == OS_WINDOWS) {
                uint8_t mod_state = get_mods();
                if (record->tap.count && mod_state & MOD_MASK_ALT && record->event.pressed) {
                    if (use_pseudo_us_keymap) {
                        tap_code16(JP_ZKHK);
                    } else {
                        register_code16(KC_RALT);
                        wait_ms(10);
                        tap_code16(KC_GRV);
                        unregister_code16(KC_RALT);
                    }
                    return false;
                }
            }
            break;
        case S(G(KC_4)): // screen capture
            if (host_os == OS_WINDOWS) {
                uint16_t kc = S(G(KC_S));
                if (record->event.pressed) {
                    register_code16(kc);
                } else {
                    unregister_code16(kc);
                }
                return false;
            }
            break;
        case ALT_T(KC_DOT):
            if (host_os == OS_WINDOWS) {
                if (!record->tap.count) { // hold
                    if (record->event.pressed) {
                        register_code16(KC_LGUI);
                    } else {
                        unregister_code16(KC_LGUI);
                    }
                    return false;
                }
            }
            break;
        case GUI_T(KC_X):
            if (host_os == OS_WINDOWS) {
                if (!record->tap.count) { // hold
                    if (record->event.pressed) {
                        register_code16(KC_LALT);
                    } else {
                        unregister_code16(KC_LALT);
                    }
                    return false;
                }
            }
            break;
        case LCA(KC_LEFT):
        case LCA(KC_DOWN):
        case LCA(KC_UP):
        case LCA(KC_RGHT):
            switch (host_os) {
            case OS_WINDOWS:
                keycode ^= (QK_LCTL | QK_LALT);
                keycode = RWIN(keycode);
                if (record->event.pressed) {
                    register_code16(keycode);
                } else {
                    unregister_code16(keycode);
                }
                return false;
            default:
                break;
            }
            break;
        case C(KC_LEFT):
        case C(KC_DOWN):
        case C(KC_UP):
        case C(KC_RGHT):
            switch (host_os) {
            case OS_WINDOWS:
                keycode = RWIN(keycode);
                if (record->event.pressed) {
                    register_code16(keycode);
                } else {
                    unregister_code16(keycode);
                }
                return false;
            default:
                break;
            }
            break;
#endif /* OS_DETECTION_ENABLE */
        case MS_WHLD:
            if (reverse_wheel_direction) {
                register_mouse(MS_WHLU, record->event.pressed);
                return false;
            }
            break;
        case MS_WHLU:
            if (reverse_wheel_direction) {
                register_mouse(MS_WHLD, record->event.pressed);
                return false;
            }
            break;
        case MS_WHLL:
            if (reverse_wheel_direction) {
                register_mouse(MS_WHLR, record->event.pressed);
                return false;
            }
            break;
        case MS_WHLR:
            if (reverse_wheel_direction) {
                register_mouse(MS_WHLL, record->event.pressed);
                return false;
            }
            break;
#ifdef DIGITIZER_ENABLE
        case MS_RST:
            if (record->event.pressed) {
                digitizer_in_range_on();
                digitizer_set_position(0.5, 0.5);
                digitizer_in_range_off();
                return false;
            }
            break;
#endif /* DIGITIZER_ENABLE */
        default:
            break;
    }
    return true;
}
