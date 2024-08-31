#ifndef MY_GPIO_SPI_DEFS_H
#define MY_GPIO_SPI_DEFS_H

#ifndef SIO_BASE
#define SIO_BASE 0xD0000000
#endif

#ifndef SPI0_BASE
#define SPI0_BASE 0x4003C000
#endif

#ifndef IO_BANK0_BASE
#define IO_BANK0_BASE 0x40014000
#endif

// SPI0の基本設定
#define SPI0_CTRLR0         (*(volatile uint32_t *)(SPI0_BASE + 0x000))
#define SPI0_SSIENR         (*(volatile uint32_t *)(SPI0_BASE + 0x008))
#define SPI0_BAUDR          (*(volatile uint32_t *)(SPI0_BASE + 0x014))
#define SPI0_TXDR           (*(volatile uint32_t *)(SPI0_BASE + 0x018))
#define SPI0_RXDR           (*(volatile uint32_t *)(SPI0_BASE + 0x01C))
#define SPI0_SR             (*(volatile uint32_t *)(SPI0_BASE + 0x028))

void rp2040_spi_write(uint8_t data) {
    while (!(SPI0_SR & (1 << 1))) {}  // 送信FIFOが空になるまで待機
    SPI0_TXDR = data;  // データ送信
}

uint8_t rp2040_spi_read(void) {
    while (!(SPI0_SR & (1 << 2))) {}  // 受信データが届くまで待機
    return SPI0_RXDR;  // 受信データを返す
}

#define GPIO_CTRL_BASE      (IO_BANK0_BASE + 0x004)
#define GPIO_OE_BASE        (SIO_BASE + 0x020)
#define GPIO_OUT_BASE       (SIO_BASE + 0x010)
#define GPIO_IN_BASE        (SIO_BASE + 0x004)

void rp2040_gpio_set_function(uint pin, uint func) {
    *(volatile uint32_t *)(GPIO_CTRL_BASE + 8 * pin) = func;
}

void rp2040_gpio_set_dir(uint pin, bool out) {
    if (out) {
        *(volatile uint32_t *)(GPIO_OE_BASE + 0x4) = (1 << pin);
    } else {
        *(volatile uint32_t *)(GPIO_OE_BASE + 0x8) = (1 << pin);
    }
}

void rp2040_gpio_put(uint pin, bool value) {
    if (value) {
        *(volatile uint32_t *)(GPIO_OUT_BASE + 0x4) = (1 << pin);
    } else {
        *(volatile uint32_t *)(GPIO_OUT_BASE + 0x8) = (1 << pin);
    }
}

bool rp2040_gpio_get(uint pin) {
    return (*(volatile uint32_t *)GPIO_IN_BASE) & (1 << pin);
}

// タイマーを使用したマイクロ秒単位の待機関数
#define TIMER_BASE 0x40054000
#define TIMER_TIMELR (*(volatile uint32_t *)(TIMER_BASE + 0x004))

void rp2040_sleep_us(uint32_t us) {
    uint32_t start_time = TIMER_TIMELR;
    while ((TIMER_TIMELR - start_time) < us) {
        // 何もしないで待機
    }
}

#endif // MY_GPIO_SPI_DEFS_H