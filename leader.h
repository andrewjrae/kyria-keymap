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

#include QMK_KEYBOARD_H

typedef void *(*leader_func_t)(uint16_t);

// Check to see if we are leading
bool is_leading(void);
// Start leader sequence
void start_leading(void);
// Stop leader sequence
void stop_leading(void);

// Process keycode for leader sequences
bool process_leader(uint16_t keycode, const keyrecord_t *record);

#ifdef LEADER_DISPLAY_STR
char *leader_display_str(void);
#endif
