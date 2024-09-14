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
    l  1    2    3    4    5    6    7      10   11   12   13   14   15   16
    { 18,  15,  11,   7,   4,   1,               57,  54,  51,  48,  44,  41}, \ 1
    { 19,  16,  12,   8,   5,   2,               58,  55,  52,  49,  45,  42}, \ 2
    { 20,  17,  13,   9,   6,   3,               59,  56,  53,  50,  46,  43}, \ 3
    {           14,  10,  28,  29,  30,     31,  32,                 47     }  \ 4
    */
   {
    {    18,    15,    11,     7,     4,     1 }, \
    {    19,    16,    12,     8,     5,     2 }, \
    {    20,    17,    13,     9,     6,     3 }, \
    {NO_LED,    14,    10,    28,    29,    30 }, \
    {    41,    44,    48,    51,    54,    57 }, \
    {    42,    45,    49,    52,    55,    58 }, \
    {    43,    46,    50,    53,    56,    59 }, \
    {NO_LED,    47,NO_LED,NO_LED,    32,    31 }, \
   },
    // LED Index to phisical poisiton
   {
    {75, 90}, //1
    {149, 90}, //2
    {224, 90}, //3
    {75, 75}, //4
    {149, 75}, //5
    {224, 75}, //6
    {75, 60}, //7
    {149, 60}, //8
    {224, 60}, //9
    {299, 60}, //10
    {75, 45}, //11
    {149, 45}, //12
    {224, 45}, //13
    {299, 45}, //14
    {75, 30}, //15
    {149, 30}, //16
    {224, 30}, //17
    {75, 15}, //18
    {149, 15}, //19
    {224, 15}, //20
    {0, 0}, //21
    {0, 0}, //22
    {0, 0}, //23
    {0, 0}, //24
    {0, 0}, //25
    {0, 0}, //26
    {0, 0}, //27
    {299, 75}, //28
    {299, 90}, //29
    {299, 105}, //30
    {299, 149}, //31
    {299, 164}, //32
    {0, 0}, //33
    {0, 0}, //34
    {0, 0}, //35
    {0, 0}, //36
    {0, 0}, //37
    {0, 0}, //38
    {0, 0}, //39
    {0, 0}, //40
    {75, 239}, //41
    {149, 239}, //42
    {224, 239}, //43
    {75, 224}, //44
    {149, 224}, //45
    {224, 224}, //46
    {299, 224}, //47
    {75, 209}, //48
    {149, 209}, //49
    {224, 209}, //50
    {75, 194}, //51
    {149, 194}, //52
    {224, 194}, //53
    {75, 179}, //54
    {149, 179}, //55
    {224, 179}, //56
    {75, 164}, //57
    {149, 164}, //58
    {224, 164}, //59
    {0, 0}  //60
   }
    // LED Index to Flag
   {
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
    LED_FLAG_KEYLIGHT, //20
    LED_FLAG_NONE, //21
    LED_FLAG_NONE, //22
    LED_FLAG_NONE, //23
    LED_FLAG_NONE, //24
    LED_FLAG_NONE, //25
    LED_FLAG_NONE, //26
    LED_FLAG_NONE, //27
    LED_FLAG_KEYLIGHT, //28
    LED_FLAG_KEYLIGHT, //29
    LED_FLAG_KEYLIGHT, //30
    LED_FLAG_KEYLIGHT, //31
    LED_FLAG_KEYLIGHT, //32
    LED_FLAG_NONE, //33
    LED_FLAG_NONE, //34
    LED_FLAG_NONE, //35
    LED_FLAG_NONE, //36
    LED_FLAG_NONE, //37
    LED_FLAG_NONE, //38
    LED_FLAG_NONE, //39
    LED_FLAG_NONE, //40
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
    LED_FLAG_KEYLIGHT, //59
    LED_FLAG_NONE //60
   }
}
#endif