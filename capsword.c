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

#include "capsword.h"

static bool caps_word_on = false;

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

__attribute__ ((weak))
bool terminate_case_mode(uint8_t keycode, const keyrecord_t *record) {
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word), but not to shift
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

bool process_caps_word(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on) {
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

        // check if the case statement has terminated
        if (terminate_case_mode(keycode, record)) {
            disable_caps_word();
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

