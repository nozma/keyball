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

// Include SROM definitions.
#include "srom_0x04.c"
#include "srom_0x81.c"

#define PMW3360_SPI_MODE 3
#define PMW3360_CLOCKS 2000000

static bool motion_bursting = false;

void pmw3360_spi_init(void) {
    spi_init();
    setPinOutput(PMW3360_NCS_PIN);
    writePinHigh(PMW3360_NCS_PIN);
}

bool pmw3360_spi_start(void) {
    writePinLow(PMW3360_NCS_PIN);
    return true;
}

void pmw3360_spi_stop(void) {
    writePinHigh(PMW3360_NCS_PIN);
}

void pmw3360_spi_write(uint8_t data) {
    spi_write(data);  // 修正：元のspi_write関数を使用
}

uint8_t pmw3360_spi_read(void) {
    return spi_read();  // 修正：元のspi_read関数を使用
}

uint8_t pmw3360_reg_read(uint8_t addr) {
    pmw3360_spi_start();
    pmw3360_spi_write(addr & 0x7f);
    wait_us(160);
    uint8_t data = pmw3360_spi_read();
    wait_us(1);
    pmw3360_spi_stop();
    wait_us(19);
    if (addr != pmw3360_Motion_Burst) {
        motion_bursting = false;
    }
    return data;
}

void pmw3360_reg_write(uint8_t addr, uint8_t data) {
    pmw3360_spi_start();
    pmw3360_spi_write(addr | 0x80);
    pmw3360_spi_write(data);
    wait_us(35);
    pmw3360_spi_stop();
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
    uint8_t mot = pmw3360_reg_read(pmw3360_Motion);
    if ((mot & 0x88) != 0x80) {
        return false;
    }
    d->x = -pmw3360_reg_read(pmw3360_Delta_X_L);
    d->x |= -pmw3360_reg_read(pmw3360_Delta_X_H) << 8;
    d->y = -pmw3360_reg_read(pmw3360_Delta_Y_L);
    d->y |= -pmw3360_reg_read(pmw3360_Delta_Y_H) << 8;
    return true;
}

bool pmw3360_motion_burst(pmw3360_motion_t *d) {
    pmw3360_reg_write(pmw3360_Motion_Burst, 0);
    pmw3360_spi_start();
    pmw3360_spi_write(pmw3360_Motion_Burst);
    wait_us(35);
    pmw3360_spi_read(); // skip MOT
    pmw3360_spi_read(); // skip Observation
    d->x = -pmw3360_spi_read();
    d->x |= -pmw3360_spi_read() << 8;
    d->y = -pmw3360_spi_read();
    d->y |= -pmw3360_spi_read() << 8;
    pmw3360_spi_stop();
    wait_us(1);
    return true;
}

bool pmw3360_init(void) {
    pmw3360_spi_init();

    pmw3360_spi_start();
    pmw3360_reg_write(pmw3360_Power_Up_Reset, 0x5a);
    wait_ms(50);

    pmw3360_reg_read(pmw3360_Motion);
    pmw3360_reg_read(pmw3360_Delta_X_L);
    pmw3360_reg_read(pmw3360_Delta_X_H);
    pmw3360_reg_read(pmw3360_Delta_Y_L);
    pmw3360_reg_read(pmw3360_Delta_Y_H);

    pmw3360_reg_write(pmw3360_Config2, 0x00);

    uint8_t pid = pmw3360_reg_read(pmw3360_Product_ID);
    uint8_t rev = pmw3360_reg_read(pmw3360_Revision_ID);
    pmw3360_spi_stop();

    return pid == 0x42 && rev == 0x01;
}

uint8_t pmw3360_srom_id = 0;

void pmw3360_srom_upload(pmw3360_srom_t srom) {
    pmw3360_reg_write(pmw3360_Config2, 0x00);
    pmw3360_reg_write(pmw3360_SROM_Enable, 0x1d);
    wait_us(10);
    pmw3360_reg_write(pmw3360_SROM_Enable, 0x18);

    pmw3360_spi_start();
    pmw3360_spi_write(pmw3360_SROM_Load_Burst | 0x80);
    wait_us(15);
    for (size_t i = 0; i < srom.len; i++) {
        uint8_t byte = pgm_read_byte(srom.data + i);
        pmw3360_spi_write(byte);
        wait_us(15);
    }
    pmw3360_spi_stop();
    wait_us(200);

    pmw3360_srom_id = pmw3360_reg_read(pmw3360_SROM_ID);
    pmw3360_reg_write(pmw3360_Config2, 0x00);
    wait_ms(10);
}