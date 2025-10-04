/*
Copyright 2021 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "lib/keyball/keyball.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif
#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#    include "drivers/pmw3360/pmw3360.h"
#endif

//////////////////////////////////////////////////////////////////////////////

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
};
// clang-format on

void keyball_on_adjust_layout(keyball_adjust_t v) {
#ifdef RGBLIGHT_ENABLE
    // adjust RGBLIGHT's clipping and effect ranges
    uint8_t lednum_this = keyball.this_have_ball ? 22 : 24;
    uint8_t lednum_that = !keyball.that_enable ? 0 : keyball.that_have_ball ? 22 : 24;
    rgblight_set_clipping_range(is_keyboard_left() ? 0 : lednum_that, lednum_this);
    rgblight_set_effect_range(0, lednum_this + lednum_that);
#endif
}

#ifdef SPLIT_KEYBOARD
bool is_keyboard_master_impl(void);

static bool keyball39_is_left       = true;
static bool keyball39_hand_detected = false;

// Keyball39 はトラックボール搭載側で左右を判定する想定。
// 標準では右手側にトラックボールを置くため、左手搭載時は KEYBALL39_TRACKBALL_ON_LEFT を有効にする。
static void keyball39_detect_hand(void) {
    if (keyball39_hand_detected) {
        return;
    }
#    ifdef POINTING_DEVICE_ENABLE
    bool has_ball = keyball.this_have_ball;
    if (!has_ball) {
        has_ball               = pmw3360_init();
        keyball.this_have_ball = has_ball;
    }
#        ifdef KEYBALL39_TRACKBALL_ON_LEFT
    keyball39_is_left = has_ball;
#        else
    keyball39_is_left = !has_ball; // 既定ではトラックボール搭載側を右手とみなす。左手搭載の場合は config.h で KEYBALL39_TRACKBALL_ON_LEFT を定義する。
#        endif
#    else
    keyball39_is_left = !is_keyboard_master_impl();
#    endif
    keyball39_hand_detected = true;
}
#endif

void keyboard_pre_init_kb(void) {
#ifdef POINTING_DEVICE_ENABLE
    keyball.this_have_ball = pmw3360_init();
#endif
#ifdef SPLIT_KEYBOARD
    keyball39_hand_detected = false;
    keyball39_detect_hand();
#endif
    keyboard_pre_init_user();
}

#ifdef SPLIT_KEYBOARD
bool is_keyboard_left_impl(void) {
    keyball39_detect_hand();
    return keyball39_is_left;
}

bool is_keyboard_left(void) {
    keyball39_detect_hand();
    return keyball39_is_left;
}
#endif
