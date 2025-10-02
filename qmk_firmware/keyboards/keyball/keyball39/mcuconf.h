#pragma once
#include_next "mcuconf.h"

/* OLED */
#ifdef OLED_ENABLE

#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 FALSE
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE


#endif

#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE

