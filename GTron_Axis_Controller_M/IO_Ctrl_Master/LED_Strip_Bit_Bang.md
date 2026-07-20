# SM16703/WS2812 LED Bit-Banging Driver Guide

This document explains the technical implementation and operational flow of the high-precision LED driver developed for the SAMC21N18A to control the GZX16703 LED strip via PB20.

## 1. Core Architecture: The Framebuffer
The driver operates on a **Framebuffer** (internal memory) model. This separates the logic of "what color should the LED be" from the complex timing of "how do I send that data."

*   **Internal Array:** Inside `led_driver.c`, a static array `led_strip[LED_STRIP_LENGTH]` holds the current state of every LED in RAM.
*   **Decoupled Updates:** When you call `LED_SetPixel()`, you are only updating memory. This is nearly instantaneous and allows for complex animations without worrying about the communication protocol.
*   **Atomic Updates:** `LED_Show()` is the "commit" function. It takes the entire snapshot of memory and blasts it out to the physical hardware in one continuous stream.

---

## 2. Operational Flow

### Phase A: Initialization (`LED_Driver_Init`)
This prepares the physical hardware for communication.
1.  **GPIO Setup:** Configures **PB20** as a Digital Output.
2.  **Line Latching:** Forces the pin to **Logic LOW (0V)**.
3.  **Bootstrap Reset:** Waits for ~300μs to ensure the LED strip controllers are reset and ready for the very first frame.

### Phase B: State Management (`LED_SetPixel` & `LED_Clear`)
1.  **`LED_Clear()`**: Uses `memset` to efficiently wipe the internal RAM buffer to zero (all LEDs OFF).
2.  **`LED_SetPixel()`**: Performs boundary checking and writes the RGB values to the specific array index.

### Phase C: The Transmission Engine (`LED_Show`)
This is the most critical part of the driver. The SM16703 protocol requires nanosecond precision.

1.  **The Latch (Reset):** The pin is held LOW for ~300μs. The LED strip sees this as a "frame end" and latches the previously received data into the PWM drivers of the LEDs.
2.  **Interrupt Silencing (`__disable_irq`):** The CPU stops processing all background tasks (SysTick, Timers, etc.). This ensures that no hardware interrupt can delay a single bit, which would cause flickering.
3.  **Color Serialization:** The driver loops through the buffer. For your specific strip, it sends data in **BRG (Blue-Red-Green)** order.
4.  **Completion:** Once the last bit is sent, interrupts are re-enabled.

---

## 3. The Bit-Banging Protocol (`send_byte`)

Since PB20 does not support hardware PWM, we use **Bit-Banging**. This involves manually toggling the pin and using CPU cycles to create the specific pulse widths the SM16703 requires.

### Timing for 48 MHz CPU (1 cycle = 20.8ns)
The driver uses **Unrolled NOPs** (No-Operation assembly instructions) to create exact delays.

#### Logic '0' (Short High, Long Low)
1.  **Pin HIGH**
2.  **Wait ~300ns** (14 CPU cycles: Write overhead + 12 NOPs)
3.  **Pin LOW**
4.  **Wait ~900ns** (43 CPU cycles: Write overhead + 40 NOPs)

#### Logic '1' (Long High, Short Low)
1.  **Pin HIGH**
2.  **Wait ~900ns** (43 CPU cycles)
3.  **Pin LOW**
4.  **Wait ~300ns** (14 CPU cycles)

### Code Precision
Using `__asm__ volatile("nop")` ensures the compiler does not optimize away our delays. By "unrolling" them (putting them in a sequence instead of a loop), we eliminate the cycles wasted on loop comparisons and branches, making the signal perfect and jitter-free.

---

## 4. Usage Summary

To use this driver in a production codebase:

```c
// 1. One-time setup
LED_Driver_Init();

// 2. Clear previous frame
LED_Clear();

// 3. Set your pattern
LED_SetPixel(0, 255, 0, 0); // Red
LED_SetPixel(1, 0, 255, 0); // Green

// 4. Push to hardware
LED_Show();
```

## 5. Hardware Constraints Note
This driver operates at **3.3V Logic**. Because the LED strip operates at **5V**, the signal is near the threshold voltage for the strip. We have optimized the pulse widths to be as robust as possible for this specific configuration.
