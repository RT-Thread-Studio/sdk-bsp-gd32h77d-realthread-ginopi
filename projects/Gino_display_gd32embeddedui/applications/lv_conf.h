/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include "generated/config/ui_config.h"

#define LV_COLOR_DEPTH                  UI_COLOR_DEPTH
#define LV_COLOR_16_SWAP                0

#define LV_HOR_RES_MAX                  UI_SCREEN_WIDTH
#define LV_VER_RES_MAX                  UI_SCREEN_HEIGHT

#define LV_USE_PERF_MONITOR             0

#define LV_USE_DEMO_BENCHMARK           0
#define LV_USE_DEMO_MUSIC               0

#define LV_FONT_MONTSERRAT_12           1
#define LV_FONT_MONTSERRAT_16           1

/* Apply the widget/font options exported by GD32EmbeddedUI to LVGL itself. */
#include "generated/config/lv_conf_patch.h"

#if (UI_SCREEN_WIDTH != 720) || (UI_SCREEN_HEIGHT != 720) || \
    (LV_HOR_RES_MAX != 720) || (LV_VER_RES_MAX != 720)
#error "Export the GD32EmbeddedUI project at 720x720 for the Gino LCD"
#endif

#if (UI_COLOR_DEPTH != 16) || (LV_COLOR_DEPTH != 16) || LV_COLOR_16_SWAP
#error "The Gino LCD requires native RGB565 (16-bit, no byte swap)"
#endif

#endif /* LV_CONF_H */
