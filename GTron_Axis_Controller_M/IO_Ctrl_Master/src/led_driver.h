#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

// Configuration: Change this to match your strip length
#define LED_STRIP_LENGTH 30

// Structures
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} LED_Color;

/**
 * @brief Initializes the LED driver and PB20 pin.
 */
void LED_Driver_Init(void);

/**
 * @brief Sets the color of pixels from 0 to the specific index in the internal buffer.
 * Does NOT send data to the strip immediately (call LED_Show for that).
 * 
 * @param index End pixel index (0 to LED_STRIP_LENGTH-1)
 * @param r Red value (0-255)
 * @param g Green value (0-255)
 * @param b Blue value (0-255)
 */
void LED_SetPixel(uint32_t index, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Clears the internal buffer (sets all pixels to 0).
 */
void LED_Clear(void);

/**
 * @brief Sends the internal buffer to the LED strip.
 */
void LED_Show(void);

/**
 * @brief Initializes the LED driver using SERCOM3 SPI.
 * Configures the SPI peripheral using the PLIB.
 */
void LED_Driver_SPI_Init(void);

/**
 * @brief Sends the internal buffer to the LED strip using SPI.
 * Uses 4-bit SPI encoding to emulate the WS2812/SM16703 protocol.
 */
void LED_Show_SPI(void);

/**
 * @brief Sends the internal buffer to the LED strip using SPI via DMA.
 * This is non-blocking (kicks off the transfer and returns).
 * Requires DMAC Channel 0 to be configured for SERCOM3_TX.
 */
void LED_Show_DMA(void);

#endif // LED_DRIVER_H
