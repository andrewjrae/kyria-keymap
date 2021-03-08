/* Copyright 2021 Andrew Rae ajrae.nv@gmail.com @andrewjrae
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <string.h>

#ifdef MY_SPLIT_RIGHT
#endif

enum layers {
    _RSTHD = 0,
    _ATHEX,
    _QWERTY,
    _NAV,
    _NUM,
    _SYM,
    _FUN,
    _LIGHTS
};

enum custom_keycodes {
    CAPSWRD = SAFE_RANGE,
};

// clang-format off
#define MY_HOMEROW_LAYOUT( \
    L00, L01, L02, L03, L04, L05,                     R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29, L30, L31, R32, R33, R34, R35, R36, R37, R38, R39, \
                   L40, L41, L42, L43, L44, R45, R46, R47, R48, R49 \
    ) \
    LAYOUT( \
        L00, L01, L02, L03, L04, L05,                     R06, R07, R08, R09, R10, R11, \
        L12, LALT_T(L13), LGUI_T(L14), LCTL_T(L15), LSFT_T(L16), L17,   \
        R18, LSFT_T(R19), LCTL_T(R20), LGUI_T(R21), LALT_T(R22), R23,   \
        L24, L25, L26, L27, L28, L29, L30, L31, R32, R33, R34, R35, R36, R37, R38, R39, \
                    L40, L41, L42, L43, L44, R45, R46, R47, R48, R49 \
    )

#define MY_ALPHA_LAYOUT( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, KQUOT, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
    KTHMB \
    ) \
    LAYOUT( \
      KC_TAB,   K01,   K02,   K03,     K04,     K05,                                          K06,     K07,    K08,    K09,    K0A,   KC_PIPE, \
      MY_ESC,   K11,   K12,   K13,     K14,     K15,                                          K16,     K17,    K18,    K19,    K1A,   KQUOT, \
      KC_SLSH,  K21,   K22,   K23,     K24,     K25,     KC_LEAD, _______, _______, KC_LEAD,  K26,     K27,    K28,    K29,    K2A,   KC_MINS, \
                              _______, KC_LGUI, MY_LALT, KTHMB,   MY_ENT,  MY_BSPC, MY_SPC,   MY_RCTL, KC_RGUI, _______ \
    )
// clang-format on

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Alpha Layer: RSTHD - modified for better vim usage and personal comfort
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Z  |   C  |   Y  |   F  |   P  |                              |   X  |   M  | '  " |   U  |   Q  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  /  ?  |   R  |   S  |   T  |   H  |   D  |                              |   L  |   N  |   A  |   I  |   O  |  ; :   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  CAPS  |  OSS |   V  |   G  |   K  |   B  |Leader|      |  |      |Leader|   W  |   J  | ,  < | .  > |  OSS |  -  _  |
 * `----------------------+------+------+------+------+ Enter|  | Bksp +------+------+------+------+----------------------'
 *                        | ???  | GUI  | Esc  | Space| SYM  |  | SYM  |  E   | Tab  | GUI  | ???  |
 *                        |      |      |      |  NAV |      |  |      | NUM  | FUN  |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
#define RST_E LT(_NUM, KC_E)
#define RST_SPC LT(_NAV, KC_SPC)
#define RST_ENT LT(_SYM, KC_ENT)
#define RST_TAB LT(_FUN, KC_TAB)
    [_RSTHD] = MY_HOMEROW_LAYOUT(
        KC_TAB,   KC_Z,    KC_C, KC_Y, KC_F, KC_P,                                     KC_X, KC_M, KC_QUOT, KC_U,    KC_Q,    KC_PIPE,
LT(_NAV,KC_SLSH), KC_R,    KC_S, KC_T, KC_H, KC_D,                                     KC_L, KC_N, KC_A,    KC_I,    KC_O,    KC_SCLN,
       CAPSWRD,  MY_LSFT, KC_V, KC_G, KC_K, KC_B, KC_LEAD, _______, _______, KC_LEAD, KC_W, KC_J, KC_COMM, KC_DOT,  MY_RSFT, KC_MINS,
        _______, KC_LGUI, KC_ESC, RST_SPC, RST_ENT, MY_BSPC, RST_E, RST_TAB, KC_RGUI, _______
    ),
/*
 * Alpha Layer: ATHEX a modified THE-1 for better vim usage and personal comfort
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Z  |   M  |   L  |   U  | .  > |                              |   V  |   D  |   R  | '  " |   Q  | \  |   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Esc/NAV |   A  |   T  |   H  |   E  |   X  |                              |   C  |   S  |   N  |   O  |   I  | ;  :   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift | /  ? |   P  |   F  |   K  | ,  < |Leader|      |  |      |Leader|   G  |   J  |   W  |   B  |   Y  | -  _   |
 * `----------------------+------+------+------+------+ Enter|  | Bksp +------+------+------+------+----------------------'
 *                        | ???  | GUI  | Esc  | OSM  | NUM  |  | SYM  | Space| Tab  | GUI  | ???  |
 *                        |      |      | Alt  | Shift|      |  |      | NAV  | Ctrl |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ATHEX] = MY_ALPHA_LAYOUT(
        KC_Z,    KC_M,   KC_L,   KC_U,   KC_DOT,        KC_V,   KC_D,   KC_R,   KC_QUOT, KC_Q,
        KC_A,    KC_T,   KC_H,   KC_E,   KC_X,          KC_C,   KC_S,   KC_N,   KC_O,    KC_I, KC_SCLN,
        KC_SLSH, KC_P,   KC_F,   KC_K,   KC_COMM,       KC_G,   KC_J,   KC_W,   KC_B,    KC_Y,
        MY_LSFT
    ),
/*
 * Alpha Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |NAV/Esc |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |Leader|      |  |      |Leader|   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+ Enter|  | Bksp +------+------+------+------+----------------------'
 *                        | ???  | GUI  | Esc  | OSM  | SYM  |  | NUM  | Space| Tab  | GUI  | ???  |
 *                        |      |      | Alt  | Shift|      |  |      | NAV  | Ctrl |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = MY_ALPHA_LAYOUT(
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,           KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
        KC_A,   KC_S,   KC_D,   KC_F,   KC_G,           KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,           KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,
        MY_LSFT
    ),
/*
 * Symbols Layer: Symbols with C style coding in mind
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  !   |  @   |  $   |      |                              |      |  ~   |  `   |  \   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  *   |  |   |  +   |  =   |  [   |                              |   <  |  {   |  (   |  >   |  %   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  /   |  &   |  -   |  #   |  ]   |      |      |  |      |      |   ^  |  }   |  )   |  _   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______, _______, KC_EXLM, KC_AT,   KC_DLR,  _______,                                     _______, KC_TILD, KC_EQL,  KC_BSLS, _______, _______,
      _______, KC_ASTR, KC_LABK, KC_MINS, KC_RABK, KC_LBRC,                                     KC_PIPE, KC_LCBR, KC_LPRN, KC_RPRN, KC_PERC, _______,
      _______, KC_SLSH, KC_PLUS, KC_CIRC, KC_HASH, KC_RBRC, _______, _______, _______, _______, KC_AMPR, KC_RCBR, KC_GRV,  KC_UNDS, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Number Layer: Numbers and function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  7   |  8   |  9   |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  /     |  1   |  2   |  3   |  0   |      |                              |  ^   |  =   |  +   |  -   |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  *   |  4   |  5   |  6   |      |      |      |  |      |      |      |  <   |  >   |  .   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = MY_HOMEROW_LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, KC_EQL,  _______, _______, _______,
      KC_SLSH, KC_3,    KC_2,    KC_1,    KC_0,    KC_4,                                        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    _______,
      _______, _______, KC_PLUS, KC_CIRC, KC_ASTR, _______, _______, _______, _______, _______, _______, KC_MINS, KC_COMM, KC_DOT,  _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Nav Layer: Navigation keys, copy paste, and media keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | Copy | End  | Paste|                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | End  | Next | Play | VolUp| Del  |                              | Left | Down | Up   | Right| Home |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | Prev | Mute | VolDn| VolDn|      |      |  |      |      | vi B | PgDn | PgUp | vi W |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
 #define LCSPSCR LSFT(LCTL(KC_PSCR))
    [_NAV] = LAYOUT(
      _______, _______, KC_PSCR, KC_COPY, LCSPSCR, KC_PASTE,                                    _______, _______, _______, _______, _______, _______,
      _______, KC_END,  KC_MNXT, KC_MPLY, KC_VOLU, KC_DEL,                                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_HOME, _______,
      _______, _______, KC_MPRV, KC_MUTE, KC_VOLD, _______, _______, _______, _______, _______, VI_B,    KC_PGDN, KC_PGUP, VI_W,    _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Function Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  F7  |  F8  |  F9  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F10 | F11  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  F4  |  F5  |  F6  | F12  |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUN] = LAYOUT(
      _______, _______, KC_F7,   KC_F8,   KC_F9,   _______,                                     _______, _______, _______, _______, _______, _______,
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F10,  KC_F11,                                      _______, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, _______,
      _______, _______, KC_F4,   KC_F5,   KC_F6,   KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifndef MY_SPLIT_RIGHT

/* --------------- PROCESS RECORD --------------- */
static bool caps_word_on = false;

void caps_word_enable(void) {
    caps_word_on = true;
}

void caps_word_disable(void) {
    caps_word_on = false;
    unregister_mods(MOD_LSFT);
}

void caps_word_process_user(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on) {
        // Get the base keycode of a mod or layer tap key
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0)
                    return;
                keycode = keycode & 0xFF;
                break;
            default:
                break;
        }

        switch (keycode) {
            // Keycodes to shift
            case KC_A ... KC_Z:
                if (record->event.pressed)
                    register_mods(MOD_LSFT);
                else if (!record->tap.interrupted)
                    unregister_mods(MOD_LSFT);
            // Keycodes to ignore (don't disable caps word), but not to shift
            case KC_1 ... KC_0:
            case KC_MINS:
            case KC_BSPC:
            case KC_UNDS:
            case CAPSWRD:
                // If mod chording disable the mods
                if (record->event.pressed && (get_mods() != MOD_LSFT) && (get_mods() != 0)) {
                    caps_word_disable();
                }
                break;
            default:
                if (record->event.pressed)
                    caps_word_disable();
                break;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process caps word for updates
    caps_word_process_user(keycode, record);

    // Regular user keycode case statement
    switch (keycode) {
        case CAPSWRD:
            if (record->event.pressed) {
                caps_word_enable();
            }
            return false;
        case KC_MINS:
            // Turn the cheeky corner minus sign into an underscore when using caps word
            if (caps_word_on && record->event.pressed && record->event.key.col == MATRIX_COLS-1) {
                tap_code16(KC_UNDS);
                return false;
            }
            return true;
        case LCTL_T(KC_PLUS):
            if (record->event.pressed && record->tap.count > 0) {
                tap_code16(KC_PLUS);
                return false;
            }
            return true;
        case LGUI_T(KC_RABK):
            if (record->event.pressed && record->tap.count > 0) {
                tap_code16(KC_RABK);
                return false;
            }
            return true;
        default:
            return true;  // Process all other keycodes normally
    }
}

/* --------------- COMBOS --------------- */
#ifdef COMBO_ENABLE
enum combo_events {
  PD_COMBO,
  XL_COMBO,
  LEFT_LEAD,
  RIGHT_LEAD,
};

const uint16_t PROGMEM pd_combo[] = {KC_P, KC_D, COMBO_END};
const uint16_t PROGMEM xl_combo[] = {KC_X, KC_L, COMBO_END};
/* const uint16_t PROGMEM left_thumb_combo[] = {RST_E, KC_LEAD, COMBO_END}; */
/* const uint16_t PROGMEM right_thumb_combo[] = {RST_SPC, KC_LEAD, COMBO_END}; */

combo_t key_combos[COMBO_COUNT] = {
  [ PD_COMBO ] = COMBO_ACTION(pd_combo),
  [ XL_COMBO ] = COMBO_ACTION(xl_combo),
  /* [ LEFT_LEAD ] = COMBO_ACTION(left_thumb_combo), */
  /* [ RIGHT_LEAD ] = COMBO_ACTION(right_thumb_combo), */
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        // This is the leader key for my xmonad config
        case LEFT_LEAD:
        case PD_COMBO:
            if (pressed) {
                tap_code16(LGUI(KC_G));
            }
            break;
        case RIGHT_LEAD:
            if (pressed) {
                qk_leader_start(); // the underlying leader command
            }
            break;
        case XL_COMBO:
            if (pressed) {
                caps_word_enable(); // toggle caps word
            }
            break;
    }
}
#    endif

/* --------------- LEADER SEQUENCES --------------- */
#ifdef LEADER_ENABLE
LEADER_EXTERNS();

#ifdef OLED_DRIVER_ENABLE
static const char keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};

static uint8_t leader_seq_idx;
static uint8_t leader_display_size;
static const char space_ascii[] = "SPC";
static char leader_display[19];

void update_leader_display(uint16_t keycode) {
    leader_seq_idx = leader_sequence_size;
    leader_display[leader_display_size] = ' ';
    ++leader_display_size;
    switch (keycode) {
        case KC_SPC:
            memcpy(leader_display+leader_display_size, space_ascii, sizeof(space_ascii));
            leader_display_size += sizeof(space_ascii);
            break;
        default:
            leader_display[leader_display_size] = keycode_to_ascii_lut[keycode];
            ++leader_display_size;
            break;
    }
}

void leader_start(void) {
    leader_display[0] = 'L';
    leader_display[1] = 'D';
    leader_display[2] = 'R';
    leader_display[3] = '-';
    leader_display_size = 3;
}
#endif // end oled enable

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
#ifdef LEADER_SEQ_ESC
    leader_time = timer_read();
#endif

    // Open terminal
    SEQ_TWO_KEYS(KC_O, KC_T) {
        SEND_STRING(SS_LCTL(SS_LALT("t")));
        leading = false;
    }
    // Close window
    SEQ_TWO_KEYS(KC_W, KC_C) {
        SEND_STRING(SS_LALT(SS_TAP(X_F4)));
        leading = false;
    }
    if (leader_sequence[0])
    // Switch to ATHEX
    SEQ_TWO_KEYS(KC_L, KC_A) {
        layer_move(_ATHEX);
        leading = false;
    }
    // Switch to RSTHD
    SEQ_TWO_KEYS(KC_L, KC_R) {
        layer_move(_RSTHD);
        leading = false;
    }
    // Switch to QWERTY
    SEQ_TWO_KEYS(KC_L, KC_Q) {
        layer_move(_QWERTY);
        leading = false;
    }
    // Switch to lights layer
    SEQ_TWO_KEYS(KC_L, KC_L) {
        layer_on(_LIGHTS);
        leading = false;
    }
    if (!leading) {
        leader_end();
    }
#ifdef OLED_DRIVER_ENABLE
    else {
        leader_display[leader_display_size] = '-';
    }
#endif // end oled enable
  }
}
#endif // end leader enable

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}


static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria - ajrae\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _ATHEX:
            oled_write_P(PSTR("ATHEX\n\n"), false);
            break;
        case _RSTHD:
            oled_write_P(PSTR("RSTHD v4\n\n"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Numbers\n\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Symbols\n\n"), false);
            break;
        case _LIGHTS:
            oled_write_P(PSTR("Lights\n\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n\n"), false);
    }
#ifdef LEADER_ENABLE
    // Leader key display
    if (leading) {
        if (leader_sequence_size != leader_seq_idx) {
            update_leader_display(leader_sequence[leader_sequence_size - 1]);
        }
    } else if (leader_display_size != 0) {
        leader_display_size = 0;
        leader_seq_idx = 0;
        memset(leader_display, 0, sizeof(leader_display));
        oled_write(leader_display, false);
    }
    oled_write_ln(leader_display, false);
#endif // end leader enable
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}

#endif // end oled enable
#endif // end is not right side
