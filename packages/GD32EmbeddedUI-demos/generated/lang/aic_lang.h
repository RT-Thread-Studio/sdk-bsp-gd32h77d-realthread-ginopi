/*!
    \file    aic_lang.h
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

#ifndef AIC_LANG_H
#define AIC_LANG_H

#include "lvgl.h"
#include "font_list.h"

typedef enum {
    AIC_LANG_EN = 0
} lang_type_t;

#define AIC_LANG_COUNT 1

typedef struct {
    char *lan_name;
    int font_id;
    bool c_flag;
} aic_language_t;

/* Translation key enum (updated by code generator) */
/* KEY_ID_ENUM_BEGIN */
typedef enum {
    KEY_LANG_KEY_PLACEHOLDER = 0
} key_id_t;
/* KEY_ID_ENUM_END */

#define AIC_LANG_KEY_COUNT 1

void aic_set_language(lang_type_t lang);
lang_type_t aic_get_language(void);
/* Resolve a language code (e.g. "zh-CN") to its enum value; -1 when unknown. */
int aic_find_language(const char *code);
const char *aic_get_translation(key_id_t key);
const lv_font_t *aic_init_lang_font(int font_id, int font_size);
const lv_font_t *aic_get_lang_font(int font_id, int font_size, bool c_flag);
const lv_font_t *aic_get_multi_lang_font(int font_size);
const aic_language_t *get_current_lang(void);

#endif /* AIC_LANG_H */
