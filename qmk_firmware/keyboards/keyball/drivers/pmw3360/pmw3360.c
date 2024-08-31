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
#ifdef F_CPU
#define PMW3360_SPI_DIVISOR (F_CPU / PMW3360_CLOCKS)
#else
#define PMW3360_SPI_DIVISOR (clock_get_hz(clk_sys) / PMW3360_CLOCKS)
#endif
#define PMW3360_CLOCKS 2000000

static bool motion_bursting = false;

bool pmw3360_spi_start(void) {
    return spi_start(PMW3360_NCS_PIN, false, PMW3360_SPI_MODE, PMW3360_SPI_DIVISOR);
}

uint8_t pmw3360_reg_read(uint8_t addr) {
    pmw3360_spi_start();
    spi_write(addr & 0x7f);
    wait_us(160);
    uint8_t data = spi_read();
    wait_us(1);
    spi_stop();
    wait_us(19);
    // Reset motion_bursting mode if read from a register other than motion
    // burst register.
    if (addr != pmw3360_Motion_Burst) {
        motion_bursting = false;
    }
    return data;
}

void pmw3360_reg_write(uint8_t addr, uint8_t data) {
    pmw3360_spi_start();
    spi_write(addr | 0x80);
    spi_write(data);
    wait_us(35);
    spi_stop();
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
    if ((mot & 0x80) == 0) {
        return false; // データが利用できない場合は false を返す
    }

    d->x = pmw3360_reg_read(pmw3360_Delta_X_L);
    d->x |= pmw3360_reg_read(pmw3360_Delta_X_H) << 8;
    d->y = pmw3360_reg_read(pmw3360_Delta_Y_L);
    d->y |= pmw3360_reg_read(pmw3360_Delta_Y_H) << 8;

    return true;
}

bool pmw3360_motion_burst(pmw3360_motion_t *d) {
#ifdef DEBUG_PMW3360_SCAN_RATE
    pmw3360_scan_perf_task();
#endif
    // Start motion burst if motion burst mode is not started.
    if (!motion_bursting) {
        pmw3360_reg_write(pmw3360_Motion_Burst, 0);
        motion_bursting = true;
    }

    pmw3360_spi_start();
    spi_write(pmw3360_Motion_Burst);
    wait_us(35);
    spi_read(); // skip MOT
    spi_read(); // skip Observation
    d->x = spi_read();
    d->x |= spi_read() << 8;
    d->y = spi_read();
    d->y |= spi_read() << 8;
    spi_stop();
    // Required NCS in 500ns after motion burst.
    wait_us(1);
    return true;
}

#include "oled_driver.h"
#include "stdio.h"
#include "spi_master.h"  // QMKのSPI通信関連のヘッダー

#include <stdio.h> // snprintfを使用するために追加

void oled_write_hex(uint8_t value) {
    char buffer[3]; // 2桁の16進数+終端文字のために3バイト確保
    snprintf(buffer, sizeof(buffer), "%02X", value);
    oled_write(buffer, false);
}

bool pmw3360_spi_test(void) {
    uint8_t test_value = 0xAB;
    uint8_t read_value;

    // テストレジスタに書き込み
    pmw3360_spi_start();
    pmw3360_reg_write(pmw3360_Config2, test_value);
    wait_us(160);
    spi_stop();
    wait_us(160);

    // テストレジスタから読み取り
    pmw3360_spi_start();
    read_value = pmw3360_reg_read(pmw3360_Config2);
    spi_stop();

    // OLEDに結果を表示
    oled_write_ln("SPI Test", false);
    oled_write("Sent: ", false);
    oled_write_hex(test_value);
    oled_write(" Recv: ", false);
    oled_write_hex(read_value);

    return (test_value == read_value);
}

void spi_init(void) {
    // SPI設定
    pin_t slavePin = PMW3360_NCS_PIN;  // 使用しているチップセレクトピン
    bool lsbFirst = false;  // MSBファーストで通信
    uint8_t mode = 3;  // SPIモード3 (CPOL=1, CPHA=1)
    uint16_t divisor = 64;  // 分周値 (例えば、クロック速度を設定)

    // SPI通信を開始
    if (!spi_start(slavePin, lsbFirst, mode, divisor)) {
        oled_write_ln("SPI Init Failed", false);
    }
}

bool pmw3360_init(void) {
    pmw3360_spi_start();

    // テスト実行
    if (!pmw3360_spi_test()) {
        oled_write_ln("SPI Test Failed", false);
        return false;
    }

    // センサーリセット
    pmw3360_reg_write(pmw3360_Power_Up_Reset, 0x5A);
    wait_ms(50); // リセット後の待機

    // モーションデータの読み捨て
    pmw3360_reg_read(pmw3360_Motion);
    pmw3360_reg_read(pmw3360_Delta_X_L);
    pmw3360_reg_read(pmw3360_Delta_X_H);
    pmw3360_reg_read(pmw3360_Delta_Y_L);
    pmw3360_reg_read(pmw3360_Delta_Y_H);

    // センサー設定の初期化
    pmw3360_reg_write(pmw3360_Config2, 0x00);

    // SROMのアップロード
    pmw3360_srom_upload(FIRMWARE);

    // プロダクトIDとリビジョンIDの確認
    uint8_t pid = pmw3360_reg_read(pmw3360_Product_ID);
    uint8_t rev = pmw3360_reg_read(pmw3360_Revision_ID);

    if (pid != 0x42 || rev != 0x01) {
        oled_write_ln("PMW3360 init fail", false);
        return false;
    } else {
        oled_write_ln("PMW3360 init OK", false);
        return true;
    }

    spi_stop();
}

uint8_t pmw3360_srom_id = 0;

void pmw3360_srom_upload(const uint8_t* firmware, size_t firmware_size) {
    pmw3360_reg_write(pmw3360_Config2, 0x00);
    pmw3360_reg_write(pmw3360_SROM_Enable, 0x1D);
    wait_us(10);
    pmw3360_reg_write(pmw3360_SROM_Enable, 0x18);

    pmw3360_spi_start();
    spi_write(pmw3360_SROM_Load_Burst | 0x80);
    wait_us(15);

    for (size_t i = 0; i < firmware_size; i++) {
        spi_write(firmware[i]);
        wait_us(15);
    }

    spi_stop();
    wait_us(200);
}
