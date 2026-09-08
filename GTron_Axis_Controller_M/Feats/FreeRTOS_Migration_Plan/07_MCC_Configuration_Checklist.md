# 07 — MCC Harmony V3 Configuration Checklist

This is a UI-level checklist for configuring a fresh MPLAB X project. Work through each section in MCC's Project Graph.

## Project Setup

1. **New MPLAB X Project** → Select Device: `ATSAMC21N18A`
2. **Launch MCC** → Select Harmony V3 framework
3. **MCC Content Manager:** Load SAMC21 DFP (Device Family Pack), CMSIS, Harmony Core

---

## 1. Clock Tree (System → Clock)

| Generator | Source | Target Frequency | Feeds |
|-----------|--------|-----------------|-------|
| GCLK0 | DFLL48M (48 MHz) | **48 MHz** | CPU, CAN1, SERCOM cores, ADC0 |
| GCLK1 | OSC48M / 24 | **2 MHz** | EIC, TC2, TC4, TC0 |
| GCLK2 | OSC48M × (25/24) | **50 MHz** | TC1 (PWM_0) |
| GCLK3 | OSC48M / 120 | **400 kHz** | SERCOM slow clocks |

- DFLL48M: enable, use internal 48 MHz oscillator
- Configure in MCC: **System → Clock Configuration** tab
- Enable all four GCLK generators with above sources and dividers

---

## 2. SERCOM0 — TMC4671 SPI Master

**MCC: Peripherals → SERCOM → Add SERCOM0**

| Setting | Value |
|---------|-------|
| Mode | SPI Master |
| Clock Source | GCLK0 (48 MHz) |
| Baud Rate | 2,000,000 Hz |
| Clock Phase | CPHA = 0 (leading edge sample) |
| Clock Polarity | CPOL = 0 (idle low) |
| Data Order | MSB first |
| Data Size | 8-bit |
| Chip Select | None (manual GPIO on PA07) |
| Pins | MOSI = PA04, SCK = PA05, MISO = PA06 |
| DMA | Not used |

Pin PA07 (`nCS_4671`) configured separately as GPIO output in GPIO section.

---

## 3. SERCOM3 — Flash + IOXP SPI Master

**MCC: Peripherals → SERCOM → Add SERCOM3**

| Setting | Value |
|---------|-------|
| Mode | SPI Master |
| Clock Source | GCLK0 (48 MHz) |
| Baud Rate | 50,000 Hz |
| Clock Phase | CPHA = 0 |
| Clock Polarity | CPOL = 0 |
| Data Order | MSB first |
| Data Size | 8-bit |
| Pins | MOSI = PA25, SCK = PA23, MISO = PA22 |
| DMA | Not used |

Pin PB07 (`FLASH_SPI_nCS`) and PA03 (`IOXP_CS`) configured as GPIO outputs.

---

## 4. SERCOM5 — TMC2209 UART

**MCC: Peripherals → SERCOM → Add SERCOM5**

| Setting | Value |
|---------|-------|
| Mode | USART |
| Baud Rate | 230,400 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Clock Source | GCLK0 (48 MHz) |
| Pins | TX = PB16, RX = PB17 |
| DMA | Not used |

Note: TMC2209 uses single-wire half-duplex. Set TX pin as output, RX pin as input. The `usart_lite` driver in the old project handles half-duplex switching manually — port that logic to the Harmony USART PLIB equivalent.

---

## 5. SERCOM7 — Debug UART (DMA-Driven)

**MCC: Peripherals → SERCOM → Add SERCOM7**

| Setting | Value |
|---------|-------|
| Mode | USART |
| Baud Rate | 2,000,000 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Clock Source | GCLK0 (48 MHz) |
| Pins | TX = PC12, RX = PC15 |
| DMA | TX DMA enabled (Channel 0, trigger = SERCOM7 TX empty) |

---

## 6. Timers

### TC0 — Free-Running Microsecond Counter (1 MHz, 32-bit)

| Setting | Value |
|---------|-------|
| Mode | 32-bit Timer |
| Clock Source | GCLK1 (2 MHz) |
| Prescaler | /2 |
| Tick Rate | 1 MHz |
| Interrupt | **Disabled** (free-running, read-only) |

### TC1 — TMC4671 25 MHz Clock (PWM)

| Setting | Value |
|---------|-------|
| Mode | 32-bit PWM |
| Clock Source | GCLK2 (50 MHz) |
| Prescaler | /1 |
| Period | 2 (50 MHz / 2 = 25 MHz, 50% duty cycle) |
| Output | PA10 (WO0) |
| Interrupt | **Disabled** |

### TC2 — Step Tracking Tick (1ms)

| Setting | Value |
|---------|-------|
| Mode | 32-bit Timer |
| Clock Source | GCLK1 (2 MHz) |
| Prescaler | /2 |
| Tick Rate | 1 ms (2 MHz / 2 / 1000 = 1000 cycles) |
| Compare Value | 999 |
| Interrupt | **Enabled** → overflow/match → TC2_Handler |
| NVIC Priority | 2 |

### TC4 — Ramp Tick (1ms)

| Setting | Value |
|---------|-------|
| Mode | 32-bit Timer |
| Clock Source | GCLK1 (2 MHz) |
| Prescaler | /2 |
| Tick Rate | 1 ms |
| Compare Value | 999 |
| Interrupt | **Enabled** → overflow/match → TC4_Handler |
| NVIC Priority | 2 |

---

## 7. CAN1

**MCC: Peripherals → CAN → Add CAN1**

| Setting | Value |
|---------|-------|
| Clock Source | GCLK0 (48 MHz) |
| Bit Rate | 500,000 bps |
| Propagation Segment | 1 |
| Phase Segment 1 | 11 |
| Phase Segment 2 | 8 |
| Sync Jump Width | 4 |
| BRP | 3 |
| Receive FIFO 0 | Enabled, 2 elements |
| Transmit FIFO | Enabled, 2 elements |
| Standard ID Filter | 2 elements (reject all by default) |
| Extended ID Filter | 2 elements (reject all by default) |
| Interrupt | **Enabled** → RX FIFO 0 new message |
| NVIC Priority | 2 |

Filter configuration (runtime, not MCC):
- Extended ID filter: configure to accept relevant CAN IDs based on `axis_id`
- Set filter at init after axis_id is read from ADC

---

## 8. EIC (External Interrupt Controller)

**MCC: Peripherals → EIC → Add EIC**

Configure these pins as external interrupts:

| Pin | Label | Sense Edge | Async | Debounce | NVIC Prio |
|-----|-------|-----------|-------|----------|-----------|
| PB21 | IOXP_INT | Rising | Yes | Yes | 2 |
| PC18 | LIM_RT | Rising | No | Yes | 2 |
| PC20 | LIM_LFT | Rising | No | Yes | 2 |
| PC21 | DIAG | Rising | Yes | Yes | 2 |

- All EIC interrupts use the shared `EIC_Handler` (EIC IRQ 3)
- Callbacks registered at runtime via `EIC_CallbackRegister()`
- NVIC Priority: set to 2 for all EIC pins

**DO NOT configure these EXTINTs from the old project:**
- PA17 (EXTINT1), PA18 (EXTINT2), PA19 (EXTINT3), PB23 (EXTINT7), PC16 (EXTINT8), PC17 (EXTINT9)

---

## 9. ADC0

**MCC: Peripherals → ADC → Add ADC0**

| Setting | Value |
|---------|-------|
| Clock Source | GCLK0 (48 MHz) |
| Resolution | 12-bit |
| Reference | VDDANA (3.3V) |
| Channel 9 | Enabled (PC01, axis ID voltage divider) |
| Interrupt | Disabled |
| NVIC Priority | N/A |

---

## 10. DMAC (DMA Controller)

**MCC: Peripherals → DMAC → Add DMAC**

| Setting | Value |
|---------|-------|
| Channel 0 | Enabled |
| Trigger Source | SERCOM7 TX empty |
| Trigger Action | Beat |
| Beat Size | Byte |
| Source Increment | Enabled |
| Destination Increment | Disabled (fixed SERCOM7 DATA register) |
| Priority | 0 (lowest) |
| Interrupt | Transfer Complete → DMAC_Handler |
| NVIC Priority | 2 |

---

## 11. GPIO Pins

Configure all unused pins as GPIO. Key output pins default high (inactive for CS/enable lines):

| Pin | Direction | Initial | Purpose |
|-----|-----------|---------|---------|
| PA03 | Output | High | IOXP_CS (MCP23S08 chip select) |
| PA07 | Output | High | nCS_4671 (TMC4671 chip select) |
| PA09 | Output | Low | DBGLED1 |
| PA10 | Peripheral (TC1 WO0) | — | TMC4671 25 MHz clock |
| PA14 | Output | Low | DBGLED3 |
| PA15 | Output | Low | DBGLED2 |
| PB07 | Output | High | FLASH_SPI_nCS |
| PB08 | Output | Low | EN_4671 (TMC4671 enable) |
| PB09 | Output | High | RST_4671 (active low reset) |
| PB10 | Output | Low | SWITCH_EN |
| PB30 | Output | Low | REELER_INT (camera trigger) |

**Do NOT configure** (dead code from old project):
- PA17 (LINENC_DIR), PA18 (LINENC_Z), PA19 (ROTENC_COUNT)
- PB11 (FPGA_CDONE), PB12 (FPGA_CRESET_B)
- PB23 (INDEX)
- PC16 (ROTENC_DIR), PC17 (ROTENC_Z)
- PA00/PA01 (UART_0 — SERCOM1 is dead)

---

## 12. FreeRTOS Component

**MCC: Third-Party → FreeRTOS → Add FreeRTOS**

| Tab | Setting | Value |
|-----|---------|-------|
| General | Max Priorities | 5 |
| General | Minimal Stack Size | 128 words |
| General | Tick Rate | 1000 Hz |
| General | Use Preemption | Enabled |
| General | Use Time Slicing | Enabled |
| General | Use Task Notifications | Enabled |
| General | Use Mutexes | Enabled |
| General | Use Counting Semaphores | Enabled |
| General | Use Recursive Mutexes | Disabled |
| General | Use Queue Sets | Disabled |
| General | Use Tickless Idle | Disabled |
| Memory | Total Heap Size | 0 (static allocation only) |
| Memory | Support Static Allocation | Enabled |
| Memory | Support Dynamic Allocation | Disabled |
| Hooks | Use Idle Hook | Disabled |
| Hooks | Use Tick Hook | Disabled |
| Hooks | Use Malloc Failed Hook | Disabled |
| Hooks | Check for Stack Overflow | Method 2 |
| Runtime | Generate Runtime Stats | Disabled |
| Runtime | Use Stats Formatting | Disabled |
| Runtime | Use Trace Facility | Disabled |

MCC auto-generates `FreeRTOSConfig.h` with correct SAMC21 port settings (SysTick, PendSV, SVC integration, NVIC priority values). Verify the generated file matches:

```c
#define configCPU_CLOCK_HZ                      48000000UL
#define configTICK_RATE_HZ                      1000
#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                128
#define configTOTAL_HEAP_SIZE                   0
#define configUSE_PREEMPTION                    1
#define configUSE_TIME_SLICING                  1
#define configUSE_TASK_NOTIFICATIONS            1
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             0
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_STATS_FORMATTING_FUNCTIONS    0
#define configCHECK_FOR_STACK_OVERFLOW          2
#define configSUPPORT_STATIC_ALLOCATION         1
#define configSUPPORT_DYNAMIC_ALLOCATION        0
```

---

## 13. Generate Code

1. Click **Generate** in MCC
2. MCC writes: `config/`, `peripheral/`, `FreeRTOS/`, `FreeRTOSConfig.h`, `initialization.c`, `system_init.c`, startup files
3. Build the empty project → verify it compiles with zero errors

---

## Post-MCC Manual Configuration

These need to be done in source code (not MCC UI):

### WDT Initialization
```c
// In app_init.c, after MCC-generated SYS_Initialize():
WDT_Initialize();  // Harmony PLIB; timeout configured via WDT CONFIG register
```

### CAN Filter Configuration
```c
// After axis_id is determined from ADC:
can_configure_filter_for_axis(g_axis_id);
```

### EIC Callback Registration
```c
EIC_CallbackRegister(EIC_PIN_5,  ioxp_Interrupt_Callback,  0);
EIC_CallbackRegister(EIC_PIN_10, right_Limit_Interrupt_Callback, 0);
EIC_CallbackRegister(EIC_PIN_12, left_Limit_Interrupt_Callback,  0);
EIC_CallbackRegister(EIC_PIN_13, diag_Interrupt_Callback,  0);
```

### Timer Start
```c
// Start TC4 (ramp tick) and TC2 (step tick) AFTER tasks are created:
TC2_TimerStart();  // Harmony PLIB
TC4_TimerStart();
```

### NVIC Priority for All App ISRs
MCC might set varying priorities. Verify all application ISRs are at priority 2. Set manually in `system_interrupt.c` if needed.

---

## Expected Generated File Tree

```
src/
├── config/
│   ├── peripheral_clk_config.h    (clock tree)
│   ├── sercom0_spi_master.h        (TMC4671)
│   ├── sercom3_spi_master.h        (flash + IOXP)
│   ├── sercom5_usart.h             (TMC2209)
│   ├── sercom7_usart.h             (debug)
│   ├── tc0_timer.h
│   ├── tc1_pwm.h
│   ├── tc2_timer.h
│   ├── tc4_timer.h
│   ├── can1.h
│   ├── eic.h
│   ├── adc0.h
│   ├── dmac.h
│   └── FreeRTOSConfig.h
├── peripheral/                     (PLIB driver files)
├── FreeRTOS/                       (kernel files)
├── initialization.c                (SYS_Initialize)
└── system_init.c
```
