#pragma once
/* Copyright 2018-2019 eswai <@eswai>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * Modified to use with Chibios on STM32 platform.
 * ** koseki(2024.4.25)
 */

void nicola_type(void);
void nicola_clear(void);

void nicola_mode(uint16_t, keyrecord_t *);

void nicola_on(void);
void nicola_off(void);
bool nicola_state(void);

bool process_nicola(uint16_t, keyrecord_t *);
void set_nicola(uint8_t);

//**koseki(2024.4.25)
void timer_tick(uint32_t);
//**

typedef enum nicola_keycodes {
    NG_TOP = SAFE_RANGE,
    NG_M_TOP = NG_TOP,
    NG_1 = NG_TOP,
    NG_2,
    NG_3,
    NG_4,
    NG_5,
    NG_6,
    NG_7,
    NG_8,
    NG_9,
    NG_0,
    NG_MINS,
    NG_EQL,
    NG_BSLS,

    NG_Q,
    NG_W,
    NG_E,
    NG_R,
    NG_T,
    NG_Y,
    NG_U,
    NG_I,
    NG_O,
    NG_P,
    NG_LBRC,
    NG_RBRC,

    NG_A,
    NG_S,
    NG_D,
    NG_F,
    NG_G,
    NG_H,
    NG_J,
    NG_K,
    NG_L,
    NG_SCLN,
    NG_QUOT,

    NG_Z,
    NG_X,
    NG_C,
    NG_V,
    NG_B,
    NG_N,
    NG_M,
    NG_COMM,
    NG_DOT,
    NG_SLSH,

    NG_M_BOTTOM = NG_SLSH,

    NG_SHFTL,
    NG_SHFTR,

    NG_BOTTOM = NG_SHFTR

} NGKEYS;




