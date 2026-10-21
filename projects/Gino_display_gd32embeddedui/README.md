# Gino_display_gd32embeddedui

A standalone GD32H77D Gino example for GD32EmbeddedUI exports, using **LVGL
8.3.11**, a **720×720 RGB565 MIPI DSI LCD** and **GT911 touch**.

## 1. Editable UI package

The shared [GD32EmbeddedUI-demos package](../../packages/GD32EmbeddedUI-demos/README.md)
contains the editable
[`GD32Embeddedui.gdlvgl`](../../packages/GD32EmbeddedUI-demos/GD32Embeddedui.gdlvgl)
project, resources, generated code and custom application code. Open that file
in GD32EmbeddedUI, edit the UI and generate code in place. The board project uses
these same sources through its `packages/GD32EmbeddedUI-demos` directory link.

The supplied design is empty, with `custom_init()` reserved for application
initialization. Add a label or button in the designer and generate code to check
display output and touch.

## 2. Hardware and initialization

The example reuses the LVGL 8 board configuration, LCD, GT911 and SDRAM drivers.
Two 200-line RGB565 buffers in AXI SRAM feed IPA transfers to the SDRAM display
framebuffer. The RT-Thread LVGL thread initializes LVGL, display and input,
calls `ui_init()`, then handles rendering and input continuously.

The generated entry already calls `custom_init()`. Do not initialize LVGL or
call these entry points again from `main()`. Put application logic in `custom/`
and synchronize any UI access from other threads with the LVGL thread.

## 3. Open the board project

From this directory:

```powershell
.\mklinks.bat
scons --target=mdk5
```

Open `project.uvprojx` in MDK5. The target command generates project files only.
For RT-Thread Studio, import this directory or create the example through the
SDK catalog. Update Studio source lists using `scons --target=eclipse` and
refresh the project. On Linux, establish links with `sh mklinks.sh`.

Shared dependencies are `rt-thread`, `libraries`, `LVGL-v8.3.11`, `gt911-latest`
and `GD32EmbeddedUI-demos`. SDK exports copy the dependencies into the standalone
project. In that case, edit its local
`packages/GD32EmbeddedUI-demos/GD32Embeddedui.gdlvgl`.

## 4. Regenerate the UI

Keep the designer at LVGL 8.3.11, 720×720 and 16-bit color. Export images and
fonts as C arrays/static fonts under `generated/`. SCons recursively collects
C sources and include paths from `generated/` and `custom/`. After adding or
removing files, regenerate the MDK/Studio project before building firmware.

`applications/lv_conf.h` includes the exported `ui_config.h` and
`lv_conf_patch.h` so configuration applies to LVGL and the generated code.
Windows simulator sources and third-party libraries are excluded from firmware.
This example has no resource filesystem, FreeType or FFmpeg integration; raw
files in `assets/` and PC media paths require additional board support.

## 5. Board checks

- UART1 prints the project name; the PC4 LED blinks.
- Use `list_device` and `gino_device_probe` to inspect `lcd` and `gt911`.
- Successful display initialization is followed by
  `GD32EmbeddedUI initialized (720x720, RGB565)`.
- The empty design has no controls. Add a button in the designer, generate
  code and verify touch on the board.

Validation covers project generation and relevant source syntax checks.
Full firmware build, flashing and hardware operation remain to be verified.
