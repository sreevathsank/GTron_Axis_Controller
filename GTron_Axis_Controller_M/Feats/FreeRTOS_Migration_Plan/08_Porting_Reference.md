# 08 — Porting Reference: What to Bring From Old Project

## Principle

- **MCC-generated code** (peripherals, init, startup, FreeRTOSConfig) → use the new project's generated files
- **Application code** (motor drivers, CAN protocol, ramp math, hybrid trigger, flash/IOXP) → copy from old project, adapt low-level API calls
- **Dead code** → discard

## Must Port (Copy → Adapt → Integrate)

### Motor Drivers

| Old Path | New Path | Notes |
|----------|----------|-------|
| `TMC-API/tmc/ic/TMC4671/*` | `src/app/drivers/tmc4671/` | Entire TMC4671 driver directory. Register map, field defs, readInt/writeInt. Adapt `SPI_0_transfer_block()` call to Harmony PLIB equivalent. CS pin toggling via GPIO_PinWrite. |
| `TMC-API/tmc/helpers/*` | `src/app/drivers/tmc4671/helpers/` | Bits.h, CRC.c, RegisterAccess.h, Types.h etc. |
| `TMC-API/tmc/ramp/*` | `src/app/drivers/tmc4671/ramp/` | LinearRamp.c/h — ramp generator library |
| `tmc2209_uart/TMC2209.c/h` | `src/app/drivers/tmc2209/` | TMC2209 UART register r/w + CRC8. Adapt to Harmony USART PLIB. Keep CRC8 table and swizzle logic (identical). |
| `tmc2209_uart/TMC2209_HW_Abstraction.h` | `src/app/drivers/tmc2209/` | TMC2209 register addresses and field defs |
| `tmc2209_uart/Step_Counter.c/h` | `src/app/motor_2209/` | MSCNT polling + step tracking |

### CAN Protocol (From Old GTron Project)

| Old Path | New Path | Notes |
|----------|----------|-------|
| `Bring_Up/CAN/IMM_CAN_Message_Id.h` | `src/app/can/can_protocol.h` | CAN ID macros, enums, union type. **KEEP AS-IS** — these define the protocol. |
| `Bring_Up/CAN/TMCL_IDE_reply.c/h` | `src/app/can/tmcl_reply.c/h` | TMCL protocol reply formatting (optional, if used) |
| `Bring_Up/CAN/MCD_v3.c/h` | `src/app/can/mcd_v3.c/h` | Motion Control Dictionary v3 (optional, if used) |
| `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.c/h` | `src/app/can/can_cmd_parser.c/h` | CAN command parser + Motor_Info_t struct + motor pointer declarations. **Core file.** |

### CAN FreeRTOS Gatekeeper (From IO_Ctrl_Master Project)

The CAN gatekeeper task, ISR callbacks, and low-level CAN read/write functions are
**ported from the IO_Ctrl_Master FreeRTOS project** with bug fixes applied.

| IO_Ctrl_Master Source | New Path | What to Copy |
|------------------------|----------|-------------|
| `src/can.c` | `src/app/can/can_gatekeeper.c` | **Selectively.** Copy `CAN1_Read()` (lines 312-380), `CAN1_Write()` (lines 288-310), `get_can_id_from_buffer()` (lines 102-112), `get_can_dlc_from_buffer()` (lines 119-135), `get_can_data_from_buffer()` (lines 142-151), `CANLengthToDlcGet()`, `CANDlcToLengthGet()`. Do NOT copy the old `CAN_Tasks()` — it has the two-hop dispatch + bugs. Write `vCAN_Gatekeeper_Task()` fresh using the pattern from doc 02/03. |
| `IOCtrl1.X/interrupt_callbacks.c` | `src/app/can/can_isr_callbacks.c` | Copy `CAN1_RxFifo0Callback()`, `CAN1_RxFifo1Callback()`, `CAN1_TxFifoCallback()`. Apply bugfixes: `woken = pdFALSE` (not pdTRUE), use local `can_frame_t` (not shared global). |
| `IOCtrl1.X/interrupt_callbacks.h` | `src/app/can/can_isr_callbacks.h` | Function declarations for the three CAN callbacks + `CAN1_TxFifoCallback`. |
| `IOCtrl1.X/global_vars.h` | `src/app/can/can_state.h` (merge) | Copy `Can_Queue_t` struct as reference, `CAN_Cmd_Parser_t`, `CAN_Rx_Fifo_CB_Info`, `CAN_STATE` enum, `CAN_STATES` enum. The `Can_Queue_t` maps to `can_frame_t` — use `can_frame_t` in GTron, keep `CAN_Cmd_Parser_t` for CAN1_Read() output. |
| `IOCtrl1.X/global_vars.c` | `src/app/can/can_state.c` | Instance definitions: `can_cmd_parse_info`, `can1_rx_fifo0_cb_info`, `can1_rx_fifo1_cb_info`, `Can1MessageRAM[]`. |
| `IOCtrl1.X/init_funcs.c` (lines 54-58) | `main.c` init sequence | Copy `CAN1_MessageRAMConfigSet()` + `CAN1_TxFifoCallbackRegister()` + `CAN1_RxFifoCallbackRegister()` calls. Substitute `xQueueCreate` with `xQueueCreateStatic`. |

**Do NOT port:**
- `xcmd_parser_queue` and the parser task (two-hop eliminated)
- `canData` state machine (replaced by blocking queue receive)
- `xbtn_state_event_grp` + button ISR callbacks (not used in GTron)
- `all_headers.h`
- `xQueueCreate` calls (use static allocation instead)
- `SYS_DEBUG_PRINT` / `SYS_DEBUG_MESSAGE` (use DBG_Printf instead)

### Motion Control (TMC4671)

| Old Path | New Path | Notes |
|----------|----------|-------|
| `Bring_Up/Motion/Motion.c/h` | `src/app/motor_4671/motion.c/h` | Ramp generation (S-curve + trapezoidal), velocity knob, homing sequence. Keep math identical. |
| `Bring_Up/Motion/Hybrid_Trigger.c/h` | `src/app/motor_4671/hybrid_trigger.c/h` | Hybrid trigger modes (inspection, n-shot, encoder mode). Keep logic identical. Adapt `can_AxC_Write()` calls to `xQueueSend(g_q_can_work, ...)`. |
| `Bring_Up/DBG_bring_up.c/h` | `src/app/motor_4671/motor_4671_init.c/h` | TMC4671 init sequence (reset_Basics, init_Basics, init_PosMode, ADC cal, open-loop alignment). Keep identical. |

### IO Expander

| Old Path | New Path | Notes |
|----------|----------|-------|
| `Bring_Up/IO_Expander/spi_io_expander.c/h` | `src/app/drivers/io_expander/` | MCP23S08 driver. The old code uses direct `hri_sercomspi_write_DATA_reg(SERCOM3, w)` — adapt to Harmony SERCOM3 SPI PLIB equivalents. CS toggling via GPIO_PinWrite. |

### External Flash + TLV

| Old Path | New Path | Notes |
|----------|----------|-------|
| `Code_Dump/ext_flash.c/h` | `src/app/drivers/ext_flash/` | Adesto SPI NOR flash driver. Adapt SPI register writes to Harmony PLIB. |
| `Code_Dump/tlv_flash.c/h` | `src/app/supervisor/tlv_flash.c/h` | TLV parameter storage. Depends on ext_flash.c. Keep logic identical. |

### Debug Transport

| Old Path | New Path | Notes |
|----------|----------|-------|
| `Bring_Up/Debug/dbg_transport.c/h` | `src/app/debug/` | DMA-driven UART TX. Keep DMA register config logic. Adapt to Harmony DMAC PLIB register names. |
| `Bring_Up/Debug/dbg_print.c/h` | `src/app/debug/` | DBG_Printf wrapper. Replace bare-metal spin-wait with FreeRTOS queue dispatch (see doc 06). |
| `Bring_Up/Debug/dbg_print_config.h` | `src/app/debug/` | Debug severity levels. Keep identical. |

### SysTick

| Old Path | New Path | Notes |
|----------|----------|-------|
| `SysTick/Systick.c/h` | **DISCARD** | FreeRTOS takes SysTick. Use `xTaskGetTickCount()` for millisecond timing and TC0 for microsecond timing. Remove the old `millis()`/`micros()` functions. |

### Global Definitions

| Old Path | New Path | Notes |
|----------|----------|-------|
| `Macros.h` | `src/app/app_config.h` | Project-wide macros. Keep useful ones; discard unused ones. |
| `Global_Vars.c/h` | **SPLIT** into per-module headers (see doc 10). Do NOT port as-is. |

---

## Must NOT Port (MCC Replaces These)

| Old Path | Disposition |
|----------|-------------|
| `config/*` (peripheral_clk_config.h, hpl_sercom_config.h, hpl_tc_config.h, hpl_eic_config.h, hpl_dmac_config.h, hpl_can_config.h, hpl_adc_config.h, hpl_port_config.h, hpl_gclk_config.h, hpl_mclk_config.h, hpl_oscctrl_config.h, hpl_osc32kctrl_config.h, hpl_divas_config.h, RTE_Components.h) | **DISCARD** — MCC generates equivalent files |
| `driver_init.c/h` | **DISCARD** — MCC generates `initialization.c` + `peripheral/` |
| `atmel_start.c/h` | **DISCARD** — MCC generates equivalent init code |
| `atmel_start_pins.h` | **DISCARD** — MCC generates pin configurations |
| `Device_Startup/*` | **DISCARD** — MCC generates startup_samc21.c |
| `hal/*` | **DISCARD** — MCC generates Harmony PLIB drivers |
| `hpl/*` | **DISCARD** — MCC generates equivalent HAL |
| `hri/*` | **KEPT** (by MCC in DFP pack, referencable from PLIB) |
| `GTron_Axis_Controller.cproj` | **DISCARD** — new MPLAB X project has its own |

---

## Must NOT Port (Dead Code)

| Old Path | Reason |
|----------|--------|
| `Bring_Up/spi.c/h` | Legacy empty stubs |
| `motor_dev/my_spi_func.c` | Commented out |
| `motor_dev/my_Ramp/myRamp.c/h` | Duplicate ramp (use Motion.c instead) |
| `TMC2209_Motion.h` + `TMC2209_motion.c` | Stubs (IOXP init moved elsewhere) |
| `Code_Dump/McuSwReset.c/h` | Unused |
| `All_Headers.h` | **REMOVED** — each .c includes only what it needs |
| SERCOM1 (PA00/PA01) init + ISR | Dead UART |
| TCC0 (GUIDE_STEP_COUNTER) macros | Commented out |
| FPGA GPIOs (PB11/PB12) init | Unused |
| All EIC callbacks for: LINENC_DIR, LINENC_Z, ROTENC_COUNT, ROTENC_DIR, ROTENC_Z, INDEX | Dead encoder counting (TMC4671 does all encoder work) |
| `GEncoderVars x_axis_encoder_counters` | All 6 encoder counters dead |

---

## Low-Level API Adaptation Notes

Old project uses Atmel Start APIs. New project uses Harmony V3 PLIB. The names differ but the functionality is identical.

**Keep your function names the same** (e.g., `gpio_set_pin_level`, `SPI_0_transfer_block`). You'll swap the implementation inside each function to use Harmony PLIB calls.

### GPIO
```
Old: gpio_set_pin_level(IOXP_CS, false)
New: GPIO_PinWrite(IOXP_CS, 0)
```

### SPI (SERCOM)
```
Old: hri_sercomspi_write_DATA_reg(SERCOM3, byte)
New: SERCOM3_SPI_WriteByte(byte)

Old: while (!(hri_sercomspi_read_INTFLAG_reg(SERCOM3) & SERCOM_SPI_INTFLAG_RXC))
New: while (!SERCOM3_SPI_IsTransmitterBusy())
```

### UART (SERCOM)
```
Old: usart_lite_send_byte(UART, byte)
New: SERCOM5_USART_WriteByte(byte)
```

### CAN
```
Old: hri_can_write_DATA0_reg(CAN1, id)
New: CAN1_MessageTransmit(id, dlc, data)
```

### EIC Callbacks
```
Old: ext_irq_register(PIN, callback)
New: EIC_CallbackRegister(PIN, callback, 0)
```

### WDT
```
Old: hri_wdt_write_CLEAR_reg(WDT, WDT_CLEAR_CLEAR_KEY)
New: WDT_Clear()
```

**The key rule:** Your higher-level logic (ramp math, CAN parsing, motor init sequence, hybrid trigger) does not change. Only the thin hardware-access wrappers at the bottom of the call stack get new Harmony PLIB implementations. From the outside, nothing is amiss.
