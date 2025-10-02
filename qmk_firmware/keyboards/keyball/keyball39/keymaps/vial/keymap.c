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
#    include "bongo.h"
#endif

#include "quantum.h"
#include "dynamic_keymap.h"
#include "eeconfig.h"
#ifdef VIAL_ENABLE
#    include "raw_hid.h"
#    include "quantum/vial.h"
#endif


enum custom_keycodes {
    USER00 = KEYBALL_SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    LT(3,KC_A), KC_S    , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , LT(4,KC_L), LT(4,KC_SCLN),
    LSFT_T(KC_Z), KC_X  , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMMA , KC_DOT   , RSFT_T(KC_SLSH),
    KC_TAB   , KC_LCTL  , QK_MACRO_0, KC_LALT , LT(1,KC_LNG2), LT(5,KC_ENTER),   LT(6,KC_SPACE), LT(2,KC_LNG1), RCTL_T(KC_LNG2), RALT_T(KC_INT1), KC_NUHS , KC_RBRC
  ),

  [1] = LAYOUT_universal(
    KC_ESC   , LGUI(KC_W), LGUI(KC_E), LGUI(KC_R), LGUI(KC_T),                   S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  , KC_MINS ,
    LGUI(KC_A), LGUI(KC_S), LGUI(KC_D), LGUI(KC_F), LGUI(KC_G),                  LGUI(KC_H), LGUI(KC_J), LGUI(KC_K), LGUI(KC_L), KC_EQUAL,
    LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_B),                  LGUI(KC_N), LGUI(KC_M), LGUI(KC_COMMA), LGUI(KC_DOT), RSFT_T(KC_INT3),
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , LGUI(KC_ENTER), KC_TRNS,    LGUI(KC_SPACE), KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
  ),

  [2] = LAYOUT_universal(
    KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                             KC_6     , KC_7     , KC_8     , KC_9     , KC_0     ,
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                             KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_QUOT ,
    KC_LSFT  , KC_F6    , KC_F7    , KC_F8    , KC_F9    ,                             KC_F10   , KC_F11   , KC_F12   , KC_NO    , KC_RSFT ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
  ),

  [3] = LAYOUT_universal(
    LCTL(KC_Q), LCTL(KC_W), LGUI(KC_RIGHT), LCTL(KC_R), LCTL(KC_T),                 LCTL(KC_Y), LCTL(KC_U), LCTL(KC_I), LCTL(KC_O), KC_UP    ,
    KC_NO    , LCTL(KC_A), KC_DELETE   , KC_RGHT  , LCTL(KC_F),                     KC_BSPC  , LCTL(KC_J), LCTL(KC_K), LCTL(KC_L), LCTL(KC_SCLN),
    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C) , LCTL(KC_V), KC_LEFT ,                      KC_DOWN  , LCTL(KC_M), LCTL(KC_COMMA), LCTL(KC_DOT), LCTL(KC_SLSH),
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , LCTL(KC_ENT), KC_TRNS,   LCTL(KC_SPC), KC_TRNS , KC_TRNS , USER00 , KC_TRNS , KC_TRNS
  ),

  [4] = LAYOUT_universal(
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             LCTL(KC_NUHS), LCTL(G(KC_I)), 0x00C1 , S(KC_L) , KC_TRNS ,
    KC_TRNS , KC_LCTL , KC_TRNS , KC_TRNS , KC_TRNS ,                             S(KC_H) , KC_BTN1 , KC_BTN2 , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_LSFT , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
  ),

  [5] = LAYOUT_universal(
    KC_ESC  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , S(KC_RBRC) , KC_RBRC ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , S(KC_NUHS) , KC_NUHS ,
    KC_TRNS , KC_LSFT , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , S(KC_INT3),
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
  ),

  [6] = LAYOUT_universal(
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , S(KC_LBRC) , KC_LBRC ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , S(KC_QUOT),
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_INT1 ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
  ),

  [7] = LAYOUT_universal(
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,
    KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,     KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
  ),
};
// clang-format on

#ifdef VIAL_COMBO_ENABLE
static void load_default_combos(void) {
    const struct {
        uint16_t input[4];
        uint16_t output;
    } defaults[] = {
        {{KC_Q, KC_W, KC_NO, KC_NO}, KC_TAB},
        {{KC_BTN1, KC_BTN2, KC_NO, KC_NO}, KC_BTN3},
        {{LGUI(KC_Z), LGUI(KC_X), KC_NO, KC_NO}, SGUI(KC_Z)},
        {{KC_NO, KC_NO, KC_NO, KC_NO}, KC_NO},
    };

    vial_combo_entry_t entry;
    for (size_t i = 0; i < VIAL_COMBO_ENTRIES && i < (sizeof(defaults) / sizeof(defaults[0])); ++i) {
        if (dynamic_keymap_get_combo(i, &entry) != 0) {
            continue;
        }

        bool empty = (entry.output == KC_NO);
        if (!empty) {
            for (size_t k = 0; k < 4; ++k) {
                if (entry.input[k] != KC_NO) {
                    empty = false;
                    break;
                }
            }
        }

        if (!empty) {
            continue;
        }

        vial_combo_entry_t def = {0};
        for (size_t k = 0; k < 4; ++k) {
            def.input[k] = defaults[i].input[k];
        }
        def.output = defaults[i].output;
        dynamic_keymap_set_combo(i, &def);
    }
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

void keyboard_post_init_user(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

#ifdef VIAL_ENABLE
#    ifdef VIAL_COMBO_ENABLE
    load_default_combos();
#    endif
    vial_init();
#endif
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"
#    define CUSTOM_OLED_SKIP_PROCESS_RECORD
#    include "custom_oled.c"
#    undef CUSTOM_OLED_SKIP_PROCESS_RECORD

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        keyball_oled_render_mymain();
    } else {
#    ifdef BONGO_ENABLE
        draw_bongo(false);
#    endif
    }
    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        count_type();
    }
#endif
#ifdef VIAL_ENABLE
    if (!process_record_vial(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {
        case QK_MACRO_0:
            if (record->event.pressed) {
                const uint8_t mods = MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT);
                register_mods(mods);
                tap_code(KC_4);
                unregister_mods(mods);
            }
            return false;
    }

    return true;
}

// RGB_MATRIX
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    /* layout image
             C1   C2   C3   C4   C5   C6      C9  C10  C11  C12  C13  C14
        L1 { 14,  10,   6,   3,   0,               43,  40,  37,  34,  30},
        L2 { 15,  11,   7,   4,   1,               44,  41,  38,  35,  31},
        L3 { 16,  12,   8,   5,   2,               45,  42,  39,  36,  32},
        L4 { 17,  13,   9,  22,  23,          24,  25,                 33} 
    */
    // Key Matrix to LED Index
   {
    {    14,    10,     6,     3,     0, NO_LED }, \
    {    15,    11,     7,     4,     1, NO_LED }, \
    {    16,    12,     8,     5,     2, NO_LED }, \
    {    17,    13,     9,    22,    23, NO_LED }, \
    {    30,    34,    37,    40,    43, NO_LED }, \
    {    31,    35,    38,    41,    44, NO_LED }, \
    {    32,    36,    39,    42,    45, NO_LED }, \
    {    33,NO_LED,NO_LED,NO_LED,    25,    24 }, \
   },
    // LED Index to physical position
   {
    { 86, 21}, // 0
    { 86, 43}, // 1
    { 86, 64}, // 2
    { 69, 21}, // 3
    { 69, 43}, // 4
    { 69, 64}, // 5
    { 52, 21}, // 6
    { 52, 43}, // 7
    { 52, 64}, // 8
    { 52, 85}, // 9
    { 34, 21}, // 10
    { 34, 43}, // 11
    { 34, 64}, // 12
    { 34, 85}, // 13
    { 17, 21}, // 14
    { 17, 43}, // 15
    { 17, 64}, // 16
    { 17, 85}, // 17
    { 69, 21}, // 18 (under near 3)
    { 17, 21}, // 19 (under near 14)
    { 17, 64}, // 20 (under near 16)
    { 52, 64}, // 21 (under near 8)
    { 86, 85}, // 22
    { 103, 85}, // 23
    { 155, 85}, // 24
    { 172, 85}, // 25
    { 198, 64}, // 26 (under near 39, 42)
    { 241, 85}, // 27 (under near 32)
    { 241, 21}, // 28 (under near 30)
    { 190, 21}, // 29 (under near 40)
    { 241, 21}, // 30
    { 241, 43}, // 31
    { 241, 64}, // 32
    { 241, 85}, // 33
    { 224, 21}, // 34
    { 224, 43}, // 35
    { 224, 64}, // 36
    { 207, 21}, // 37
    { 207, 43}, // 38
    { 207, 64}, // 39
    { 190, 21}, // 40
    { 190, 43}, // 41
    { 190, 64}, // 42
    { 172, 21}, // 43
    { 172, 43}, // 44
    { 172, 64}, // 45
    { 0, 0}, // 46
    { 0, 0}, // 47
   },
    // LED Index to Flag
   {
    LED_FLAG_KEYLIGHT, // 0
    LED_FLAG_KEYLIGHT, // 1
    LED_FLAG_KEYLIGHT, // 2
    LED_FLAG_KEYLIGHT, // 3
    LED_FLAG_KEYLIGHT, // 4
    LED_FLAG_KEYLIGHT, // 5
    LED_FLAG_KEYLIGHT, // 6
    LED_FLAG_KEYLIGHT, // 7
    LED_FLAG_KEYLIGHT, // 8
    LED_FLAG_KEYLIGHT, // 9
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
    LED_FLAG_KEYLIGHT, //21
    LED_FLAG_KEYLIGHT, //22
    LED_FLAG_KEYLIGHT, //23
    LED_FLAG_KEYLIGHT, //24
    LED_FLAG_KEYLIGHT, //25
    LED_FLAG_KEYLIGHT, //26
    LED_FLAG_KEYLIGHT, //27
    LED_FLAG_KEYLIGHT, //28
    LED_FLAG_KEYLIGHT, //29
    LED_FLAG_KEYLIGHT, //30
    LED_FLAG_KEYLIGHT, //31
    LED_FLAG_KEYLIGHT, //32
    LED_FLAG_KEYLIGHT, //33
    LED_FLAG_KEYLIGHT, //34
    LED_FLAG_KEYLIGHT, //35
    LED_FLAG_KEYLIGHT, //36
    LED_FLAG_KEYLIGHT, //37
    LED_FLAG_KEYLIGHT, //38
    LED_FLAG_KEYLIGHT, //39
    LED_FLAG_KEYLIGHT, //40
    LED_FLAG_KEYLIGHT, //41
    LED_FLAG_KEYLIGHT, //42
    LED_FLAG_KEYLIGHT, //43
    LED_FLAG_KEYLIGHT, //44
    LED_FLAG_KEYLIGHT, //45    
    LED_FLAG_NONE,      //46
    LED_FLAG_NONE       //47
   }
};
#endif
