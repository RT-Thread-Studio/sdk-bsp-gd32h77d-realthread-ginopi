# GD32EmbeddedUI-demos

An editable GD32EmbeddedUI project and local RT-Thread package, exported by
GD32EmbeddedUI 0.3.0-beta for **LVGL 8.3.11**, **720×720**, **RGB565**.

## Edit and regenerate

Open [`GD32Embeddedui.gdlvgl`](GD32Embeddedui.gdlvgl) in GD32EmbeddedUI. Edit the
screens, events and resources, then save and generate code in this directory.
The [Gino board example](../../projects/Gino_display_gd32embeddedui/README.md)
uses these same sources. SCons discovers `.c` files recursively under
`generated/` and `custom/` on every invocation.

After adding or removing source files, regenerate the MDK project with
`scons --target=mdk5`, or update Studio with `scons --target=eclipse` and refresh
the project. Run these commands from the board example directory.

The bundled design is the original **empty project**. It has no widgets and an
empty `custom_init()`. Add widgets and generate code in the designer to obtain a
visible, interactive UI; this package does not start an LVGL demo.

## Layout

| Path | Purpose |
| --- | --- |
| `GD32Embeddedui.gdlvgl` | Editable screens, widgets and resource configuration |
| `assets/` | Original design resources |
| `generated/` | Generated UI, events, themes, translations and C assets |
| `custom/` | Application logic; called through `custom_init()` |
| `port/aic_ui.h` | RT-Thread platform header with simulator mode disabled |
| `simulator/`, `CMakeLists.txt` | Original PC simulator used by the designer |
| `SConscript` | Firmware source and include-path collection |

Firmware only builds `generated/` and `custom/`; it uses the BSP's LVGL,
display and touch drivers. The Windows simulator and its third-party libraries
are excluded. PC simulation still requires the designer's LVGL/toolchain or the
dependencies described by its CMake configuration.

Keep application changes in `custom/`. Regeneration replaces `generated/`.
Preserve `port/` and `SConscript`. When importing another design, keep the
`.gdlvgl`, `assets/`, `generated/` and relevant `custom/` files together.

## Firmware integration

The LVGL thread calls `ui_init()` after display and input initialization.
The generated entry already calls `custom_init()`; do not call it twice or add
another LVGL initialization, tick source or timer loop.

The BSP's `applications/lv_conf.h` includes both exported configuration headers,
including `generated/config/lv_conf_patch.h`, so widget/font settings also apply
to the LVGL library. The board port checks LVGL 8.3.11, 720×720 and native RGB565.

Export images and fonts as C arrays/static fonts under `generated/`. Original
files in `assets/` are not automatically available to the firmware. This example
does not configure a resource filesystem, FreeType or FFmpeg.

This is a local SDK package; `pkgs --update` is unnecessary. Exported files retain
their original GigaDevice copyright and license notices.
