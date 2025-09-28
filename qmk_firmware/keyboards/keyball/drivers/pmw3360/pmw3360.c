/*
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

#include "quantum.h"
#include "pmw3360.h"

#if defined(MCU_RP)
#    include "hardware/spi.h"
#    include "hardware/gpio.h"
#    include "hardware/clocks.h"
static spi_inst_t *const pmw3360_spi_instance = spi0;
static bool             pmw3360_spi_initialized = false;

#    define PMW_SPI_WRITE(data) pmw3360_spi_transfer((data))
#    define PMW_SPI_READ()       pmw3360_spi_transfer(0x00)
#    define PMW_SPI_STOP()       pmw3360_cs_high()
#    define PMW3360_SPI_DIVISOR (clock_get_hz(clk_sys) / PMW3360_CLOCKS)

static inline void pmw3360_cs_low(void) {
    gpio_put(PMW3360_NCS_PIN, 0);
}

static inline void pmw3360_cs_high(void) {
    gpio_put(PMW3360_NCS_PIN, 1);
}

static inline uint8_t pmw3360_spi_transfer(uint8_t data) {
    uint8_t rx = 0;
    spi_write_read_blocking(pmw3360_spi_instance, &data, &rx, 1);
    return rx;
}
#else
#    define PMW_SPI_WRITE(data) spi_write((data))
#    define PMW_SPI_READ()       spi_read()
#    define PMW_SPI_STOP()       spi_stop()
#    define PMW3360_SPI_DIVISOR (F_CPU / PMW3360_CLOCKS)
#endif

// Include SROM definitions.
#include "srom_0x04.c"
#include "srom_0x81.c"

#define PMW3360_SPI_MODE 3
#define PMW3360_CLOCKS 2000000

static bool motion_bursting = false;

void pmw3360_spi_init(void) {
#if defined(MCU_RP)
    if (!pmw3360_spi_initialized) {
        spi_init(pmw3360_spi_instance, PMW3360_CLOCKS);
        spi_set_format(pmw3360_spi_instance, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
        gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
        gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
        gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);
        gpio_init(PMW3360_NCS_PIN);
        gpio_set_dir(PMW3360_NCS_PIN, GPIO_OUT);
        pmw3360_cs_high();
        pmw3360_spi_initialized = true;
    }
#else
    spi_init();
    setPinOutput(PMW3360_NCS_PIN);
    writePinHigh(PMW3360_NCS_PIN);
#endif
}

bool pmw3360_spi_start(void) {
#if defined(MCU_RP)
    pmw3360_cs_low();
    return true;
#else
    return spi_start(PMW3360_NCS_PIN, false, PMW3360_SPI_MODE, PMW3360_SPI_DIVISOR);
#endif
}

uint8_t pmw3360_reg_read(uint8_t addr) {
    pmw3360_spi_start();
#if defined(MCU_RP)
    pmw3360_spi_transfer(addr & 0x7f);
#else
    spi_write(addr & 0x7f);
#endif
    wait_us(160);
#if defined(MCU_RP)
    uint8_t data = pmw3360_spi_transfer(0x00);
#else
    uint8_t data = pmw3360_spi_read();
#endif
    wait_us(1);
#if defined(MCU_RP)
    pmw3360_cs_high();
#else
    spi_stop();
#endif
    wait_us(19);
    if (addr != pmw3360_Motion_Burst) {
        motion_bursting = false;
    }
    return data;
}

void pmw3360_reg_write(uint8_t addr, uint8_t data) {
    pmw3360_spi_start();
#if defined(MCU_RP)
    pmw3360_spi_transfer(addr | 0x80);
    pmw3360_spi_transfer(data);
#else
    spi_write(addr | 0x80);
    spi_write(data);
#endif
    wait_us(35);
#if defined(MCU_RP)
    pmw3360_cs_high();
#else
    spi_stop();
#endif
    wait_us(145);
}

uint8_t pmw3360_cpi_get(void) {
    return pmw3360_reg_read(pmw3360_Config1);
}

void pmw3360_cpi_set(uint8_t cpi) {
    if (cpi > pmw3360_MAXCPI) {
        cpi = pmw3360_MAXCPI;
    }
    pmw3360_reg_write(pmw3360_Config1, cpi);
}

static uint32_t pmw3360_timer      = 0;
static uint32_t pmw3360_scan_count = 0;
static uint32_t pmw3360_last_count = 0;

void pmw3360_scan_perf_task(void) {
    pmw3360_scan_count++;
    uint32_t now = timer_read32();
    if (TIMER_DIFF_32(now, pmw3360_timer) > 1000) {
#if defined(CONSOLE_ENABLE)
        dprintf("pmw3360 scan frequency: %lu\n", pmw3360_scan_count);
#endif
        pmw3360_last_count = pmw3360_scan_count;
        pmw3360_scan_count = 0;
        pmw3360_timer      = now;
    }
}

uint32_t pmw3360_scan_rate_get(void) {
    return pmw3360_last_count;
}

bool pmw3360_motion_read(pmw3360_motion_t *d) {
#ifdef DEBUG_PMW3360_SCAN_RATE
    pmw3360_scan_perf_task();
#endif
    uint8_t mot = pmw3360_reg_read(pmw3360_Motion);
    if ((mot & 0x88) != 0x80) {
        return false;
    }
    d->y = pmw3360_reg_read(pmw3360_Delta_X_L);
    d->y |= pmw3360_reg_read(pmw3360_Delta_X_H) << 8;
    d->x = pmw3360_reg_read(pmw3360_Delta_Y_L);
    d->x |= pmw3360_reg_read(pmw3360_Delta_Y_H) << 8;
    return true;
}

bool pmw3360_motion_burst(pmw3360_motion_t *d) {
#ifdef DEBUG_PMW3360_SCAN_RATE
    pmw3360_scan_perf_task();
#endif
    if (!motion_bursting) {
        pmw3360_reg_write(pmw3360_Motion_Burst, 0);
        motion_bursting = true;
    }

    pmw3360_spi_start();
    PMW_SPI_WRITE(pmw3360_Motion_Burst);
    wait_us(35);
    PMW_SPI_READ(); // skip MOT
    PMW_SPI_READ(); // skip Observation
    d->y = PMW_SPI_READ();
    d->y |= PMW_SPI_READ() << 8;
    d->x = PMW_SPI_READ();
    d->x |= PMW_SPI_READ() << 8;
    PMW_SPI_STOP();
    wait_us(1);
    return true;
}

bool pmw3360_init(void) {
    uprintf("pmw_debug: spi_init\n");
    pmw3360_spi_init();

    uprintf("pmw_debug: spi_start\n");
    bool ok = pmw3360_spi_start();
    uprintf("pmw_debug: spi_start returned %d\n", ok);
    if (!ok) {
        uprintf("pmw_debug: spi_start failed\n");
        return false;
    }

    uprintf("pmw_debug: reset\n");
    pmw3360_reg_write(pmw3360_Power_Up_Reset, 0x5a);
    wait_ms(50);

    uprintf("pmw_debug: clear regs\n");
    pmw3360_reg_read(pmw3360_Motion);
    pmw3360_reg_read(pmw3360_Delta_X_L);
    pmw3360_reg_read(pmw3360_Delta_X_H);
    pmw3360_reg_read(pmw3360_Delta_Y_L);
    pmw3360_reg_read(pmw3360_Delta_Y_H);

    uprintf("pmw_debug: config2\n");
    pmw3360_reg_write(pmw3360_Config2, 0x00);

    uprintf("pmw_debug: read pid\n");
    uint8_t pid = pmw3360_reg_read(pmw3360_Product_ID);
    uint8_t rev = pmw3360_reg_read(pmw3360_Revision_ID);
    PMW_SPI_STOP();

    uprintf("pmw_debug: pid=%02X rev=%02X\n", pid, rev);
    return pid == 0x42 && rev == 0x01;
}

uint8_t pmw3360_srom_id = 0;

void pmw3360_srom_upload(pmw3360_srom_t srom) {
    pmw3360_reg_write(pmw3360_Config2, 0x00);
    pmw3360_reg_write(pmw3360_SROM_Enable, 0x1d);
    wait_us(10);
    pmw3360_reg_write(pmw3360_SROM_Enable, 0x18);

    pmw3360_spi_start();
    PMW_SPI_WRITE(pmw3360_SROM_Load_Burst | 0x80);
    wait_us(15);
    for (size_t i = 0; i < srom.len; i++) {
        uint8_t byte = pgm_read_byte(srom.data + i);
        PMW_SPI_WRITE(byte);
        wait_us(15);
    }
    PMW_SPI_STOP();
    wait_us(200);

    pmw3360_srom_id = pmw3360_reg_read(pmw3360_SROM_ID);
    pmw3360_reg_write(pmw3360_Config2, 0x00);
    wait_ms(10);
}
