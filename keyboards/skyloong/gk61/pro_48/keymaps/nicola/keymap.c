// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "nicola.h" // NICOLA親指シフト
#include <timer.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keymap_layers {
  _QWERTY = 0,
// NICOLA親指シフト
  _NICOLA, // NICOLA親指シフト入力レイヤー
// NICOLA親指シフト
  _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E | R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   |Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │   |Sft|   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│GUI│Alt│   │Spc│Mut│   │   |Spc|Alt│App│Ctl│   │Mo1|
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
	/*
    [0] = LAYOUT_all(
         KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,       KC_8,     KC_9,        KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,
         KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,       KC_I,     KC_O,        KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,       KC_K,     KC_L,     KC_SCLN,     KC_QUOT,              KC_ENT,
        KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,   KC_DOT,     KC_SLSH,               KC_RSFT,
        KC_LCTL,  KC_LGUI,  KC_LALT,             KC_SPC,   KC_SPC,     KC_MUTE,               KC_SPC,  KC_RALT,      KC_APP,     KC_RCTL,               MO(1)
    ),

    [1] = LAYOUT_all(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,
        _______,  RGB_TOG,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,            _______,  _______,     _______,            _______,  _______,  _______,  _______,            _______
    )
	*/
    [_QWERTY] = LAYOUT_all(
        KC_ESC,       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,    KC_8,     KC_9,      KC_0,      KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,       KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,    KC_I,     KC_O,      KC_P,      KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_CAPS_LOCK, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,    KC_K,     KC_L,      KC_SCLN,   KC_QUOT,            KC_ENT,
        KC_LSFT,      KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,    KC_COMM,  KC_DOT,    KC_SLSH,             KC_RSFT,
        KC_LCTL,      KC_LGUI,  KC_LALT,            KC_F14,   KC_SPC,      KC_F15,            KC_SPC,   MO(_FUNC), KC_RALT,   KC_APP,             KC_RCTL
    ),

    [_NICOLA] = LAYOUT_all(
        KC_ESC,       NG_1,     NG_2,     NG_3,     NG_4,     NG_5,        NG_6,     NG_7,    NG_8,     KC_9,       NG_0,     NG_MINS,  NG_EQL,   KC_BSPC,
        KC_TAB,       NG_Q,     NG_W,     NG_E,     NG_R,     NG_T,        NG_Y,     NG_U,    NG_I,     NG_O,       NG_P,     NG_LBRC,  NG_RBRC,  NG_BSLS,
        KC_CAPS_LOCK, NG_A,     NG_S,     NG_D,     NG_F,     NG_G,        NG_H,     NG_J,    NG_K,     NG_L,       NG_SCLN,  KC_BSPC,            KC_ENT,
        KC_LSFT,      NG_Z,     NG_X,     NG_C,     NG_V,     NG_B,        NG_N,     NG_M,    NG_COMM,  NG_DOT,     NG_SLSH,            KC_RSFT,
        KC_LCTL,      KC_LGUI,  KC_LALT,            NG_SHFTL, KC_SPC,      KC_F15,            NG_SHFTR, MO(_FUNC),  KC_RALT,  KC_APP,             KC_RCTL
    ),

    [_FUNC] = LAYOUT_all(
        KC_GRV,       KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,      KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12,   KC_DEL ,
        _______,      RGB_TOG,  _______,  KC_UP  ,  _______,   _______,    _______,  KC_PSCR,  _______,  _______,   _______,  _______,  _______,  _______,
        _______,      _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  _______,    _______,  _______,  _______,  KC_PGUP,   _______,  _______,            _______,
        _______,      _______,  _______,  _______,  _______,   _______,    _______,  _______,  _______,  KC_PGDN,   _______,            _______,
        _______,      _______,  _______,            KC_TAB,    _______,    _______,            KC_F15,   _______,   _______,  _______,            _______
    )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
	/*
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) }
	*/
    [_QWERTY] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [_NICOLA] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [_FUNC] =   { ENCODER_CCW_CW(KC_DOWN, KC_UP) }
};
#endif

void matrix_init_user(void) {
  // NICOLA親指シフト
  set_nicola(_NICOLA);
  // NICOLA親指シフト
}

/*
// Initialize the 13th LED
void keyboard_post_init_user(void) {
    for(int i=0; i<RGBLED_NUM; ++i) {
        rgblight_setrgb_at(0, 0, 0, i);
    }
    rgblight_setrgb_at(170,255,40, RGBLED_NUM-1); // the last LED = BLUE (NICOLA off)
    nicola_off();
}
*/

// IMEを監視する"observe_ime"を使用する場合、Num Lockでnicola on/offする。
// キーボード単体でnicola on/offを制御する場合はコメントアウトする。
#define USE_OBSERVE_IME

// This functions will be called when one of those 5 LEDs changes state.
// Num Lock, Caps Lock, Scroll Lock, Compose, Kan
#ifdef USE_OBSERVE_IME
bool led_update_kb(led_t led_state) {

    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.num_lock)
            nicola_on();
        else
            nicola_off();
    }
    return res;
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    // 英数キー(Caps Lock)、nicola mode オフ
    case KC_CAPS_LOCK:
        if (record->event.pressed) {
            //send_string(SS_TAP(X_CAPS_LOCK)); // Win MS-IME
            send_string(SS_LSFT(SS_TAP(X_CAPS_LOCK))); // Win MS-IME
        #ifndef USE_OBSERVE_IME
            nicola_off();
        #endif
        }
        return false;
        break;
    // 英数モードのとき左親指キー(F14)で、nicola mode オン
    case KC_F14:
        if (record->event.pressed) {
            send_string(SS_TAP(X_F14));
        #ifndef USE_OBSERVE_IME
            nicola_on();
        #endif
        }
        return false;
        break;
    // 右親指キー(空白)
    case KC_SPC:
      if (record->event.pressed) {
        /* ここでは何もしない */
      }
      break;
  }

  // NICOLA親指シフト
  bool a = true;
  if (nicola_state()) {
    nicola_mode(keycode, record);
    a = process_nicola(keycode, record);
  }
  if (a == false) return false;
  // NICOLA親指シフト

//   bool continue_process = process_jtu(keycode, record);
//   if (continue_process == false) {
//     return false;
//   }

  return true;
}

// This function gets called at every matrix scan.
void matrix_scan_user(void) {

	uint32_t now = timer_read32();
	timer_tick(now);	// drive nicola state-machine.
}
