# Gino_display_gd32embeddedui

GD32H77D Gino 开发板运行 GD32EmbeddedUI 导出界面的独立工程。
使用 **LVGL 8.3.11、720×720 MIPI DSI LCD、RGB565、GT911 触摸**。

## 1. 可编辑的 UI 软件包

UI 放在共享软件包
[`../../packages/GD32EmbeddedUI-demos`](../../packages/GD32EmbeddedUI-demos/README_zh.md)，
通过本工程 `packages/GD32EmbeddedUI-demos` 目录链接引用。
直接用 GD32EmbeddedUI 打开软件包内的
[`GD32Embeddedui.gdlvgl`](../../packages/GD32EmbeddedUI-demos/GD32Embeddedui.gdlvgl)，
即可继续编辑、保存和生成代码，板端构建会读取同一份导出结果。

当前附带空白设计工程，`custom_init()` 保留为应用初始化入口。
可以在设计器中添加标签或按钮，保存并生成代码后验证显示和触摸。

## 2. 硬件与运行流程

复用 `Gino_display_lvgl8` 的板级配置和显示/触摸适配：

- LCD、GT911、SDRAM 由现有板级驱动初始化。
- 两个 200 行 RGB565 绘制缓冲位于 AXI SRAM，IPA 将绘制结果复制到 SDRAM 帧缓冲。
- RT-Thread 的 LVGL 线程依次初始化 LVGL、显示、触摸，然后调用 `ui_init()`。
- `ui_init()` 内部调用 `custom_init()`；LVGL 线程持续处理刷新和触摸事件。

不要在 `main()` 中再次初始化 LVGL 或调用 `ui_init()`。应用逻辑写在软件包的
`custom/` 中；从其他线程更新 UI 时，需要与 LVGL 线程进行同步。

## 3. 打开板级工程

在本工程目录执行：

```powershell
.\mklinks.bat
scons --target=mdk5
```

然后用 MDK5 打开 `project.uvprojx`。`scons --target=mdk5` 只生成工程文件。
使用 RT-Thread Studio 时，可导入当前目录，或从 SDK 示例列表创建本工程。
Studio 更新文件列表使用：

```powershell
scons --target=eclipse
```

执行后刷新 Studio 工程。Linux 使用 `sh mklinks.sh` 建立共享源码链接。
本工程链接 `rt-thread`、`libraries`、`LVGL-v8.3.11`、`gt911-latest` 和
`GD32EmbeddedUI-demos`。SDK 示例导出为独立工程时，这些依赖会复制到工程内；
此时应打开独立工程 `packages/GD32EmbeddedUI-demos/GD32Embeddedui.gdlvgl`。

## 4. 后续修改界面

1. 打开上述 `.gdlvgl` 文件，在 GD32EmbeddedUI 中编辑并生成代码。
2. 保持 LVGL 8.3.11、720×720、16 位色深。
3. 图片和字体使用 C 数组/静态字体输出，放在 `generated/` 下。
4. 新增或删除源文件后重新生成 MDK/Studio 工程文件，再进行固件构建和下载。

SCons 自动递归收集 `generated/`、`custom/` 中的 `.c` 文件及头文件目录。
`applications/lv_conf.h` 加载导出的 `ui_config.h` 和 `lv_conf_patch.h`。
PC 模拟器、Windows 入口及第三方库不会加入板端构建。

本示例没有配置资源文件系统、FreeType 或 FFmpeg。设计器预览中使用的文件字体、
图片路径和视频需要额外移植，不能仅靠复制 `assets/` 在板端使用。

## 5. 上板检查

- UART1 控制台输出工程名称，PC4 LED 闪烁。
- `list_device` 和 `gino_device_probe` 可以检查 `lcd`、`gt911` 等设备。
- 显示初始化成功后输出 `GD32EmbeddedUI initialized (720x720, RGB565)`。
- 空白设计默认没有控件；在设计器中添加按钮并生成代码后验证触摸响应。

验证范围为工程生成和相关源码语法检查；完整固件构建、下载和硬件运行仍需验证。
