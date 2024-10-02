/*
Copyright 2022 @Yowkees
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
#ifdef BONGO_ENABLE
#include "bongo.h"
#endif

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),
  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                  _______  , _______ , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1,KC_LNG2):
            return true;
        case LT(2,KC_INT2):
            return true;
        default:
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1,KC_LNG2):
            return 0;
        case LT(2,KC_INT2):
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"
#include "custom_oled.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    //if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    //}
    // return OLED_ROTATION_180;
}

// メイン、サブの判定
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        keyball_oled_render_mymain();
    } else {
        draw_bongo(false);
    }
    return true;
}
#endif

// RGB_MATRIX
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    // Key Matrix to LED Index
    /* layout image
      C1   C2   C3   C4   C5   C6   C7     C10  C11  C12  C13  C14  C15  C16
 L1 { 17,  14,  10,   6,   3,   0,               56,  53,  50,  47,  43,  40},
 L2 { 18,  15,  11,   7,   4,   1,               57,  54,  51,  48,  44,  41},
 L3 { 19,  16,  12,   8,   5,   2,               58,  55,  52,  49,  45,  42},
 L4 {           13,   9,  27,  28,  29,     30,  31,                 46     } 
    */
   {
    {    17,    14,    10,     6,     3,     0 }, \
    {    18,    15,    11,     7,     4,     1 }, \
    {    19,    16,    12,     8,     5,     2 }, \
    {NO_LED,    13,     9,    27,    28,    29 }, \
    {    40,    43,    47,    50,    53,    56 }, \
    {    41,    44,    48,    51,    54,    57 }, \
    {    42,    45,    49,    52,    55,    58 }, \
    {NO_LED,    46,NO_LED,NO_LED,    31,    30 }, \
   },
    // LED Index to phisical poisiton
   {
    {90, 21}, //0
    {90, 43}, //1
    {90, 64}, //2
    {75, 21}, //3
    {75, 43}, //4
    {75, 64}, //5
    {60, 21}, //6
    {60, 43}, //7
    {60, 64}, //8
    {60, 85}, //9
    {45, 21}, //10
    {45, 43}, //11
    {45, 64}, //12
    {45, 85}, //13
    {30, 21}, //14
    {30, 43}, //15
    {30, 64}, //16
    {15, 21}, //17
    {15, 43}, //18
    {15, 64}, //19
    {0, 0}, //20
    {0, 0}, //21
    {0, 0}, //22
    {0, 0}, //23
    {0, 0}, //24
    {0, 0}, //25
    {0, 0}, //26
    {75, 85}, //27
    {90, 85}, //28
    {105, 85}, //29
    {149, 85}, //30
    {164, 85}, //31
    {0, 0}, //32
    {0, 0}, //33
    {0, 0}, //34
    {0, 0}, //35
    {0, 0}, //36
    {0, 0}, //37
    {0, 0}, //38
    {0, 0}, //39
    {239, 21}, //40
    {239, 43}, //41
    {239, 64}, //42
    {224, 21}, //43
    {224, 43}, //44
    {224, 64}, //45
    {224, 85}, //46
    {209, 21}, //47
    {209, 43}, //48
    {209, 64}, //49
    {194, 21}, //50
    {194, 43}, //51
    {194, 64}, //52
    {179, 21}, //53
    {179, 43}, //54
    {179, 64}, //55
    {164, 21}, //56
    {164, 43}, //57
    {164, 64}, //58
    {0, 0} //59
   },
    // LED Index to Flag
   {
    LED_FLAG_KEYLIGHT, //0
    LED_FLAG_KEYLIGHT, //1
    LED_FLAG_KEYLIGHT, //2
    LED_FLAG_KEYLIGHT, //3
    LED_FLAG_KEYLIGHT, //4
    LED_FLAG_KEYLIGHT, //5
    LED_FLAG_KEYLIGHT, //6
    LED_FLAG_KEYLIGHT, //7
    LED_FLAG_KEYLIGHT, //8
    LED_FLAG_KEYLIGHT, //9
    LED_FLAG_KEYLIGHT, //10
    LED_FLAG_KEYLIGHT, //11
    LED_FLAG_KEYLIGHT, //12
    LED_FLAG_KEYLIGHT, //13
    LED_FLAG_KEYLIGHT, //14
    LED_FLAG_KEYLIGHT, //15
    LED_FLAG_KEYLIGHT, //16
    LED_FLAG_KEYLIGHT, //17
    LED_FLAG_KEYLIGHT, //18
    LED_FLAG_KEYLIGHT, //19
    LED_FLAG_NONE, //20
    LED_FLAG_NONE, //21
    LED_FLAG_NONE, //22
    LED_FLAG_NONE, //23
    LED_FLAG_NONE, //24
    LED_FLAG_NONE, //25
    LED_FLAG_NONE, //26
    LED_FLAG_KEYLIGHT, //27
    LED_FLAG_KEYLIGHT, //28
    LED_FLAG_KEYLIGHT, //29
    LED_FLAG_KEYLIGHT, //30
    LED_FLAG_KEYLIGHT, //31
    LED_FLAG_NONE, //32
    LED_FLAG_NONE, //33
    LED_FLAG_NONE, //34
    LED_FLAG_NONE, //35
    LED_FLAG_NONE, //36
    LED_FLAG_NONE, //37
    LED_FLAG_NONE, //38
    LED_FLAG_NONE, //39
    LED_FLAG_KEYLIGHT, //40
    LED_FLAG_KEYLIGHT, //41
    LED_FLAG_KEYLIGHT, //42
    LED_FLAG_KEYLIGHT, //43
    LED_FLAG_KEYLIGHT, //44
    LED_FLAG_KEYLIGHT, //45
    LED_FLAG_KEYLIGHT, //46
    LED_FLAG_KEYLIGHT, //47
    LED_FLAG_KEYLIGHT, //48
    LED_FLAG_KEYLIGHT, //49
    LED_FLAG_KEYLIGHT, //50
    LED_FLAG_KEYLIGHT, //51
    LED_FLAG_KEYLIGHT, //52
    LED_FLAG_KEYLIGHT, //53
    LED_FLAG_KEYLIGHT, //54
    LED_FLAG_KEYLIGHT, //55
    LED_FLAG_KEYLIGHT, //56
    LED_FLAG_KEYLIGHT, //57
    LED_FLAG_KEYLIGHT, //58
    LED_FLAG_NONE //59
   }
};
#endif