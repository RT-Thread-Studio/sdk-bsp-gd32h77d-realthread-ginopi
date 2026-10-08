/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GINO_LVGL_COMPAT_H
#define GINO_LVGL_COMPAT_H

#include <lvgl.h>

#if LVGL_VERSION_MAJOR == 8

#if (LV_COLOR_DEPTH != 16) || LV_COLOR_16_SWAP
#error "The Gino LCD port requires native RGB565 (LV_COLOR_DEPTH=16, LV_COLOR_16_SWAP=0)"
#endif

typedef lv_disp_t lv_display_t;
typedef lv_disp_drv_t lv_port_flush_driver_t;
typedef lv_color_t lv_port_pixel_t;
typedef lv_indev_drv_t lv_port_indev_driver_t;
typedef lv_img_dsc_t lv_image_dsc_t;

#define lv_port_flush_ready             lv_disp_flush_ready
#define lv_port_flush_is_last           lv_disp_flush_is_last
#define lv_display_get_default          lv_disp_get_default
#define lv_display_set_theme            lv_disp_set_theme
#define lv_button_create                lv_btn_create
#define lv_image_create                 lv_img_create
#define lv_image_set_src                lv_img_set_src
#define lv_image_set_scale              lv_img_set_zoom
#define lv_image_set_antialias          lv_img_set_antialias
#define lv_screen_active                lv_scr_act
#define lv_screen_load                  lv_scr_load
#define lv_obj_delete                   lv_obj_del
#define lv_obj_remove_state             lv_obj_clear_state
#define lv_event_get_target_obj         lv_event_get_target
#define lv_table_set_column_count       lv_table_set_col_cnt
#define lv_table_set_column_width       lv_table_set_col_width
#define lv_table_set_row_count          lv_table_set_row_cnt
#define LV_LABEL_LONG_MODE_DOTS         LV_LABEL_LONG_DOT

static inline void lv_obj_set_hidden(lv_obj_t *obj, bool hidden)
{
    if (hidden)
    {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

static inline void lv_obj_set_scrollable(lv_obj_t *obj, bool scrollable)
{
    if (scrollable)
    {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    }
    else
    {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    }
}

static inline void lv_obj_set_state(lv_obj_t *obj, lv_state_t state, bool enabled)
{
    if (enabled)
    {
        lv_obj_add_state(obj, state);
    }
    else
    {
        lv_obj_clear_state(obj, state);
    }
}

#elif LVGL_VERSION_MAJOR == 9

typedef lv_display_t lv_port_flush_driver_t;
typedef uint8_t lv_port_pixel_t;
typedef lv_indev_t lv_port_indev_driver_t;

#define lv_port_flush_ready             lv_display_flush_ready
#define lv_port_flush_is_last           lv_display_flush_is_last

#else
#error "The Gino LVGL port supports LVGL 8.x and 9.x"
#endif

#endif /* GINO_LVGL_COMPAT_H */
