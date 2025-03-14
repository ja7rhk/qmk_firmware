//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "nicola.h" // NICOLA親指シフト
#include <timer.h>
#include "rgb_config.h" // RGB LEDの定義

// IMEを監視する"observe_ime"を使用する場合、Num Lockでnicola on/offする。
// キーボード単体でnicola on/offを制御する場合はコメントアウトする。
#define USE_OBSERVE_IME

enum layer_names {
    _QWERTY = 0,
// NICOLA親指シフト入力レイヤー
    _NICOLA,
// FUNCTION
    _FUNC
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] =  LAYOUT_all(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,    KC_F6,     KC_F7,     KC_F8,      KC_F9,     KC_F10,   KC_F11,   KC_F12,   LCTL(KC_0),
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,        KC_6,     KC_7,      KC_8,      KC_9,       KC_0,      KC_MINS,  KC_EQL,   KC_BSPC,  KC_PSCR,  KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,     KC_U,      KC_I,      KC_O,       KC_P,      KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_LNG2,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,        KC_H,     KC_J,      KC_K,      KC_L,       KC_SCLN,   KC_QUOT,            KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,        KC_N,     KC_M,      KC_COMM,   KC_DOT,     KC_SLSH,                       KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,            KC_LNG1,  KC_SPC,                KC_SPC,               MO(_FUNC),  KC_RALT,   KC_APP,             KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

     [_NICOLA] =  LAYOUT_all(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,       KC_F5,    KC_F6,     KC_F7,     KC_F8,      KC_F9,     KC_F10,   KC_F11,   KC_F12,   LCTL(KC_0),
        KC_GRV,   NG_1,     NG_2,     NG_3,     NG_4,     NG_5,        NG_6,     NG_7,      NG_8,      NG_9,       NG_0,      NG_MINS,  NG_EQL,   KC_BSPC,  KC_PSCR,  KC_HOME,  KC_PGUP,
        KC_TAB,   NG_Q,     NG_W,     NG_E,     NG_R,     NG_T,        NG_Y,     NG_U,      NG_I,      NG_O,       NG_P,      NG_LBRC,  NG_RBRC,  NG_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_LNG2,  NG_A,     NG_S,     NG_D,     NG_F,     NG_G,        NG_H,     NG_J,      NG_K,      NG_L,       NG_SCLN,   KC_BSPC,            KC_ENT,
        KC_LSFT,  NG_Z,     NG_X,     NG_C,     NG_V,     NG_B,        NG_N,     NG_M,      NG_COMM,   NG_DOT,     NG_SLSH,                       KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,            NG_SHFTL, _______,               NG_SHFTR,             MO(_FUNC),  KC_RALT,   KC_APP,             KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_FUNC] =  LAYOUT_all(
        _______,            KC_F13,   KC_F14,   KC_F15,   KC_F16,      _______,   _______,   _______,  _______,    _______,   _______,  _______,  _______,  _______,
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,       KC_F6,     KC_F7,    KC_F8,     KC_F9,      KC_F10,    KC_F11,   KC_F12,   KC_DEL,   KC_INS,   _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   KC_PSCR,   _______,  _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,     _______,   _______,   _______,  _______,    _______,                       _______,            _______,
        _______,  _______,  _______,            KC_DEL,   _______,                KC_ESC,              _______,    _______,   _______,            _______,  _______,  _______,  _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
// Zoom-Up と Zoom-Down を割り当てる場合
    [_QWERTY] = { ENCODER_CCW_CW((LCTL(KC_MINUS)), (LCTL(KC_EQUAL))) },
    [_NICOLA] = { ENCODER_CCW_CW((LCTL(KC_MINUS)), (LCTL(KC_EQUAL))) },
    [_FUNC] =   { ENCODER_CCW_CW(_______, _______) }
};
#endif

#if defined(DIP_SWITCH_MAP_ENABLE)
const uint16_t PROGMEM dip_switch_map[NUM_DIP_SWITCHES][NUM_DIP_STATES] = {
    DIP_SWITCH_OFF_ON(DF(0), DF(1)),
};
#endif

void matrix_init_user(void) {
    // NICOLA親指シフト
    set_nicola(_NICOLA);
    // NICOLA親指シフト
}

// Initialize the 13th LED
void keyboard_post_init_user(void) {
    nicola_off();
}

static bool is_capslock = false;    // CapsLockがオンかオフか
#ifdef USE_OBSERVE_IME
static bool is_numlock = false;     // NumLockがオンかオフか
// This functions will be called when one of those 5 LEDs changes state.
// Num Lock, Caps Lock, Scroll Lock, Compose, Kan
bool led_update_kb(led_t led_state) {

    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.num_lock != is_numlock) {
            if (led_state.num_lock)
                nicola_on();
            else
                nicola_off();
            is_numlock = led_state.num_lock;
        }
        is_capslock = led_state.caps_lock;
    }
    return res;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        // 英数キー(Caps Lock)で nicola mode オフ
        //case KC_CAPS_LOCK:
        //case KC_F16:
        case KC_LNG2:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG2));
                //send_string(SS_LSFT(SS_TAP(X_CAPS_LOCK)));
            #ifndef USE_OBSERVE_IME
                nicola_off();
            #endif
            }
            return false;
        // 英数モードのとき左親指キーで nicola mode オン
        //case KC_F14:
        case KC_LNG1:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG1));
                //send_string(SS_TAP(X_F14));
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

// This function switches the LED pattern for each layer.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    //rgb_matrix_set_color_all(0, 0, 0);
    for (uint8_t i = led_min; i < led_max; i++)
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            if (is_capslock) {
                RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 255); // CapsLock : on
            } else {
                RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 0); // CapsLock : off
            }
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_CENTER_INDEX, 0, 63, 0); // nicola : off
            break;
        case _NICOLA:
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_LEFT_INDEX, 255, 255, 0); // nicola : on
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_CENTER_INDEX, 127, 127, 0); // nicola : on
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_RIGHT_INDEX, 255, 255, 0); // nicola : on
            break;
        case _FUNC:
            if (is_capslock) {
                RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 255); // CapsLock : on
            } else {
                RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 0); // CapsLock : off
            }
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_LEFT_INDEX, 255, 0, 0); // Left Oyayubi key : DEL
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_RIGHT_INDEX, 0, 0, 255); // nicola : on
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_PS_INDEX, 0, 0, 255); // function key : PS
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_BS_INDEX, 255, 0, 0); // function key : BS -> DEL
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_INS_INDEX, 0, 0, 255); // function key : PS ->INS
            break;
    }
    return false;
}


