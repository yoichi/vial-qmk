/*
Copyright 2024 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include "os_detection.h"
#include "keymap_japanese.h"

#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#define MS_BTN3 KC_MS_BTN3

enum layer_number {
    _BASE = 0,
    _NUMBER = 1,
    _SYMBOL = 2,
    _FUNC = 3,
    _MEDIA = 4,
    _CONFIG = 5,
};

enum custom_user_keycodes {
    IME_TGL = QK_USER_0,

    // Reuse unused basic keycodes
    //MY_S_0 = KC_NUBS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TAB,  KC_H,    KC_J,    KC_K,    KC_L,    RCTL_T(KC_SCLN),
LSFT_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),
              KC_LALT, KC_LGUI, LT(_NUMBER,KC_SPC),  MS_BTN1, KC_BSPC, LT(_SYMBOL,KC_ENT), LT(_FUNC,KC_DEL)
    ),
    [_NUMBER] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_INT1, KC_INT3, KC_GRV,  KC_LBRC, KC_RBRC, KC_ESC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS,
LSFT_T(KC_CAPS),S(KC_HOME),S(KC_END),KC_QUOT,KC_BSLS,         KC_MINS, KC_EQL,  KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),
                          KC_HOME, KC_END, _______,  MS_BTN2, IME_TGL, TT(_MEDIA), RCTL(KC_RALT)
    ),
    [_SYMBOL] = LAYOUT(
        S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),          S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0),
S(KC_INT1),S(KC_INT3),S(KC_GRV),S(KC_LBRC),S(KC_RBRC),S(KC_TAB),S(KC_LEFT),S(KC_DOWN),S(KC_UP),S(KC_RGHT),S(KC_INS),
      XXXXXXX, XXXXXXX, XXXXXXX,S(KC_QUOT),S(KC_BSLS),        S(KC_MINS),S(KC_EQL), XXXXXXX, XXXXXXX, XXXXXXX,
                 LCTL(KC_LGUI), KC_LGUI, TT(_MEDIA), MS_BTN1, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_FUNC] = LAYOUT(
        G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5),          G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0),
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,TT(_CONFIG),KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        XXXXXXX,C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),    LCA(KC_LEFT),LCA(KC_DOWN),LCA(KC_UP),LCA(KC_RGHT),KC_F11,
                 LCTL(KC_LGUI), KC_LGUI, TT(_MEDIA), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_MEDIA] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIU, KC_VOLU,
        QK_RBT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_VOLD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_CONFIG] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,          SCRL_TO, XXXXXXX, XXXXXXX, ROT_L15, ROT_R15,
        QK_BOOT, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, XXXXXXX, SCRL_MO, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
        XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD,         SCRL_IN, XXXXXXX, XXXXXXX, XXXXXXX, CPI_SW,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SCRL_SW
    ),
    [6] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [7] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};



#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [1] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [2] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [3] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [4] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [5] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [6] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [7] =   { ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
};
#endif



#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
      case KC_LCTL:
        return true;
      case KC_LSFT:
        return true;
      case SCRL_MO:
        return true;
      default:
        return false;
    }
    return is_mouse_record_user(keycode, record);
}
#endif



#ifdef RGB_MATRIX_ENABLE

static bool is_indicator_for_rotation_angle(uint8_t led) {
    switch (cocot_config.rotation_angle) {
    case 0:
        return (led == g_led_config.matrix_co[1][0] || led == g_led_config.matrix_co[1][1]);
    case 1:
        return (led == g_led_config.matrix_co[0][0] || led == g_led_config.matrix_co[1][1]);
    case 2:
        return (led == g_led_config.matrix_co[0][1] || led == g_led_config.matrix_co[1][1]);
    case 3:
        return (led == g_led_config.matrix_co[0][2] || led == g_led_config.matrix_co[1][2]);
    case 4:
        return (led == g_led_config.matrix_co[0][3] || led == g_led_config.matrix_co[1][3]);
    case 5:
        return (led == g_led_config.matrix_co[0][4] || led == g_led_config.matrix_co[1][4]);
    case 6:
        return led == g_led_config.matrix_co[3][4];
    case 7:
        return (led == g_led_config.matrix_co[0][5] || led == g_led_config.matrix_co[1][5]);
    case 8:
        return (led == g_led_config.matrix_co[0][6] || led == g_led_config.matrix_co[1][6]);
    case 9:
        return (led == g_led_config.matrix_co[0][7] || led == g_led_config.matrix_co[1][7]);
    case 10:
        return (led == g_led_config.matrix_co[0][8] || led == g_led_config.matrix_co[1][8]);
    case 11:
        return (led == g_led_config.matrix_co[0][9] || led == g_led_config.matrix_co[1][8]);
    case 12:
        return (led == g_led_config.matrix_co[1][9] || led == g_led_config.matrix_co[1][8]);
    default:
        return false;
    }
}

static bool is_indicator_for_cpi_idx(uint8_t led) {
    switch (cocot_config.cpi_idx) {
    case 0:
        return led == g_led_config.matrix_co[2][5];
    case 1:
        return led == g_led_config.matrix_co[2][6];
    case 2:
        return led == g_led_config.matrix_co[2][7];
    case 3:
        return led == g_led_config.matrix_co[2][8];
    case 4:
        return led == g_led_config.matrix_co[2][9];
    default:
        return false;
    }
}

static bool is_indicator_for_scrl_div(uint8_t led) {
    switch (cocot_config.scrl_div) {
    case 0:
        return led == g_led_config.matrix_co[3][2];
    case 1:
        return led == g_led_config.matrix_co[3][3];
    case 2:
        return led == g_led_config.matrix_co[3][5];
    case 3:
        return led == g_led_config.matrix_co[3][6];
    case 4:
        return led == g_led_config.matrix_co[3][7];
    case 5:
        return led == g_led_config.matrix_co[3][8];
    default:
        return false;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) { 
    int is_layer = get_highest_layer(layer_state|default_layer_state);  
    HSV hsv = {0, 255, rgblight_get_val()};
    if (is_layer == _NUMBER) {
      hsv.h = 11; //CORAL
    } else if (is_layer == _SYMBOL)  {
      hsv.h = 85; //GREEN
    } else if (is_layer == _FUNC)  {
      hsv.h = 43; //YELLOW
    } else if (is_layer == _MEDIA)  {
      hsv.h = 0; //RED
    } else if (is_layer == _CONFIG)  {
      hsv.h = 191; //PURPLE
    } else if (is_layer == 6)  {
      hsv.h = 64; //CHARTREUSE
    } else if (is_layer == 7)  {
      hsv.h = 224;
    } else {
      hsv.h = 128; //CYAN
    }
    RGB rgb = hsv_to_rgb(hsv);
    HSV hsv_red = {0/*RED*/, 255, rgblight_get_val()};
    RGB rgb_red = hsv_to_rgb(hsv_red);
 
    for (uint8_t i = led_min; i < led_max; i++) {
        if (is_layer == _CONFIG &&
            (is_indicator_for_rotation_angle(i) ||
             is_indicator_for_cpi_idx(i) ||
             is_indicator_for_scrl_div(i))) {
          rgb_matrix_set_color(i, rgb_red.r, rgb_red.g, rgb_red.b);
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
          rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
          rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
    return false;
};

#endif

static bool use_pseudo_us_keymap = false;
static os_variant_t host_os;

#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
uint32_t os_detect_callback(uint32_t trigger_time, void *cb_arg) {
    host_os = detected_host_os();
#ifdef CONSOLE_ENABLE
    uprintf("detected_host_os %d\n", host_os);
#endif
    switch (host_os) {
        case OS_MACOS:
        case OS_IOS:
            host_os = OS_MACOS;
            cocot_config.scrl_inv = false;
            break;
        case OS_WINDOWS:
        default:
            use_pseudo_us_keymap = true;
            host_os = OS_WINDOWS;
            cocot_config.scrl_inv = true;
            break;
    }
    return 0;
}
#endif

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    defer_exec(500, os_detect_callback, NULL);
#endif
}

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
                    uint16_t kc = JP_AT; // @
                    if (record->event.pressed) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(kc);
                        set_mods(mod_state);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
                }
            }
            break;
        case KC_6:
        case S(KC_6):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (keycode == S(KC_6) || mod_state & MOD_MASK_SHIFT) {
                    uint16_t kc = JP_CIRC; // ^
                    if (record->event.pressed) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(kc);
                        set_mods(mod_state);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
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
                    uint16_t kc = JP_UNDS; // _
                    if (record->event.pressed) {
                        register_code16(kc);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
                }
            }
            break;
        case KC_QUOT:
        case S(KC_QUOT):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                if (record->event.pressed) {
                    uint8_t mod_state = get_mods();
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
                    unregister_code16(kc);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_GRV:
        case S(KC_GRV):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                if (record->event.pressed) {
                    uint8_t mod_state = get_mods();
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
                    unregister_code16(kc);
                    kc = 0;
                    return false;
                }
            }
            break;
        case RCTL_T(KC_SCLN):
            if (use_pseudo_us_keymap) {
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    uint16_t kc = JP_COLN; // :
                    if (record->event.pressed) {
                        register_code16(kc);
                    } else {
                        unregister_code16(kc);
                    }
                    return false;
                }
            }
            break;
        case KC_EQL:
        case S(KC_EQL):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                if (record->event.pressed) {
                    uint8_t mod_state = get_mods();
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
                    unregister_code16(kc);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_BSLS:
        case S(KC_BSLS):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                if (record->event.pressed) {
                    uint8_t mod_state = get_mods();
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
                    unregister_code16(kc);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_LBRC:
        case S(KC_LBRC):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                if (record->event.pressed) {
                    uint8_t mod_state = get_mods();
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
                    unregister_code16(kc);
                    kc = 0;
                    return false;
                }
            }
            break;
        case KC_RBRC:
        case S(KC_RBRC):
            if (use_pseudo_us_keymap) {
                static uint16_t kc;
                if (record->event.pressed) {
                    uint8_t mod_state = get_mods();
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
                    unregister_code16(kc);
                    kc = 0;
                    return false;
                }
            }
            break;
        case RALT_T(KC_QUOT):
            if (use_pseudo_us_keymap) {
                if (record->tap.count) {
                    static uint16_t kc;
                    if (record->event.pressed) {
                        uint8_t mod_state = get_mods();
                        if (mod_state & MOD_MASK_SHIFT) {
                            del_mods(MOD_MASK_SHIFT);
                            kc = JP_DQUO;
                        } else {
                            kc = JP_QUOT;
                        }
                        register_code16(kc);
                        set_mods(mod_state);
                        return false;
                    } else if (kc) {
                        unregister_code16(kc);
                        kc = 0;
                        return false;
                    }
                }
            }
            break;
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
        case KC_LALT:
            switch (host_os) {
            case OS_WINDOWS:
                if (record->event.pressed) {
                    register_code16(KC_LGUI);
                } else {
                    unregister_code16(KC_LGUI);
                }
                return false;
            default:
                break;
            }
            break;
        case KC_LGUI:
            switch (host_os) {
            case OS_WINDOWS:
                if (record->event.pressed) {
                    register_code16(KC_LALT);
                } else {
                    unregister_code16(KC_LALT);
                }
                return false;
            default:
                break;
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
        case IME_TGL:
            switch (host_os) {
            case OS_WINDOWS:
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
            case OS_MACOS:
                if (record->event.pressed) {
                    register_code16(KC_LGUI);
                    wait_ms(10);
                    tap_code16(KC_SPC);
                    unregister_code16(KC_LGUI);
                }
                return false;
            default:
                break;
            }
            break;
#endif
        default:
            break;
    }
    return true;
}
