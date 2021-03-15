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

#include "casemodes.h"

// enum for the xcase states
enum xcase_state {
    XCASE_OFF = 0,  // xcase is off
    XCASE_ON,       // xcase is actively on
    XCASE_WAIT,     // xcase is waiting for the delimiter input
};

// bool to keep track of the caps word state
static bool caps_word_on = false;

// enum to keep track of the xcase state
static enum xcase_state xcase_state = XCASE_OFF;
// the keycode of the xcase delimiter
static uint16_t xcase_delimiter;
// the number of keys to the last delimiter
static int8_t distance_to_last_delim = -1;

// Check whether caps word is on
bool caps_word_enabled(void) {
    return caps_word_on;
}

// Enable caps word
void enable_caps_word(void) {
    caps_word_on = true;
#ifndef CAPSWORD_USE_SHIFT
    if (!host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
#endif
}

// Disable caps word
void disable_caps_word(void) {
    caps_word_on = false;
#ifndef CAPSWORD_USE_SHIFT
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
#else
    unregister_mods(MOD_LSFT);
#endif
}

// Toggle caps word
void toggle_caps_word(void) {
    if (caps_word_on) {
        disable_caps_word();
    }
    else {
        enable_caps_word();
    }
}

// Start xcase and pickup the next keystroke as the delimiter
void enable_xcase(void) {
    xcase_state = XCASE_WAIT;
}

// Start xcase with the specified delimiter
void enable_xcase_with(uint16_t delimiter) {
    xcase_state = XCASE_ON;
    xcase_delimiter = delimiter;
    distance_to_last_delim = -1;
}

void disable_xcase(void) {
    xcase_state = XCASE_OFF;
}

static void place_delimiter(void) {
    switch (xcase_delimiter) {
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX: {
            // apparently set_oneshot_mods() is dumb and doesn't deal with handedness for you
            uint8_t mods = xcase_delimiter & 0x10 ? (xcase_delimiter & 0x0F) << 4 : xcase_delimiter & 0xFF;
            set_oneshot_mods(mods);
            break;
        }
        /* case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX: */
        /*     set_oneshot_layer(xcase_delimiter & 0xFF, 1); */
        /*     break; */
        default:
            tap_code16(xcase_delimiter);
            break;
    }
}

static void remove_delimiter(void) {
    switch (xcase_delimiter) {
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            clear_oneshot_mods();
            break;
        /* case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX: */
        /*     set_oneshot_layer(xcase_delimiter & 0xFF, 0); */
        /*     break; */
        default:
            tap_code(KC_BSPC);
            break;
    }
}

// overrideable function to determine whether the case mode should stop
__attribute__ ((weak))
bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case KC_MINS:
            case KC_BSPC:
                // If mod chording disable the mods
                if (record->event.pressed && (get_mods() != 0)) {
                    return true;
                }
                break;
            default:
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
        return false;
}

bool process_case_modes(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on || xcase_state) {
        // Get the base keycode of a mod or layer tap key
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0)
                    return true;
                keycode = keycode & 0xFF;
                break;
            default:
                break;
        }

        if (record->event.pressed) {
            // grab the next input to be the delimiter
            if (xcase_state == XCASE_WAIT) {
                enable_xcase_with(keycode);
                return false;
            }
            // handle xcase mode
            else if (xcase_state == XCASE_ON) {
                // place the delimiter if space is tapped
                if (keycode == KC_SPACE) {
                    if (distance_to_last_delim != 0) {
                        place_delimiter();
                        distance_to_last_delim = 0;
                        return false;
                    }
                    // remove the delimiter and disable modes
                    else {
                        remove_delimiter();
                        disable_xcase();
                        disable_caps_word();
                        return true;
                    }
                }
                // decrement distance to delimiter on back space
                else if (keycode == KC_BSPC) {
                    --distance_to_last_delim;
                }
                // don't increment distance to last delim if negative
                else if (distance_to_last_delim >= 0) {
                    // puts back a one shot delimiter if you we're back to the delimiter pos
                    if (distance_to_last_delim == 0 &&
                        ((xcase_delimiter >= QK_ONE_SHOT_MOD && xcase_delimiter <= QK_ONE_SHOT_MOD_MAX))) {//|| (keycode >= QK_ONE_SHOT_LAYER && keycode <= QK_ONE_SHOT_LAYER_MAX))) {
                        place_delimiter();
                    }
                    ++distance_to_last_delim;
                }
            }
        }

        // check if the case modes have been terminated
        if (terminate_case_modes(keycode, record)) {
            disable_caps_word();
            disable_xcase();
        }
#ifdef CAPSWORD_USE_SHIFT
        else if (keycode >= KC_A && keycode <= KC_Z){
            if (record->event.pressed) {
                tap_code16(LSFT(keycode));
            }
            return false;
        }
#endif
        return true;
    }
    return true;
}

