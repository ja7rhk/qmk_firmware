// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include "nicola.h" // NICOLA親指シフト
#include <timer.h>

// IMEを監視する"observe_ime"を使用する場合、Num Lockでnicola on/offする。
// キーボード単体でnicola on/offを制御する場合はコメントアウトする。
#define USE_OBSERVE_IME

enum keymap_layers {
    _QWERTY,
    _NICOLA,
    _FUNC
  };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
    * │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ @ │Ctl│pUp│pDn│PSc│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Cap│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ : │Ent│Del│Hom│Ins│
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │F7 │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │Bsp│Esc│   │ ↑ │   │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Sft|   │ ← | → │ ↓ │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │Mo1│   │Tab│   │Loy│   │   │Roy|   |   |Spc│   │   |   │   │   │
    * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
    * │   │   │   │   │   │Muh│Hen│   |   |   │   │   │   |   │Ent│   │
    * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
    */

   [_QWERTY] = LAYOUT(
       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     JP_MINS,  JP_AT,    KC_RCTL,   KC_PGUP,  KC_PGDN,  KC_PSCR,
       KC_LNG2,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     JP_COLN,  KC_ENT,    KC_DEL,   KC_HOME,  KC_INS,
       JP_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_BSPC,  KC_ESC,              KC_UP,
       KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                       KC_LEFT,  KC_RIGHT, KC_DOWN,
       MO(_FUNC),          KC_TAB,             KC_LNG1,                      KC_SPC,                       KC_SPC,
                                                         JP_MHEN,  JP_HENK,                                                                         KC_ENT
   ),

   [_NICOLA] = LAYOUT(
       NG_1,     NG_2,     NG_3,     NG_4,     NG_5,     NG_6,     NG_7,     NG_8,     NG_9,     NG_0,     NG_MINS,  NG_AT,    KC_RCTL,   KC_PGUP,  KC_PGDN,  KC_PSCR,
       KC_LNG2,  NG_Q,     NG_W,     NG_E,     NG_R,     NG_T,     NG_Y,     NG_U,     NG_I,     NG_O,     NG_P,     NG_COLN,  KC_ENT,    KC_DEL,   KC_HOME,  KC_INS,
       KC_F7,    NG_A,     NG_S,     NG_D,     NG_F,     NG_G,     NG_H,     NG_J,     NG_K,     NG_L,     NG_SCLN,  KC_BSPC,  KC_ESC,              KC_UP,
       KC_LSFT,  NG_Z,     NG_X,     NG_C,     NG_V,     NG_B,     NG_N,     NG_M,     NG_COMM,  NG_DOT,   NG_SLSH,                       KC_LEFT,  KC_RIGHT, KC_DOWN,
       MO(_FUNC),          KC_TAB,             NG_SHFTL,                     NG_SHFTR,                     KC_SPC,
                                                         JP_MHEN,  JP_HENK,                                                                         KC_ENT
   ),

   [_FUNC] = LAYOUT(
       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   JP_CIRC,  JP_YEN,   _______,   _______,  _______,  _______,
       _______,  KC_F11,   KC_F12,   _______,  _______,  _______,  _______,  KC_PSCR,  _______,  _______,  _______,  JP_LBRC,  _______,   _______,  _______,  _______,
       _______,  _______, LCTL(KC_S),  _______,  _______,  _______, _______, _______,  _______,  _______,  JP_RBRC,  _______,  _______,             _______,
       _______,  _______, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______, _______, _______, _______, JP_BSLS,                       _______,  _______,  _______,
       _______,            KC_LALT,            _______,                      _______,                      _______,
                                                         _______,  _______,                                                                         _______
   )
};

void matrix_init_user(void) {
    // NICOLA親指シフト
    set_nicola(_NICOLA);
    // NICOLA親指シフト
}

// Initialize the 13th LED
void keyboard_post_init_user(void) {
    nicola_off();
}

static bool is_numlock = false;     // NumLockがオンかオフか
static bool is_capslock = false;    // CapsLockがオンかオフか

// This functions will be called when one of those 5 LEDs changes state.
// Num Lock, Caps Lock, Scroll Lock, Compose, Kan
bool led_update_kb(led_t led_state) {

    bool res = led_update_user(led_state);
    if(res) {
        #ifdef USE_OBSERVE_IME
        if (led_state.num_lock != is_numlock) {
            if (led_state.num_lock)
            {
                nicola_on();
                gpio_write_pin(USER_LED, 0);
            }
			else
            {
                nicola_off();
                gpio_write_pin(USER_LED, 1);
            }
        }
        #endif
        is_numlock = led_state.num_lock;
        is_capslock = led_state.caps_lock;
    }
    return res;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        // 英数キー(Caps Lock)で nicola mode オフ
        case KC_LNG2:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG2));
            #ifndef USE_OBSERVE_IME
                nicola_off();
            #endif
            }
            return false;
        // 英数モードのとき左親指キーで nicola mode オン
        case KC_LNG1:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG1));
            #ifndef USE_OBSERVE_IME
                nicola_on();
            #endif
            }
            return false;
    }

    // NICOLA親指シフト
    bool a = true;
    if (nicola_state()) {
        nicola_mode(keycode, record);
        a = process_nicola(keycode, record);
    }
    if (a == false) return false;

    return true;
}

// This function gets called at every matrix scan.
void matrix_scan_user(void) {

	uint32_t now = timer_read32();
	timer_tick(now);	// drive nicola state-machine.
}

