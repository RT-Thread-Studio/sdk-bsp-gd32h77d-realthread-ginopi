# LVGL 8.3.11 for the Gino SDK

Upstream: https://github.com/lvgl/lvgl/tree/v8.3.11

Source archive: https://github.com/lvgl/lvgl/archive/refs/tags/v8.3.11.tar.gz

Archive SHA-256: `83b7325a4b78cbb19a39f3ac75346c8086926d7faeab5ff2d825c20da0bbdb46`

This offline package retains the upstream `src`, `demos`, `examples`, and
`env_support/rt-thread` directories, the root headers, package metadata, and
`LICENCE.txt`. These files are unchanged from v8.3.11. Other platform ports,
documentation, tests, and upstream development tools are omitted from the SDK.

`projects/Gino_display_lvgl8/mklinks.bat` links the project to this package.
The project uses native RGB565, GT911 touch, and the built-in music demo.
