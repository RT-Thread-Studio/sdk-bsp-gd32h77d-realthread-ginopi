/*!
    \file    screen.c
*/

/*
    Copyright (c) 2026, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include <string.h>

#include "ui_objects.h"
#include "ui_init.h"
#include "screen.h"
#include "screen_event.h"


/* lv_scr_load_anim(auto_del = true) destroys the previous screen, but ui_manager keeps
 * the cached pointers. Clear them on delete so they never dangle and the screen can be
 * re-created on demand. */
static void screen_deleted_cb(lv_event_t *e)
{
    ui_manager_t *ui = (ui_manager_t *)lv_event_get_user_data(e);

    memset(screen_get(ui), 0, sizeof(screen_t));
}




void screen_create(ui_manager_t *ui)
{
    screen_t *scr = screen_get(ui);

    if (scr->obj) {
        screen_update_current_language();
        return;
    }

    /* Init scr->obj */
    scr->obj = lv_obj_create(NULL);
    lv_obj_add_event_cb(scr->obj, screen_deleted_cb, LV_EVENT_DELETE, ui);
    lv_obj_set_scrollbar_mode(scr->obj, LV_SCROLLBAR_MODE_OFF);

    /* Set style of scr->obj */
    lv_obj_set_style_bg_color(scr->obj, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* No widgets on this screen */


    screen_register_events(ui);
}

void screen_update_language(lang_type_t lang)
{
    screen_t *scr = screen_get(&ui_manager);
    if (!scr->obj)
        return;
    aic_set_language(lang);
    (void)scr;
}

void screen_update_current_language(void)
{
    screen_update_language(aic_get_language());
}
