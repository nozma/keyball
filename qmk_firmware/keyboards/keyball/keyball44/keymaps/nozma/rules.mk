RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812

OLED_ENABLE = yes

VIA_ENABLE = yes

OLED_DRIVER_ENABLE = yes
OLED_DRIVER = ssd1306

#BOARD = GENERIC_RP_RP2040

WS2812_DRIVER = vendor # RP2040用に追加
SERIAL_DRIVER = vendor # RP2040用に分割キーボードで追加

# for bongo.h
WPM_ENABLE = yes
