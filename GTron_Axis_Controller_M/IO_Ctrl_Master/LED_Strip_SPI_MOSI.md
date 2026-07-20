# SM16703/WS2812 LED Driver Guide (SPI MOSI Method)

This document details the implementation of a high-precision, jitter-free LED driver for the **SAMC21N18A** using the **SERCOM SPI** peripheral and **DMAC**. This method replaces CPU-intensive bit-banging with hardware-accelerated signal generation, ensuring perfect timing stability even in complex RTOS-based environments.

---

## 1. Core Concept: Why SPI?

The SM16703/WS2812 protocol requires a specific pulse-width encoded signal:
*   **Logic 0:** Short High (~333ns), Long Low (~1000ns)
*   **Logic 1:** Long High (~1000ns), Short Low (~333ns)
*   **Frequency:** ~750-800 kHz

Instead of toggling a GPIO manually, we use the **SPI MOSI (Master Out Slave In)** line to generate this waveform. By running the SPI clock at **3.0 MHz**, one SPI bit takes **333ns**. We can therefore construct 1 LED bit using **4 SPI bits**:

| LED Bit | SPI Pattern (4 bits) | Duration (High / Low) | Timing (approx) |
| :--- | :--- | :--- | :--- |
| **0** | `1000` (0x8) | 1 High / 3 Low | 333ns / 1000ns |
| **1** | `1110` (0xE) | 3 High / 1 Low | 1000ns / 333ns |

---

## 2. Hardware Configuration

### Pin Mapping
*   **MCU:** ATSAMC21N18A
*   **MOSI Pin:** **PB20** (EXT2 Header Pin 14) -> Connected to LED Data In
*   **SCK Pin:** **PB21** (EXT2 Header Pin 13) -> Configured but left unconnected.

### SERCOM3 Settings
*   **Mode:** SPI Master
*   **Clock Source:** GCLK0 (48 MHz)
*   **Baud Rate:** 3.0 MHz (Baud Register = 7)
*   **Data Order:** MSB First

### DMAC Settings (For Background Transfer)
*   **Channel:** 0
*   **Trigger Source:** `SERCOM3_Transmit`
*   **Trigger Action:** One Beat Transfer per DMA Request
*   **Source Address Mode:** Increment
*   **Destination Address Mode:** Fixed (Points to `SERCOM3_REGS->SPIM.SERCOM_DATA`)
*   **Beat Size:** 8-bit

---

## 3. Driver Architecture

### A. Initialization (`LED_Driver_SPI_Init`)
Configures the SERCOM3 peripheral for SPI Master mode at 3MHz. The DMAC is typically initialized via `SYS_Initialize()`.

### B. Framebuffer Encoding
The driver maintains a color buffer `led_strip[LED_STRIP_LENGTH]`. Every 2 bits of LED data are mapped to 1 byte of SPI data using a lookup table:
```c
static const uint8_t spi_lookup[4] = {0x88, 0x8E, 0xE8, 0xEE};
```

### C. Transmission Methods

#### Method 1: Polling (`LED_Show_SPI`)
A blocking function that loops through the data and waits for the hardware to be ready for each byte.
*   **Pros:** Simple, no DMA setup required.
*   **Cons:** Blocks CPU during transmission (~1.25µs per LED bit). Risk of frame-splitting in RTOS if preempted.

#### Method 2: DMA (`LED_Show_DMA`)
A non-blocking function that kicks off a hardware transfer.
*   **Pros:** 0% CPU usage during transmission. Immune to RTOS context switches (no frame splitting).
*   **Cons:** Requires DMAC configuration.

---

## 4. Usage in RTOS / Production

When using FreeRTOS, the **DMA method** is strongly recommended. It ensures that the precise SPI stream is never interrupted by higher-priority tasks, which would otherwise cause flickering or reset the LED strip prematurely.

```c
#include "led_driver.h"

void LED_Task(void *pvParameters) {
    LED_Driver_SPI_Init();

    while(1) {
        LED_Clear();
        LED_SetPixel(0, 50, 50, 0); // Set colors
        
        // Background update - returns immediately
        LED_Show_DMA();
        
        // Wait for next frame (e.g. 30 FPS)
        vTaskDelay(pdMS_TO_TICKS(33));
    }
}
```

---

## 5. Troubleshooting
*   **First LED Issues:** Ensure the Reset preamble is long enough. The driver uses **150 bytes (~400µs)** of zeros to guarantee a latch.
*   **Buffer Persistence:** When using `LED_Show_DMA`, the `spi_buffer` must be `static` or `global` because the DMA controller will continue reading from it after the function returns.