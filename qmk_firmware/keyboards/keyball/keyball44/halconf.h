#pragma once

/* OLED */
#ifdef OLED_ENABLE

#define HAL_USE_I2C TRUE

#endif

#define HAL_USE_SPI                 TRUE

#include_next "halconf.h"
