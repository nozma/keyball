# MCU name
#MCU = atmega32u4
MCU = RP2040

# Bootloader selection
#BOOTLOADER = caterina
BOOTLOADER = rp2040

# Link Time Optimization required for size.
LTO_ENABLE = yes

# Build Options
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

# Keyball44 is split keyboard.
SPLIT_KEYBOARD = yes

# Optical sensor driver for trackball.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
SRC += drivers/pmw3360/pmw3360.c
QUANTUM_LIB_SRC += spi_master.c # Optical sensor use SPI to communicate

# This is unnecessary for processing KC_MS_BTN*.
MOUSEKEY_ENABLE = no

# Enabled only one of RGBLIGHT and RGB_MATRIX if necessary.
RGBLIGHT_ENABLE = no        # Enable RGBLIGHT
RGB_MATRIX_ENABLE = no      # Enable RGB_MATRIX (not work yet)
RGB_MATRIX_DRIVER = ws2812

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

# To support OLED
OLED_ENABLE = no                # Please Enable this in each keymaps.
SRC += lib/oledkit/oledkit.c    # OLED utility for Keyball series.

# Include common library
SRC += lib/keyball/keyball.c

# Disable other features to squeeze firmware size
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

# Pico SDKのパスを指定
PICO_SDK_PATH = lib/pico-sdk-master

# 必要なCソースファイルのディレクトリを追加
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_spi/spi.c
SRC += $(PICO_SDK_PATH)/src/common/pico_stdlib.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_gpio/gpio.c
SRC += $(PICO_SDK_PATH)/src/rp2_common/hardware_clocks/clocks.c

# インクルードディレクトリを指定
CFLAGS += -I$(PICO_SDK_PATH)/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_spi/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_gpio/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2_common/hardware_clocks/include
CFLAGS += -I$(PICO_SDK_PATH)/src/common/pico_stdlib/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2040/hardware_regs/include
CFLAGS += -I$(PICO_SDK_PATH)/src/rp2040/hardware_structs/include

# 必要なPico SDKのライブラリをリンク
LDFLAGS += -L$(PICO_SDK_PATH)/build/lib
LDFLAGS += -lpico_stdlib -lhardware_spi -lhardware_gpio -lhardware_clocks
