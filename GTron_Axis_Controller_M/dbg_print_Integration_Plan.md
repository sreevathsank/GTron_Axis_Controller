# dbg_print Integration Plan — GTron AxC Firmware

**Status:** Approved, ready to execute.
**Author/session:** OpenCode (claude-opus-4.7), with user-driven decisions.
**Companion plan:** `Hybrid_Trigger_Implementation_Plan.md` (executes after this one).
**Source library:** `SYS_DEBUG/src/dbg_print/` and `SYS_DEBUG/dbg_print_docs.md`.

---

## 1. Goal

Replace the AxC firmware's current synchronous `printf()` debug logging path
(SERCOM7 USART @ 2 Mbaud via Atmel Start `usart_sync` + `stdio_redirect`) with
the DMA-based `dbg_print` library. Convert all 338+ existing
`PRINTF_DEBUG ? printf(...) : 0` call sites to `DBG_Printf(...)` in a
big-bang rewrite. Delete the `PRINTF_DEBUG` macro. Remove unconditional
ISR `printf` calls outright. Then proceed to the Hybrid Triggering
implementation on top of this new foundation.

---

## 2. Confirmed environment facts

| Fact | Value | Source |
|---|---|---|
| MCU | ATSAMC21N18A | matches reference transport |
| Framework | **Atmel Start ASF** (NOT Microchip Harmony) | `atmel_start.c`, `hpl_dmac.c`, `usart_sync_*` API |
| Current stdio TX | **SERCOM7** | `driver_init.c:375` — `usart_sync_init(&TARGET_IO, SERCOM7, NULL)` |
| Current baud rate | **2,000,000** | `hpl_sercom_config.h:314` — `CONF_SERCOM_7_USART_BAUD 2000000` |
| Current stdio mechanism | `usart_sync_*` (blocking, polled) | `stdio_start.c:21-22` |
| DMAC | Enabled and initialized; **all 16 channels at `_SETTINGS = 0`** | `hpl_dmac_config.h` |
| DMAC API surface | ASF `_dma_*` (in `hal/include/hpl_dma.h`); HRI helpers in `hri_dmac_c21.h` | inspected |
| RTOS | None | bare-metal main loop |
| `PRINTF_DEBUG` macro location | `Macros.h:20` — `#define PRINTF_DEBUG 1` | grep |
| Number of `PRINTF_DEBUG?printf` / `PRINTF_DEBUG && printf` call sites | **338+** | grep across project |

---

## 3. The SERCOM6/7 trigger-source GUI gap

**Problem:** Atmel Start GUI for SAMC21 omits SERCOM6 and SERCOM7 from the
DMA trigger source list. Only SERCOM0–SERCOM5 RX/TX are listed (values
0x02 through 0x0D), then it jumps to CAN0/CAN1 Debug at 0x0E/0x0F.

**Cause:** Atmel Start's SAMC21 DMAC config template appears to use the
J/G-variant trigger source table. The SAMC21**N** variant (our chip — N18A)
has 8 SERCOMs and supports SERCOM6/7 as DMA triggers in hardware, but the
GUI metadata doesn't expose them.

**Mitigation:** Configure DMA Channel 0 **programmatically** in
`dbg_transport.c` rather than through the Atmel Start GUI. Atmel Start
will not be used for any per-channel DMA configuration at all.

---

## 4. Locked decisions (from session)

| Decision | Locked answer |
|---|---|
| Order of work | dbg_print integration first, then Hybrid Triggering |
| Migration strategy | Big-bang rewrite |
| Severity assignment | All-DEBUG mechanical pass, then selective promotion |
| ISR `printf` calls | Delete entirely |
| `PRINTF_DEBUG` macro | Delete after rewrite |
| Library location | `Bring_Up/Debug/` |
| SERCOM | SERCOM7 @ 2 Mbaud (already configured as `TARGET_IO`) |
| DMA Channel | Channel 0 (currently unused) |
| DMA config method | **Programmatic in `dbg_transport.c`** (Option B1) |
| USART name | Keep as `TARGET_IO` — no new peripheral added |
| Old stdio path | Leave intact as passive fallback |
| Stage buffer | 512 bytes |
| Commit structure | Two stages: (1) mechanical, (2) severity promotion |
| RTOS mode | `DBG_RTOS_NONE` (bare-metal) |
| Mechanical rewrite tool | PowerShell script |
| Plan document | This file (separate from Hybrid plan) |

---

## 5. Phase 0 — Pre-flight verification (read-only)

Three sub-tasks, must complete before any code changes:

### 0.1 — SERCOM7 TX DMAC trigger source from datasheet

Open `SYS_DEBUG/SAMC20_C21_Family_Data_Sheet_DS60001479D.pdf`, navigate to
§22 (DMAC) Table 22-7 "DMA Trigger Source" (or equivalent section).
Confirm and record:

- Exact trigger source value for **SERCOM7 TX** on SAMC21N variant.
- Exact trigger source value for SERCOM7 RX (for completeness).
- How SERCOM6 RX/TX overlap with the CAN0/CAN1 Debug values.

Cross-check against `samc21n18a.h` (CMSIS device header) for symbols like
`SERCOM7_DMAC_ID_TX` if defined.

### 0.2 — HRI register helper API for DMAC

Open `hri/hri_dmac_c21.h` and `hpl/dmac/hpl_dmac.c`. Confirm:

- The channel selection idiom (write `CHID`, then operate on `CHCTRLA`/
  `CHCTRLB` register window).
- Exact helper names for: write CHID, set/clear CHCTRLA.ENABLE, write
  CHCTRLB, set CHINTEN.TCMPL.
- Whether `_dma_resource->dma_cb.transfer_done` is the correct ASF
  callback hook for our channel-0 TCMPL.

### 0.3 — Linker --specs for float printf support

Open `GTron_Axis_Controller.cproj` (or the relevant Makefile) and check
linker flags for `--specs=nano.specs`, `-u _printf_float`, or
`--specs=nosys.specs`. The fact that existing `printf("%.2f", ...)`
output works in production today proves float support is enabled, but
explicitly recording the flag in the plan removes ambiguity.

---

## 6. Phase 1 — Atmel Start GUI work (NO-OP)

**Do NOT make any changes in Atmel Start GUI for DMA channel
configuration.** Verification only:

1. Confirm `CONF_DMAC_ENABLE = 1` in `hpl_dmac_config.h` (it is).
2. Confirm `system_init()` calls `_dma_init()` (it does, via `hpl_init.c`).
3. Confirm `CONF_DMAC_CHANNEL_0_SETTINGS = 0` (channel 0 untouched by GUI).

Net result of Phase 1: zero file changes. Phase 1 exists as a checkbox
to prevent later confusion about whether the GUI was supposed to be used.

---

## 7. Phase 2 — Drop in dbg_print library

### 7.1 Files added under `Bring_Up/Debug/`

| File | Source | Modifications |
|---|---|---|
| `dbg_print.h` | `SYS_DEBUG/src/dbg_print/` | None |
| `dbg_print.c` | `SYS_DEBUG/src/dbg_print/` | None |
| `dbg_print_config.h` | `SYS_DEBUG/src/dbg_print/` | Edit (see 7.2) |
| `dbg_transport.h` | `SYS_DEBUG/src/dbg_print/` | None |
| `dbg_transport.c` | NEW (ASF-based, programmatic DMA) | Full rewrite |

### 7.2 `dbg_print_config.h` edits

```c
#define DBG_BUF_SIZE        128
#define DBG_STAGE_SIZE      512   /* AxC has prints up to ~250 chars */
#define DBG_DEFAULT_LEVEL   ERR_LVL_DEBUG

/* #define DBG_RTOS_FREERTOS -- DO NOT define */
#define DBG_RTOS_NONE       1
```

### 7.3 New `dbg_transport.c` (ASF + programmatic DMA config)

Skeleton (exact HRI helper names finalized in Phase 0.2):

```c
#include "dbg_transport.h"
#include "atmel_start.h"
#include "hpl_dma.h"

#define DBG_DMAC_CHANNEL              0
#define DBG_DMAC_TRIGSRC_SERCOM7_TX   52u   /* SERCOM7_DMAC_ID_TX, samc21n/include/instance/sercom7.h:126 (Phase 0.1 confirmed) */

static struct _dma_resource *s_dbg_resource;

static void dma_done_cb(struct _dma_resource *resource) {
    (void)resource;
    DBG_TransferComplete();
}

static bool transport_send(const uint8_t *data, size_t len) {
    if (_dma_set_source_address(DBG_DMAC_CHANNEL, data) < 0)        return false;
    if (_dma_set_destination_address(DBG_DMAC_CHANNEL,
            (void *)&((Sercom *)SERCOM7)->USART.DATA.reg) < 0)      return false;
    if (_dma_set_data_amount(DBG_DMAC_CHANNEL, len) < 0)            return false;
    return _dma_enable_transaction(DBG_DMAC_CHANNEL, false) >= 0;
}

static bool transport_is_busy(void) {
    return (hri_dmac_read_BUSYCH_reg(DMAC) & (1u << DBG_DMAC_CHANNEL)) != 0;
}

static const dbg_transport_t s_transport = {
    .send    = transport_send,
    .is_busy = transport_is_busy,
};

void DBG_TransportInit(void) {
    /* Configure DMAC channel 0 directly because Atmel Start GUI omits
     * SERCOM6/7 from its trigger source list (J/G-variant table bug). */

    /* 1. Select channel, disable, soft-reset */
    hri_dmac_write_CHID_reg(DMAC, DBG_DMAC_CHANNEL);
    hri_dmac_clear_CHCTRLA_ENABLE_bit(DMAC);
    hri_dmac_set_CHCTRLA_SWRST_bit(DMAC);
    while (hri_dmac_get_CHCTRLA_SWRST_bit(DMAC));

    /* 2. CHCTRLB: SERCOM7 TX trigger, beat trigger, level 0 */
    hri_dmac_write_CHCTRLB_reg(DMAC,
        DMAC_CHCTRLB_TRIGSRC(DBG_DMAC_TRIGSRC_SERCOM7_TX) |
        DMAC_CHCTRLB_TRIGACT_BEAT |
        DMAC_CHCTRLB_LVL_LVL0);

    /* 3. Descriptor: byte beat, src-inc, no dst-inc, valid */
    extern DmacDescriptor _descriptor_section[];
    _descriptor_section[DBG_DMAC_CHANNEL].BTCTRL.reg =
        DMAC_BTCTRL_VALID |
        DMAC_BTCTRL_BEATSIZE_BYTE |
        DMAC_BTCTRL_SRCINC |
        DMAC_BTCTRL_BLOCKACT_NOACT;

    /* 4. Register completion callback via ASF resource */
    _dma_get_channel_resource(&s_dbg_resource, DBG_DMAC_CHANNEL);
    s_dbg_resource->dma_cb.transfer_done = dma_done_cb;

    /* 5. Enable TCMPL interrupt */
    hri_dmac_set_CHINTEN_TCMPL_bit(DMAC);

    /* 6. Enable channel */
    hri_dmac_set_CHCTRLA_ENABLE_bit(DMAC);
}

const dbg_transport_t *DBG_TransportGet(void) {
    return &s_transport;
}
```

### 7.4 Add files to project

Add the five files to `GTron_Axis_Controller.cproj` Compile entries.
Verify `Bring_Up/Debug/` is on the include search path (it should be
implicitly, but check).

---

## 8. Phase 3 — Wire into startup

**File: `main.c`**

After `atmel_start_init()` returns, before any `printf` (or after the
existing first `printf` if we want to compare paths during smoke test):

```c
#include "Bring_Up/Debug/dbg_print.h"
#include "Bring_Up/Debug/dbg_transport.h"

int main(void) {
    atmel_start_init();
    DBG_TransportInit();
    DBG_Init(DBG_TransportGet());
    DBG_SetLevel(ERR_LVL_DEBUG);
    DBG_Printf(ERR_LVL_INFO, "dbg_print online\n");
    /* ... existing main body ... */
}
```

---

## 9. Phase 4 — Smoke test + checkpoint commit

**USER VERIFIES:**

1. Build (Atmel Studio / make).
2. Flash to AxC board.
3. Open serial terminal at 2 Mbaud.
4. Reset and observe:
   - The legacy `printf("\nAxC - GTron TOP\n")` (or whichever axis)
     still prints (passive fallback).
   - `[INF] dbg_print online` appears.
5. Run a basic CAN command (e.g., reeler start) — confirm the existing
   `PRINTF_DEBUG ? printf(...)` outputs still work.

**Checkpoint commit:** "Add dbg_print library with ASF DMAC transport (channel 0, SERCOM7 TX)".

This commit is reversible without affecting any existing logic — only
additions.

---

## 10. Phase 5 — Mechanical big-bang rewrite

### 10.1 Script-driven regex transform

Author `tools/migrate_printf_to_dbgprintf.ps1` (PowerShell, since project
is Windows). It walks `*.c`, `*.h` under
`GTron_Axis_Controller/GTron_Axis_Controller/` (excluding `Code_Dump/`,
`Debug/`, `examples/`, `hpl/`, `hri/`, `hal/`, `Device_Startup/`,
`config/`, `stdio_redirect/`, `Bring_Up/Debug/` itself).

Transforms (case-sensitive, anchored to non-comment context):

| Match (regex) | Replace |
|---|---|
| `PRINTF_DEBUG\s*\?\s*printf\((.*?)\)\s*:\s*0\s*;` | `DBG_Printf(ERR_LVL_DEBUG, $1);` |
| `PRINTF_DEBUG\s*&&\s*printf\((.*?)\)\s*;` | `DBG_Printf(ERR_LVL_DEBUG, $1);` |

The `(.*?)` is non-greedy. Multi-line printf calls (rare in this codebase
based on grep) are handled with the `Singleline` regex flag plus careful
balancing. If a file has nested parens that confuse the regex, the script
flags it for manual review.

After regex pass, the script:

1. Adds `#include "Bring_Up/Debug/dbg_print.h"` to any modified `.c` that
   doesn't already include it (insert after the last existing `#include`).
2. Writes a per-file diff summary to `migrate_report.txt`.

### 10.2 ISR-printf removal (manual edits, NOT in script)

Delete (use `Edit` tool with exact line content):

- `Motion.c:622-626` — Z-pulse ISR axis-name `printf` switch cases.
- `Motion.c:647` — `printf("\n Reeler Left Limit Sensor Edge Detected!\n")`.
- `Motion.c:661` — `printf("\n Reeler Right imit Sensor Edge Detected!\n")`.

These are kept out of the script because they're unconditional `printf`
calls (no `PRINTF_DEBUG` gate) and need surgical removal, not transform.

### 10.3 Remove `PRINTF_DEBUG` macro

- Delete line `Macros.h:20` — `#define PRINTF_DEBUG 1`.
- Verify zero remaining references via grep across the project (excluding
  documentation files like `Code_Dump/tlv_flash.h` comments).

### 10.4 Build verification

After script + manual ISR delete + macro delete:

1. `grep -rn "printf(" GTron_Axis_Controller/` — should be zero matches in
   application code (excluding `dbg_print.c` itself which uses
   `vsnprintf`, and excluding generated/dump folders).
2. `grep -rn "PRINTF_DEBUG" GTron_Axis_Controller/` — zero matches.
3. Compile clean.

### 10.5 Hardware verification

Flash, observe `[DBG]`-prefixed output for normal operation, all coming
through DMA at 2 Mbaud non-blocking.

### 10.6 Commit 1

"Replace printf debug logging with DMA-based DBG_Printf (mechanical pass + ISR-printf removal)"

---

## 11. Phase 6 — Selective severity promotion

### 11.1 Promotion rubric

| To `ERR_LVL_INFO` | Lifecycle / configuration / state changes |
|---|---|
| | "Reeler Homing Done", "Move Done", "Reeler Start Motor", "Reeler Stop Motor" |
| | "Set Velocity", "Set Initial Position", "Set Teeth Number" |
| | Board-active ping replies, axis-detected at boot |

| To `ERR_LVL_WARNING` | Recoverable abnormal state |
|---|---|
| | "Already in Open/Close Limit. Not moving" |
| | "Target Position is same as Current Position. Not Moving" |
| | "Limit is Hit" (sensor-edge style, non-fault) |

| To `ERR_LVL_ERROR` | Faults / invalid commands |
|---|---|
| | "STOPPED MOTOR MOVEMENT AS THE MOTOR IS STALLED OR STUCK" |
| | "Reeler Motor Invalid Operation Rxcvd" |
| | "Hybrid Trigger Invalid Operation Rxcvd" |
| | All `default: ... Invalid Operation` cases in the CAN parser |

| Stay `ERR_LVL_DEBUG` | All other call sites — dev/diagnostic prints |

### 11.2 Execution

Walk every `DBG_Printf(ERR_LVL_DEBUG, ...)` call in the modified files,
apply rubric. Estimate ~30–50 promotions out of 338+.

### 11.3 Commit 2

"Assign severity levels to debug log messages"

---

## 12. Phase 7 — Update Hybrid Triggering plan

In `Hybrid_Trigger_Implementation_Plan.md`:

1. Replace all `PRINTF_DEBUG ? printf(...)` references with
   `DBG_Printf(level, ...)`.
2. Adjust §5 (slip-detection log call) to
   `DBG_Printf(ERR_LVL_WARNING, ...)`.
3. In §15 (confirmation tasks at implementation start):
   - Remove the "ISR printf removal" task — already done in Phase 5.
   - Add a note: "ISRs are now flag-only; no logging in ISR context."
4. Update the Discoveries section to record that ISR printfs were
   eliminated as part of dbg_print integration.

### 12.1 Commit 3

"Update Hybrid Triggering plan to use DBG_Printf API"

---

## 13. Phase 8 — Hybrid Triggering implementation

Execute `Hybrid_Trigger_Implementation_Plan.md` per its own phases.
This phase is out of scope for *this* plan document.

---

## 14. Files touched (summary)

### New files
- `Bring_Up/Debug/dbg_print.h`
- `Bring_Up/Debug/dbg_print.c`
- `Bring_Up/Debug/dbg_print_config.h`
- `Bring_Up/Debug/dbg_transport.h`
- `Bring_Up/Debug/dbg_transport.c` (ASF-rewritten)
- `tools/migrate_printf_to_dbgprintf.ps1` (helper script)
- `dbg_print_Integration_Plan.md` (this file)

### Modified files
- `main.c` — DBG_Init() wire-up + printf rewrites.
- `Macros.h` — delete `PRINTF_DEBUG` define.
- `Bring_Up/Motion/Motion.c` — printf rewrites + ISR-printf deletes
  (lines 622-626, 647, 661).
- `Bring_Up/Motion/Hybrid_Trigger.c` — printf rewrites.
- `Bring_Up/GTron_Cmd_Parser/gtron_can_cmd_parser.c` — printf rewrites.
- `Bring_Up/CAN/IMM_CAN_Read.c` — printf rewrites (mostly commented).
- `Bring_Up/CAN/IMM_CAN_Write.c` — if any.
- `Bring_Up/IO_Expander/*.c` — if any.
- `Bring_Up/DBG_bring_up.c` — if any.
- All other `*.c` containing `PRINTF_DEBUG` or bare `printf(`.
- `GTron_Axis_Controller.cproj` — add new Debug/ files to compile list.

### Files NOT modified
- All Atmel Start generated files in `config/`, `hpl/`, `hri/`, `hal/`,
  `Device_Startup/`, `examples/`, `driver_init.{c,h}`, `atmel_start.{c,h}`.
- `stdio_start.c`, `stdio_redirect/` — left as passive fallback.
- `Code_Dump/` folder — excluded from rewrite.

---

## 15. Risks

| # | Risk | Mitigation |
|---|---|---|
| 1 | SERCOM7 TX trigger source value wrong | Phase 0.1 datasheet confirmation is gating — no code until verified |
| 2 | HRI helper names differ from skeleton | Phase 0.2 — confirmed against `hri_dmac_c21.h` before writing transport |
| 3 | DMAC callback dispatch shape mismatch | If `_dma_resource.dma_cb.transfer_done` doesn't fire, fall back to overriding weak `DMAC_Handler` |
| 4 | Two writers to SERCOM7.DATA temporarily | Phase 5 eliminates all `printf` calls — only window is between Phase 3 and Phase 5 commits, during which we're careful not to interleave; smoke test in Phase 4 only exercises new path |
| 5 | Regex misses edge cases (multi-line printf, comments) | Script reports flagged files; manual cleanup if any |
| 6 | `vsnprintf` float support | Phase 0.3 verifies linker flags |
| 7 | DMA channel 0 already used by something | Confirmed unused in Phase 0 (all `_SETTINGS = 0`) |
| 8 | Stage buffer too small for longest existing print | 512 bytes covers all observed prints; truncation is harmless if it happens |
| 9 | IRQ priority/preemption issues | Smoke-tested in Phase 4; bare-metal mode uses spin-flag, no priority inversion possible |
| 10 | RAM budget | Total ~768 bytes (256 dbg_buf + 512 stage + ~16 static) — verify against `.map` file |

---

## 16. Open items / TBDs

- **Phase 0.1 result** — **DONE.** `SERCOM7_DMAC_ID_TX = 52` (per
  `samc21n18a` CMSIS pack, `instance/sercom7.h:126`). `SERCOM6_DMAC_ID_TX = 50`,
  `SERCOM7_DMAC_ID_RX = 51`. `DMAC_CHCTRLB_TRIGSRC` is a 6-bit field
  (mask `0x3F`, max 63) — values 51/52 fit. Hardware fully supports
  SERCOM6/7 DMA triggers; only Atmel Start GUI's enum list omits them.
- **Phase 0.2 result** — DONE. HRI naming pattern confirmed in
  `hri/hri_dmac_c21n.h` (channel-indexed access via `hri_dmac_write_CHID_reg`
  then per-register helpers).
- **Phase 0.3 result** — DONE. `-u _printf_float` confirmed at
  `GTron_Axis_Controller.cproj:439`.
- **Project file format** — `.cproj` (Atmel Studio XML) vs `.X` MPLAB.
  AxC uses `.cproj` (already confirmed). Adding source files requires
  XML edit; will be done in Phase 2.

---

## 17. Decision Log

1. Integrate dbg_print **before** Hybrid Triggering work, as a foundation.
2. Big-bang rewrite over compatibility shim — cleaner final state.
3. Severity: mechanical-DEBUG pass first, selective promotion second.
4. ISR `printf` calls **deleted entirely** (not deferred to main loop).
5. `PRINTF_DEBUG` macro **deleted** (no compile-time kill-switch retained).
6. Library lives at `Bring_Up/Debug/`.
7. SERCOM7 reused — no peripheral relocation.
8. Old stdio path **left intact** as passive fallback (not removed).
9. Stage buffer size: **512 bytes**.
10. Two-commit strategy: mechanical pass + severity promotion separated.
11. Atmel Start GUI **NOT used** for DMA channel 0 — programmatic config
    in `dbg_transport.c` due to GUI's missing SERCOM6/7 trigger sources.
12. Callback registration via ASF `_dma_resource->dma_cb.transfer_done`,
    NOT via overriding weak `DMAC_Handler`.
13. Float printf: assumed working (existing `%.2f` calls work today),
    confirmed via Phase 0.3 linker check.
14. Mechanical rewrite: **PowerShell script**, not manual or Edit-tool.
15. USART name in Atmel Start: keep as `TARGET_IO`, no rename, no new
    peripheral.

---

End of plan.
