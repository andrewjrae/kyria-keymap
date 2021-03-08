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

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
#endif

// Save firmware space
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// Enable eeprom hand definitions
#define EE_HANDS

// Leader key settings
#define LEADER_SEQ_ESC KC_ESC
#define LEADER_TIMEOUT 200
#define LEADER_PER_KEY_TIMING

// Combo settings
#define COMBO_COUNT 4
#define COMBO_TERM 50

// Tapping settings
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD

#define ONESHOT_TIMEOUT 400

/* Default all the mods to be one shot */
#define MY_ESC LT(_NAV, KC_ESC)
#define MY_BSPC LT(_SYM, KC_BSPC)
#define MY_ENT LT(_NUM, KC_ENT)

#define MY_SPC LT(_NAV, KC_SPC)
#define MY_LSFT OSM(MOD_LSFT)
#define MY_RSFT OSM(MOD_RSFT)
#define MY_RCTL MT(MOD_RCTL, KC_TAB)
#define MY_LALT MT(MOD_LALT, KC_ESC)

/* Define some simple vi motions */
#define VI_B   LCTL(KC_LEFT)
#define VI_W   LCTL(KC_RIGHT)
