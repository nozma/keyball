#include QMK_KEYBOARD_H

// ヘッダタイトル
static const char PROGMEM img_title[] = {
    0x3e, 0x63, 0x41, 0x41, 0x22, 0x00, 0x7c, 0x14, 0x08, 0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x08, 0x7f, 0x49, 0x41, 0x22, 0x1c, 0x00, 0x74, 0x00, 0x38, 0x40, 0x38
};

// 猫足跡アイコン
static const char PROGMEM img_num0[] = {
 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 
	0x00, 0x00, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x70, 0xfc, 0xfc, 0xfc, 0xfc, 0x70, 0x01, 0x03, 0x87, 0xc7, 0xe7, 0xe3, 0xf1, 0xf8, 0xf8, 
	0xf8, 0xf8, 0xf1, 0xe3, 0xe7, 0xc7, 0x87, 0x03, 0x01, 0x70, 0xfc, 0xfc, 0xfc, 0xfc, 0x70, 0x00, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0xc1, 0xf8, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xc1, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x3f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const char PROGMEM img_num1[] = {
 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0xc0, 0x80, 0x38, 0x7c, 0x38, 0x00, 0x38, 0x7c, 0x38, 0x80, 0xc0, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x0b, 0x19, 0x1c, 0x3e, 0x3f, 0x1f, 0x3f, 0x3e, 0x1c, 0x19, 0x0b, 0x01, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const char PROGMEM img_num2[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0xc0, 0x80, 0x38, 0x7c, 0x38, 0x00, 0x38, 0x7c, 0x38, 0x80, 0xc0, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x0b, 0x19, 0x1c, 0x3e, 0x3f, 0x1f, 0x3f, 0x3e, 0x1c, 0x19, 0x0b, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x70, 0xf8, 0x70, 0x00, 0x70, 0xf8, 0x70, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x17, 0x33, 0x38, 0x7c, 0x7e, 0x3e, 0x7e, 0x7c, 0x38, 0x33, 0x17, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const char PROGMEM img_num3[] = {
	0x00, 0x00, 0x80, 0xc0, 0x80, 0x38, 0x7c, 0x38, 0x00, 0x38, 0x7c, 0x38, 0x80, 0xc0, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x0b, 0x19, 0x1c, 0x3e, 0x3f, 0x1f, 0x3f, 0x3e, 0x1c, 0x19, 0x0b, 0x01, 0x00, 
	0x00, 0x80, 0xc0, 0x80, 0x38, 0x7c, 0x38, 0x00, 0x38, 0x7c, 0x38, 0x80, 0xc0, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x80, 0x00, 0x70, 0xf8, 0x70, 0x00, 0x70, 0xf8, 0x70, 0x00, 0x80, 0x00, 0x00, 
	0x00, 0x01, 0x0b, 0x19, 0x1c, 0x3e, 0x3f, 0x1f, 0x3f, 0x3e, 0x1c, 0x19, 0x0b, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x17, 0x33, 0x38, 0x7c, 0x7e, 0x3e, 0x7e, 0x7c, 0x38, 0x33, 0x17, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const char PROGMEM img_num4[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xc0, 0x00, 0xc0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0xe0, 0xc0, 0x1c, 0x3e, 0x9c, 0x80, 0x9c, 0x3e, 0x1c, 0xc0, 0xe0, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x0c, 0x5e, 0xcc, 0xe1, 0xf3, 0xf9, 0xf8, 0xf9, 0xf3, 0xe1, 0xcc, 0x5e, 0x0c, 0x00, 
	0x00, 0x00, 0x05, 0x0c, 0x8e, 0x1f, 0x1f, 0x0f, 0x9f, 0x1f, 0x0e, 0x0c, 0x05, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x70, 0xf8, 0x71, 0x01, 0x70, 0xf9, 0x71, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x30, 0x78, 0x30, 0x87, 0xcf, 0xe7, 0xe0, 0xe7, 0xcf, 0x87, 0x30, 0x78, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x17, 0x33, 0x38, 0x7c, 0x7e, 0x3e, 0x7e, 0x7c, 0x38, 0x33, 0x17, 0x03, 0x00, 0x00, 
	0x00, 0x01, 0x03, 0x03, 0x07, 0x07, 0x03, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00
};

// スクロールアイコン
static const char PROGMEM img_scroll_up[] = {
	0x00, 0x80, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x86, 0x86, 0xc3, 
	0xc3, 0x86, 0x86, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x80, 0x00, 
	0xc3, 0x61, 0x61, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 
	0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x61, 0x61, 0xc3
};
static const char PROGMEM img_scroll_down[] = {
    0xc3, 0x86, 0x86, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x80, 0x00, 
    0x00, 0x80, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x86, 0x86, 0xc3, 
    0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x61, 0x61, 0xc3, 
    0xc3, 0x61, 0x61, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00
};
static const char PROGMEM img_scroll_no[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

// 数値を文字列に変換します。指定桁数の右寄せでスペースパディングされます。
static const char *itoc(uint8_t number, uint8_t width) {
    static char str[5]; 
    uint8_t i = 0;
    width = width > 4 ? 4 : width;

    do {
        str[i++] = number % 10 + '0';
        number /= 10;
    } while (number != 0);

    while (i < width) {
        str[i++] = ' ';
    }

    int len = i;
    for (int j = 0; j < len / 2; j++) {
        char temp = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = temp;
    }

    str[i] = '\0';
    return str;
}

// CPI, スクロール情報表示
static void print_cpi_status(void) {
    oled_write_raw_P(img_title, sizeof(img_title));
    oled_set_cursor(0, 2);

    oled_write(itoc(keyball_get_cpi(), 0), false);
    oled_write_P(PSTR(" "), false);
    
    oled_set_cursor(4, 2);
    oled_write_char('0' + keyball_get_scroll_div(), false);
}

// レイヤーNo表示
static void print_layer_status(void) {
    oled_set_cursor(0, 10);
    switch (get_highest_layer(layer_state)) {
        case 1:  oled_write_raw_P(img_num1, sizeof(img_num1)); break;
        case 2:  oled_write_raw_P(img_num2, sizeof(img_num2)); break;
        case 3:  oled_write_raw_P(img_num3, sizeof(img_num3)); break;
        case 4:  oled_write_raw_P(img_num4, sizeof(img_num4)); break;
        default: oled_write_raw_P(img_num0, sizeof(img_num0)); break;
    }
}

// スクロール状態表示
static void print_scroll_status(void) {
    oled_set_cursor(0, 8);
    oled_write_raw_P(keyball.scroll_mode ? img_scroll_up : img_scroll_no, sizeof(img_scroll_no));
    oled_set_cursor(0, 14);
    oled_write_raw_P(keyball.scroll_mode ? img_scroll_down : img_scroll_no, sizeof(img_scroll_no));
}

// LEDステータス表示
//static void print_led_status(void) {
//    oled_set_cursor(0, 5);
//    oled_write_P(rgblight_is_enabled() ? PSTR("led o") : PSTR("led -"), false);
//    oled_write_P(PSTR("spd "), false);
//    oled_write(itoc(rgblight_get_speed(), 0), false);
//    oled_write_P(PSTR("mo"), false);
//    oled_write(itoc(rgblight_get_mode(), 3), false);
//}

// キーを押した回数のカウント
static uint16_t type_count = 0;
void count_type(void) {
    type_count++;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        count_type();
    }
#endif
    return true;
}

// WPM, type count表示
static void print_wpm_type_count(void) {
    // WPM表示
    oled_set_cursor(0, 4);
    static char wpm[5];
    oled_write_ln_P(PSTR("WPM"), false);
    itoa(get_current_wpm(), wpm, 10);
    oled_write_ln(wpm, false);
    // type count表示
    static char type_count_str[7];
    oled_write_ln_P(PSTR("Count"), false);
    itoa(type_count, tyep_count_str, 10);
    oled_write_ln(type_count_str, false);
}

// デフォルトページ表示
static void render_default(void) {
    print_cpi_status();
    print_wpm();
    print_layer_status();
    print_scroll_status();
}

// OLEDメイン処理(メイン側)
void keyball_oled_render_mymain(void) {
    render_default();
}
