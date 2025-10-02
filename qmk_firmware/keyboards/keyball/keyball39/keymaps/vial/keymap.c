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
    // Key Matrix to LED Index
   {
    {     0,     1,     2,     3,     4, NO_LED }, \
    {     5,     6,     7,     8,     9, NO_LED }, \
    {    10,    11,    12,    13,    14, NO_LED }, \
    {    15,    16,    17,    18,    19,    20 }, \
    {    21,    22,    23,    24,    25, NO_LED }, \
    {    26,    27,    28,    29,    30, NO_LED }, \
    {    31,    32,    33,    34,    35, NO_LED }, \
    {    36,    37,    38,    39,    40,    41 }, \
   },
    // LED Index to physical position
   {
    { 10,  0}, // 0
    { 30,  0}, // 1
    { 50,  0}, // 2
    { 70,  0}, // 3
    { 90,  0}, // 4
    { 10, 22}, // 5
    { 30, 22}, // 6
    { 50, 22}, // 7
    { 70, 22}, // 8
    { 90, 22}, // 9
    { 10, 44}, //10
    { 30, 44}, //11
    { 50, 44}, //12
    { 70, 44}, //13
    { 90, 44}, //14
    {  5, 66}, //15
    { 25, 66}, //16
    { 45, 66}, //17
    { 65, 66}, //18
    { 85, 66}, //19
    {105, 66}, //20
    {230,  0}, //21
    {210,  0}, //22
    {190,  0}, //23
    {170,  0}, //24
    {150,  0}, //25
    {230, 22}, //26
    {210, 22}, //27
    {190, 22}, //28
    {170, 22}, //29
    {150, 22}, //30
    {230, 44}, //31
    {210, 44}, //32
    {190, 44}, //33
    {170, 44}, //34
    {150, 44}, //35
    {235, 66}, //36
    {215, 66}, //37
    {195, 66}, //38
    {175, 66}, //39
    {155, 66}, //40
    {135, 66}, //41
    { 40, 90}, //42
    { 70, 90}, //43
    {100, 90}, //44
    {150, 90}, //45
    {180, 90}, //46
    {210, 90}, //47
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
    LED_FLAG_NONE,      //42
    LED_FLAG_NONE,      //43
    LED_FLAG_NONE,      //44
    LED_FLAG_NONE,      //45
    LED_FLAG_NONE,      //46
    LED_FLAG_NONE       //47
   }
};
#endif
