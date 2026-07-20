#include "led_driver.h"
#include "definitions.h"
#include <string.h> // For memset

// Pin Definition: PB20
#define LED_PIN_MASK (1U << 20)

// Internal Buffer
static LED_Color led_strip[LED_STRIP_LENGTH];

// Unrolled NOP macros for 48MHz (20.8ns/cycle)
#define DELAY_SHORT \
    __asm__ volatile("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;"); // 12 x 20.8ns = 249.6ns.

#define DELAY_LONG \
    __asm__ volatile("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;" \     
                     "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;" \
                     "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;" \
                     "nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;");          // 10 x 3 x 20.8ns = 832ns

static void delay_cycles(uint32_t count)
{
    while (count--) {
        __asm__ volatile ("nop");
    }
    return;
}

void LED_Driver_Init(void)
{
    PORT_REGS->GROUP[1].PORT_DIRSET = LED_PIN_MASK;
    PORT_REGS->GROUP[1].PORT_OUTCLR = LED_PIN_MASK;
    LED_Clear();
    delay_cycles(15000);
    return;
}

void LED_SetPixel(uint32_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index < LED_STRIP_LENGTH) {
        for (uint32_t i = 0; i <= index; i++) {
            led_strip[i].r = r;
            led_strip[i].g = g;
            led_strip[i].b = b;
        }
    }
    return;
}

void LED_Clear(void)
{
    memset(led_strip, 0, sizeof(led_strip));
    return;
}

static void send_byte(uint8_t byte)
{
    for (int i = 7; i >= 0; i--) {
        if (byte & (1 << i)) {
            PORT_REGS->GROUP[1].PORT_OUTSET = LED_PIN_MASK;
            DELAY_LONG;
            PORT_REGS->GROUP[1].PORT_OUTCLR = LED_PIN_MASK;
            DELAY_SHORT;
        } else {
            PORT_REGS->GROUP[1].PORT_OUTSET = LED_PIN_MASK;
            DELAY_SHORT;
            PORT_REGS->GROUP[1].PORT_OUTCLR = LED_PIN_MASK;
            DELAY_LONG;
        }
    }
    return;
}

void LED_Show(void)
{
    // Reset Signal
    delay_cycles(15000); 

    // Safe Critical Section: Save interrupt state before disabling
    uint32_t primask_save = __get_PRIMASK();
    __disable_irq();
    for (uint32_t i = 0; i < LED_STRIP_LENGTH; i++) {
        // Send BRG (Blue-Red-Green)
        send_byte(led_strip[i].b);
        send_byte(led_strip[i].r);
        send_byte(led_strip[i].g);
    }
    // Restore interrupt state (re-enables interrupts only if they were enabled before)
    __set_PRIMASK(primask_save);

}

// ==========================================
// SPI Based Driver Implementation
// ==========================================

#include "peripheral/sercom/spi_master/plib_sercom3_spi_master.h"

// Lookup table for 4-bit SPI encoding (2 LED bits per SPI byte)
// Logic '0': 1000 (0x8) -> 333ns High, 1000ns Low
// Logic '1': 1110 (0xE) -> 1000ns High, 333ns Low
// Index = 2 bits of color data (00, 01, 10, 11)
static const uint8_t spi_lookup[4] = {
    0x88, // 00 -> 1000 1000
    0x8E, // 01 -> 1000 1110
    0xE8, // 10 -> 1110 1000
    0xEE  // 11 -> 1110 1110
};

void LED_Driver_SPI_Init(void)
{
    SERCOM3_SPI_Initialize();
    LED_Clear();
}

void LED_Show_SPI(void)
{
    // Single buffer for Reset + Data
    // Original Bit-Bang used ~300us reset.
    // 1 Byte @ 3MHz = 2.67us. 
    // 150 Bytes = ~400us, which guarantees a latch.
    #define SPI_RESET_BYTES 150
    static uint8_t spi_buffer[SPI_RESET_BYTES + (LED_STRIP_LENGTH * 3 * 4)];
    
    uint32_t buf_idx = 0;

    // 1. Fill Reset Signal (Zeros)
    memset(spi_buffer, 0, SPI_RESET_BYTES);
    buf_idx += SPI_RESET_BYTES;

    // 2. Encode Frame Data
    for (uint32_t i = 0; i < LED_STRIP_LENGTH; i++) {
        // Send BRG (Blue-Red-Green)
        uint8_t colors[3] = {led_strip[i].b, led_strip[i].r, led_strip[i].g};

        for (int c = 0; c < 3; c++) {
            uint8_t val = colors[c];
            
            // Encode 8 bits into 4 SPI bytes
            // LED Bits 7,6
            spi_buffer[buf_idx++] = spi_lookup[(val >> 6) & 0x03];
            // LED Bits 5,4
            spi_buffer[buf_idx++] = spi_lookup[(val >> 4) & 0x03];
            // LED Bits 3,2
            spi_buffer[buf_idx++] = spi_lookup[(val >> 2) & 0x03];
            // LED Bits 1,0
            spi_buffer[buf_idx++] = spi_lookup[(val >> 0) & 0x03];
        }
    }

    // 3. Send Everything in one go
    SERCOM3_SPI_Write(spi_buffer, buf_idx);
    
    // Wait for completion
    while(SERCOM3_SPI_IsTransmitterBusy()); 
}

// ==========================================
// DMA Based Driver Implementation
// ==========================================

#include "peripheral/dmac/plib_dmac.h"

// Shared buffer for DMA transfers. Must be static/global to persist during transfer.
// Size: Reset (200) + Data (LED_STRIP_LENGTH * 3 * 4)
#define RESET_BYTES 200
static uint8_t dma_spi_buffer[RESET_BYTES + (LED_STRIP_LENGTH * 3 * 4)];

void LED_Show_DMA(void)
{
    // Ensure sufficient reset time between frames (approx 300us)
    delay_cycles(15000);
    
    // 0. Ensure previous transfer is done before modifying buffer
    while (DMAC_ChannelIsBusy(DMAC_CHANNEL_0));

    uint32_t buf_idx = 0;

    // 1. Fill Reset Signal (Zeros)
    memset(dma_spi_buffer, 0, RESET_BYTES);
    buf_idx += RESET_BYTES;

    // 2. Insert Dummy Black LED (sacrificial) to fix first-LED-eating glitch
    // REMOVED: This causes the first LED to display black on valid hardware.
    //for (int d = 0; d < 12; d++) {
    //    dma_spi_buffer[buf_idx++] = 0x88;
    //}

    // 3. Encode Frame Data
    for (uint32_t i = 0; i < LED_STRIP_LENGTH; i++) {
        // Send BRG (Blue-Red-Green)
        uint8_t colors[3] = {led_strip[i].b, led_strip[i].r, led_strip[i].g};

        for (int c = 0; c < 3; c++) {
            uint8_t val = colors[c];
            
            // Encode 8 bits into 4 SPI bytes
            dma_spi_buffer[buf_idx++] = spi_lookup[(val >> 6) & 0x03];
            dma_spi_buffer[buf_idx++] = spi_lookup[(val >> 4) & 0x03];
            dma_spi_buffer[buf_idx++] = spi_lookup[(val >> 2) & 0x03];
            dma_spi_buffer[buf_idx++] = spi_lookup[(val >> 0) & 0x03];
        }
    }

    // 4. Start DMA Transfer
    // Source: RAM buffer
    // Dest:   SERCOM3 Data Register
    DMAC_ChannelTransfer(DMAC_CHANNEL_0, 
                         dma_spi_buffer, 
                         (const void *)&SERCOM3_REGS->SPIM.SERCOM_DATA, 
                         buf_idx);
}