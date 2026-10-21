# GD32EmbeddedUI-demos

GD32EmbeddedUI 的可编辑 UI 工程和 RT-Thread 本地软件包。基于 GD32EmbeddedUI
0.3.0-beta 导出的 LVGL **8.3.11** 工程，画布为 **720×720、RGB565**。

## 在设计器中继续编辑

1. 在 GD32EmbeddedUI 中选择打开工程，打开本目录的
   [`GD32Embeddedui.gdlvgl`](GD32Embeddedui.gdlvgl)。
2. 添加控件、事件、图片和字体，保存并生成代码到当前工程目录。
3. 构建板级工程 [`Gino_display_gd32embeddedui`](../../projects/Gino_display_gd32embeddedui/README_zh.md)。
   SCons 每次运行会递归收集 `generated/` 和 `custom/` 中的 `.c` 文件。
4. 新增或删除源文件后，MDK 用户执行 `scons --target=mdk5` 更新文件列表；
   Studio 用户执行 `scons --target=eclipse` 并刷新工程。

设计器和板级工程使用同一份 UI 源码，无需从桌面目录反复复制。
仓库目前附带的是原始空白工程：没有控件，`custom_init()` 也为空，
所以上板后不会显示音乐 demo 或测试按钮。请在设计器中添加控件并生成代码。

## 目录与边界

| 路径 | 用途 |
| --- | --- |
| `GD32Embeddedui.gdlvgl` | 设计器工程，保存页面、控件和资源配置 |
| `assets/` | 设计器使用的原始图片、字体和视频资源 |
| `generated/` | 自动生成的界面、事件、主题、多语言和 C 资源 |
| `custom/` | 自定义逻辑；`ui_init()` 内部会调用 `custom_init()` |
| `port/aic_ui.h` | RT-Thread 平台头文件，关闭模拟器标志 |
| `simulator/`、`CMakeLists.txt` | 原始 PC 模拟器工程，供设计器使用 |
| `SConscript` | 板端源码和头文件路径收集 |

板端只收集 `generated/`、`custom/`，使用 BSP 中的 LVGL 和显示/触摸驱动。
`simulator/main.c`、Windows API 和模拟器第三方库不参与固件构建。
PC 模拟器仍需要设计器提供的 LVGL/工具链，或按其 CMake 提示配置依赖。

不要把业务修改写进 `generated/`，重新生成时会覆盖它。保留 `port/` 和
`SConscript`；如果从另一份设计器工程迁移，请一起更新 `.gdlvgl`、`assets/`、
`generated/` 和所需的 `custom/`，以保持设计文件和源码一致。

## 板端接入

`lv_user_gui_init()` 在 LVGL 线程中调用 `ui_init()`，此时显示和触摸已完成初始化。
`custom_init()` 由生成器入口调用，不要再调用一次，也不需要增加 `lv_init()`、
`lv_tick_inc()` 或另一个 `lv_timer_handler()` 循环。

BSP 的 `applications/lv_conf.h` 引入 `generated/config/ui_config.h` 和
`generated/config/lv_conf_patch.h`，让导出的控件/字体选项同时作用于 LVGL 库。
当前板端适配固定为 LVGL 8.3.11、720×720、RGB565，修改画布或色深会触发编译检查。

图片和字体请使用生成器的 **C 数组/静态字体** 输出，并放在 `generated/` 下。
`assets/` 中的原始文件不会自动变成板端文件系统；本示例没有配置资源文件系统、
FreeType 或 FFmpeg，PC 模拟器中的文件路径和视频功能不能直接搬到板上。

这是 SDK 内的本地软件包，不需要 `pkgs --update`；GD32 导出文件保留原有版权和许可头。
