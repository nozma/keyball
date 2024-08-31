#define SIO_BASE            0xD0000000
#define SPI0_BASE           0x4003C000
#define IO_BANK0_BASE       0x40014000

// SPI0の基本設定
#define SPI0_CTRLR0         (*(volatile uint32_t *)(SPI0_BASE + 0x000))
#define SPI0_SSIENR         (*(volatile uint32_t *)(SPI0_BASE + 0x008))
#define SPI0_BAUDR          (*(volatile uint32_t *)(SPI0_BASE + 0x014))
#define SPI0_TXDR           (*(volatile uint32_t *)(SPI0_BASE + 0x018))
#define SPI0_RXDR           (*(volatile uint32_t *)(SPI0_BASE + 0x01C))
#define SPI0_SR             (*(volatile uint32_t *)(SPI0_BASE + 0x028))

void spi_init() {
    // SPIの設定 (8ビットモード、ポーリング方式)
    SPI0_CTRLR0 = (0x7 << 0);  // 8ビットデータ
    SPI0_BAUDR = 0x2;          // クロック分周器設定
    SPI0_SSIENR = 0x1;         // SPI有効化
}

void spi_write(uint8_t data) {
    while (!(SPI0_SR & (1 << 1))) {}  // 送信FIFOが空になるまで待機
    SPI0_TXDR = data;  // データ送信
}

uint8_t spi_read() {
    while (!(SPI0_SR & (1 << 2))) {}  // 受信データが届くまで待機
    return SPI0_RXDR;  // 受信データを返す
}

#define GPIO_CTRL_BASE      (IO_BANK0_BASE + 0x004)
#define GPIO_OE_BASE        (SIO_BASE + 0x020)
#define GPIO_OUT_BASE       (SIO_BASE + 0x010)
#define GPIO_IN_BASE        (SIO_BASE + 0x004)

void gpio_set_function(uint pin, uint func) {
    *(volatile uint32_t *)(GPIO_CTRL_BASE + 8 * pin) = func;
}

void gpio_set_dir(uint pin, bool out) {
    if (out) {
        *(volatile uint32_t *)(GPIO_OE_BASE + 0x4) = (1 << pin);
    } else {
        *(volatile uint32_t *)(GPIO_OE_BASE + 0x8) = (1 << pin);
    }
}

void gpio_put(uint pin, bool value) {
    if (value) {
        *(volatile uint32_t *)(GPIO_OUT_BASE + 0x4) = (1 << pin);
    } else {
        *(volatile uint32_t *)(GPIO_OUT_BASE + 0x8) = (1 << pin);
    }
}

bool gpio_get(uint pin) {
    return (*(volatile uint32_t *)GPIO_IN_BASE) & (1 << pin);
}