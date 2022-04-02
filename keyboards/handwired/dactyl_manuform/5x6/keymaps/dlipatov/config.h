/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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


#pragma once


#define USE_SERIAL

#define EE_HANDS

// Underglow
#undef RGBLED_NUM
#undef RGBLED_SPLIT

#define RGBLIGHT_DISABLE_KEYCODES
#define RGB_DI_PIN D1
#define RGBLED_NUM 24    // Number of LEDs
#define RGBLED_SPLIT { 12, 12 }
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
#define RGBLIGHT_SLEEP
#define RGBLIGHT_DEFAULT_HUE 246
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL


// Layers
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
#define LAYER_STATE_8BIT

//Boogmagic Lite
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

//Tap Dance
#define TAPPING_TERM 200
