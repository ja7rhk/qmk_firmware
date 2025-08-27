// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum keymap_layers {
    _QWERTY,
    _FUNC
  };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
    * │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ @ │Alt│pUp│pDn│PSc│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Tab│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ : │Ent│Del│Hom│Ins│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │Bsp│Esc│   │ ↑ │   │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Sft|   │ ← | → │ ↓ │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Ctl│   │Tab│   │Loy│   │   │Roy|   |   |Mo1│   │   |   │   │   │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │   │   │   │   │   │Muh│Hen│   |   |   │   │   │   |   │Ent│   │
    * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
    */

   [_QWERTY] = LAYOUT(
       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     JP_MINS,  JP_AT,    KC_RALT,   KC_PGUP,  KC_PGDN,  KC_PSCR,
       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     JP_COLN,  KC_ENT,    KC_DEL,   KC_HOME,  KC_INS,
       KC_LNG2,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_BSPC,  KC_ESC,              KC_UP,
       KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,             KC_LEFT,  KC_RIGHT, KC_DOWN,
       KC_LCTL,            KC_TAB,             KC_LNG1,                      KC_SPC,                       MO(_FUNC),
                                                         _______,  _______,                                                                         KC_ENT
   ),

   [_FUNC] = LAYOUT(
       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   JP_CIRC,  JP_YEN,   KC_RALT,   _______,  _______,  _______,
       _______,  KC_F11,   KC_F12,   _______,  _______,  _______,  _______,  KC_PSCR,  _______,  _______,  _______,  JP_LBRC,  _______,   _______,  _______,  _______,
       JP_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  JP_RBRC,  _______,  _______,             _______,
       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  JP_BSLS,  _______,             _______,  _______,  _______,
       KC_LGUI,            KC_LALT,            _______,                      _______,                      _______,
                                                         _______,  _______,                                                                         _______
   )
};

