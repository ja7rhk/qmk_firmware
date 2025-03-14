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
 * introduced NICOLA state machine
 * (C) 2020 Sadao Ikebe @bonyarou
 */
/*
 * Modified to use with Chibios on STM32 platform.
 * ** koseki(2024.4.25)
 */

#include QMK_KEYBOARD_H
#include "nicola.h"
//#include "key_duration.h"
#include <timer.h>

static bool is_nicola = false;      // 親指シフトがオンかオフか
static uint8_t nicola_layer = 0;    // レイヤー番号
static uint8_t n_modifier = 0;      // 押しているmodifierキーの数

//#define TIMEOUT_THRESHOLD (150)         // 文字キー長押しの場合の自動送出
#define TIMEOUT_THRESHOLD (200)         // 文字キー長押しの場合の自動送出
#define TIMEOUT_OYA_THRESHOLD (250)     // 親指キー長押しの場合(Space → F15:変換キー)
//**koseki(2024.5.16)
//#define OVERLAP_THRESHOLD (20)
#define OVERLAP_THRESHOLD (80)
//**
typedef enum {
  NICOLA_STATE_S1_INIT,
  NICOLA_STATE_S2_M,
  NICOLA_STATE_S3_O,
  NICOLA_STATE_S4_MO,
  NICOLA_STATE_S5_OM
} nicola_state_t;

static nicola_state_t nicola_int_state = NICOLA_STATE_S1_INIT;
static int nicola_m_key;
static int nicola_o_key;
// previous key record
static int previous_m_key;
static uint32_t nicola_m_time;
static uint32_t nicola_o_time;

static int key_process_guard = 0;
void keypress_timer_expired(void);

//**koseki(2024.4.25)
static uint32_t event_time = 0;

void timer_tick(uint32_t now) {
	if (event_time != 0 && (now > event_time)) {
		event_time = 0;
		keypress_timer_expired();
	}
}
//**

// 親指シフトのレイヤー、シフトキーを設定
void set_nicola(uint8_t layer) {
  nicola_layer = layer;
#ifdef TIMEOUT_INTERRUPT
  //keypress_timer_init(keypress_timer_expired);
#endif
}

// 親指シフトをオンオフ
void nicola_on(void) {
  is_nicola = true;
  nicola_clear();
  layer_on(nicola_layer);

//   tap_code(KC_LANG1); // Mac
//   tap_code(KC_HENK); // Win
}

void nicola_off(void) {
  is_nicola = false;
  nicola_clear();
  layer_off(nicola_layer);

//   tap_code(KC_LANG2); // Mac
//   tap_code(KC_MHEN); // Win
}

// 親指シフトの状態
bool nicola_state(void) {
  return is_nicola;
}

// バッファをクリアする
void nicola_clear(void) {
    nicola_int_state = NICOLA_STATE_S1_INIT;
    key_process_guard = 0;
    //**koseki(2024.4.27)
    n_modifier = 0;
}

// 入力モードか修飾モードかを確認する
void nicola_mode(uint16_t keycode, keyrecord_t *record) {
    if (!is_nicola) return;

    // modifierが押されたらレイヤーをオフ
    switch (keycode) {
        case KC_LCTL:
        case KC_LSFT:
        case KC_LALT:
        case KC_LGUI:
        case KC_RCTL:
        case KC_RSFT:
        case KC_RALT:
        case KC_RGUI:
            if (record->event.pressed) {
                if(n_modifier == 0)
                    layer_off(nicola_layer);
                if (n_modifier < 3)
                    n_modifier++;
            } else {
                if (n_modifier > 0)
                    n_modifier--;
                if (n_modifier == 0) {
                    layer_on(nicola_layer);
                }
            }
            break;
    }
}

//#define SS_ALNUM(x) SS_TAP(X_CAPSLOCK) x SS_TAP(X_CAPSLOCK)

void nicola_m_type(void) {
    //if (n_modifier == 0) {
    if (n_modifier == 0) {
        switch(nicola_m_key) {
            case NG_1   : send_string("1" ); break;     // １
            case NG_2   : send_string("2" ); break;     // ２
            case NG_3   : send_string("3" ); break;     // ３
            case NG_4   : send_string("4" ); break;     // ４
            case NG_5   : send_string("5" ); break;     // ５
            case NG_6   : send_string("6" ); break;     // ６
            case NG_7   : send_string("7" ); break;     // ７
            case NG_8   : send_string("8" ); break;     // ８
            case NG_9   : send_string("9" ); break;     // ９
            case NG_0   : send_string("0" ); break;     // ０
            case NG_MINS: send_string("-" ); break;     // ――
            case NG_EQL : send_string("=" ); break;     // ＝

            case NG_Q   : send_string("." ); break;     //ピリオドと句点は区別できない
            case NG_W   : send_string("ka"); break;
            case NG_E   : send_string("ta"); break;
            case NG_R   : send_string("ko"); break;
            case NG_T   : send_string("sa"); break;
            case NG_Y   : send_string("ra"); break;
            case NG_U   : send_string("ti"); break;
            case NG_I   : send_string("ku"); break;
            case NG_O   : send_string("tu"); break;
            case NG_P   : send_string(",");  break;     // カンマと読点も区別できない
            case NG_LBRC: nicola_marked_m_type(); break;
            case NG_RBRC: nicola_p_marked_m_type(); break;
            case NG_BSLS: send_string("\\"); break;     // 円記号"\"を送る

            case NG_A   : send_string("u" ); break;
            case NG_S   : send_string("si"); break;
            case NG_D   : send_string("te"); break;
            case NG_F   : send_string("ke"); break;
            case NG_G   : send_string("se"); break;
            case NG_H   : send_string("ha"); break;
            case NG_J   : send_string("to"); break;
            case NG_K   : send_string("ki"); break;
            case NG_L   : send_string("i" ); break;
            case NG_SCLN: send_string("nn"); break;
            case NG_QUOT:                  ; break;

            case NG_Z   : send_string("." ); break;     //ピリオドと句点は区別できない
            case NG_X   : send_string("hi"); break;
            case NG_C   : send_string("su"); break;
            case NG_V   : send_string("hu"); break;
            case NG_B   : send_string("he"); break;
            case NG_N   : send_string("me"); break;
            case NG_M   : send_string("so"); break;
            case NG_COMM: send_string("ne"); break;
            case NG_DOT : send_string("ho"); break;
            case NG_SLSH: send_string("/" ); break;
        }
        // previous key record
        previous_m_key = nicola_m_key;
    }
}

void nicola_o_type(void) {
    if(nicola_o_key == NG_SHFTL) {
        send_string(SS_TAP(X_F14));         // 左親指キーはWin MS-IME で無変換キー
    } else if(nicola_o_key == NG_SHFTR) {
        send_string(SS_TAP(X_SPACE));       // 右親指キーは単独打鍵で空白キー
    }
    // previous key clear
    previous_m_key = KC_NO;
}

void nicola_o_TO_type(void) {
    if(nicola_o_key == NG_SHFTL) {
        send_string(SS_TAP(X_TAB));         // タイムアウト時はTAB(変換候補選択)キー
    } else if(nicola_o_key == NG_SHFTR) {
        send_string(SS_TAP(X_ENTER));         // タイムアウト時はENTERキー
        //send_string(SS_TAP(X_F14));         // タイムアウト時はF14(無変換)キー
        //send_string(SS_TAP(X_F15));         // タイムアウト時はF15(変換)キー
    }
    // previous key clear
    previous_m_key = KC_NO;
}

void nicola_om_type(void) {
    if(nicola_o_key == NG_SHFTR) {          // シングル親指シフトは右親指キーとする
        switch(nicola_m_key) {
        //  case NG_1   : send_string("?"); break;      // ？
        //  case NG_2   : send_string("/"); break;      // ・
        //  case NG_3   : send_string("~"); break;      // ～
            case NG_1   : send_string("?"); send_string(SS_TAP(X_F9)); break;      // ？
            case NG_2   : send_string("/"); send_string(SS_TAP(X_F9)); break;      // ／
            case NG_3   : send_string("~"); send_string(SS_TAP(X_F9)); break;      // ～
            case NG_4   : send_string("["); break;      // 「
            case NG_5   : send_string("]"); break;      // 」
            case NG_6   : send_string("{"); break;      // 『
            case NG_7   : send_string("}"); break;      // 』
            case NG_8   : send_string("*"); break;      // ＊
            case NG_9   : send_string("("); break;      // （
            case NG_0   : send_string(")"); break;      // ）
            case NG_MINS: send_string("_"); break;      // ＿
            case NG_EQL : send_string("+"); break;      // ＋

            case NG_Q   : send_string("xa"); break;
            case NG_W   : send_string("e" ); break;
            case NG_E   : send_string("ri"); break;
            case NG_R   : send_string("xya");break;
            case NG_T   : send_string("re"); break;
            case NG_Y   : send_string("yo"); break;
            case NG_U   : send_string("ni"); break;
            case NG_I   : send_string("ru"); break;
            case NG_O   : send_string("ma"); break;
            case NG_P   : send_string("xe"); break;
            case NG_LBRC:                  ; break;
            case NG_RBRC:                  ; break;
            case NG_BSLS: send_string("|" ); break;

            case NG_A   : send_string("wo"); break;
            case NG_S   : send_string("a" ); break;
            case NG_D   : send_string("na"); break;
            case NG_F   : send_string("xyu");break;
            case NG_G   : send_string("mo"); break;
            case NG_H   : send_string("mi"); break;
            case NG_J   : send_string("o" ); break;
            case NG_K   : send_string("no"); break;
            case NG_L   : send_string("xyo");break;
            case NG_SCLN: send_string("xtu");break;
            case NG_QUOT:                    break;

            case NG_Z   : send_string("xu"); break;
            case NG_X   : send_string("-" ); break;
            case NG_C   : send_string("ro"); break;
            case NG_V   : send_string("ya"); break;
            case NG_B   : send_string("xi"); break;
            case NG_N   : send_string("nu"); break;
            case NG_M   : send_string("yu"); break;
            case NG_COMM: send_string("mu"); break;
            case NG_DOT : send_string("wa"); break;
            case NG_SLSH: send_string("xo"); break;
        }
        // previous key clear
        previous_m_key = KC_NO;
    }
}

void nicola_marked_m_type(void) {
    // 後退キーを送出、濁音・半濁音に該当しないキーはただの後退になる
    if(NG_M_TOP <= previous_m_key && previous_m_key <= NG_M_BOTTOM)
        send_string(SS_TAP(X_BACKSPACE));
    else
        return;
    switch(previous_m_key) {
        case NG_W   : send_string("ga"); break;
        case NG_E   : send_string("da"); break;
        case NG_R   : send_string("go"); break;
        case NG_T   : send_string("za"); break;
        case NG_U   : send_string("di"); break;
        case NG_I   : send_string("gu"); break;
        case NG_O   : send_string("du"); break;

        case NG_A   : send_string("vu"); break;
        case NG_S   : send_string("zi"); break;
        case NG_D   : send_string("de"); break;
        case NG_F   : send_string("ge"); break;
        case NG_G   : send_string("ze"); break;
        case NG_H   : send_string("ba"); break;
        case NG_J   : send_string("do"); break;
        case NG_K   : send_string("gi"); break;

        case NG_X   : send_string("bi"); break;
        case NG_C   : send_string("zu"); break;
        case NG_V   : send_string("bu"); break;
        case NG_B   : send_string("be"); break;
        case NG_M   : send_string("zo"); break;
        case NG_DOT : send_string("bo"); break;
    }
        // previous key clear
        previous_m_key = KC_NO;
}

void nicola_p_marked_m_type(void) {
    // 後退キーを送出、濁音・半濁音に該当しないキーはただの後退になる
    if(NG_M_TOP <= previous_m_key && previous_m_key <= NG_M_BOTTOM)
        send_string(SS_TAP(X_BACKSPACE));
    else
        return;
    switch(previous_m_key) {
        case NG_H   : send_string("pa"); break;
        case NG_X   : send_string("pi"); break;
        case NG_V   : send_string("pu"); break;
        case NG_B   : send_string("pe"); break;
        case NG_DOT : send_string("po"); break;
    }
        // previous key clear
        previous_m_key = KC_NO;
}

// 親指シフトの入力処理
bool process_nicola(uint16_t keycode, keyrecord_t *record) {

  if (n_modifier > 0) return true;

  key_process_guard = 1; // timeout entrance guard
  bool cont_process = true;
  uint32_t curr_time = timer_read32();

  if (record->event.pressed) {
    if(NG_M_TOP <= keycode && keycode <= NG_M_BOTTOM) {
        // M key
        switch(nicola_int_state) {
          case NICOLA_STATE_S1_INIT:
            nicola_int_state = NICOLA_STATE_S2_M;
            break;
          case NICOLA_STATE_S2_M:
            nicola_m_type();
            break;
          case NICOLA_STATE_S3_O:
            // combo => S5
            nicola_int_state = NICOLA_STATE_S5_OM;
            break;
          case NICOLA_STATE_S4_MO:
            // combo => three key judge【処理A】
            uint32_t t1 = nicola_o_time - nicola_m_time;
            uint32_t t2 = curr_time - nicola_o_time;
            if(t1 >= t2) {
              // the leading M key is single, the O key in between is combo with current key
              nicola_m_type();
              nicola_int_state = NICOLA_STATE_S5_OM;
            } else {
              // the O key in between is combo with the leading M key
              nicola_om_type();
              nicola_int_state = NICOLA_STATE_S2_M;
            }
            break;
          case NICOLA_STATE_S5_OM:
            nicola_om_type();
            nicola_int_state = NICOLA_STATE_S2_M;
            break;
        }
        nicola_m_key = keycode;
        nicola_m_time = curr_time;
        //koseki(2024.4.25)
        event_time = curr_time + TIMEOUT_THRESHOLD;
        //**
        cont_process = false;
    } else if(keycode == NG_SHFTL || keycode == NG_SHFTR) {
    //} else if(keycode == NG_SHFTR) {    // シングル親指シフト
        // O key
        switch(nicola_int_state) {
          case NICOLA_STATE_S1_INIT:
            nicola_int_state = NICOLA_STATE_S3_O;
            break;
          case NICOLA_STATE_S2_M:
            // combo => S4
            nicola_int_state = NICOLA_STATE_S4_MO;
            break;
          case NICOLA_STATE_S3_O:
            nicola_o_type();
            break;
          case NICOLA_STATE_S4_MO:
            nicola_om_type();
            nicola_int_state = NICOLA_STATE_S3_O;
            break;
          case NICOLA_STATE_S5_OM:
            // combo => three key judge【処理B】
            uint32_t t1 = nicola_m_time - nicola_o_time;
            uint32_t t2 = curr_time - nicola_m_time;
            if(t1 >= t2) {
              // the leading O key is single, the M key in between is combo with current key
              nicola_o_type();
              nicola_int_state = NICOLA_STATE_S4_MO;
            } else {
              // the M key in between is combo with the leading O key
              nicola_om_type();
              nicola_int_state = NICOLA_STATE_S3_O;
            }
            break;
        }
        nicola_o_key = keycode;
        nicola_o_time = curr_time;
        //koseki(2024.4.25)
        event_time = curr_time + TIMEOUT_OYA_THRESHOLD;
        //**
        cont_process = false;

    } else {
        // その他のキーが押された
        switch(nicola_int_state) {
          case NICOLA_STATE_S1_INIT:
            break;
          case NICOLA_STATE_S2_M:
            nicola_m_type();
            break;
          case NICOLA_STATE_S3_O:
            nicola_o_type();
            break;
          case NICOLA_STATE_S4_MO:
            nicola_om_type();
            break;
          case NICOLA_STATE_S5_OM:
            nicola_om_type();
            break;
        }
        nicola_int_state = NICOLA_STATE_S1_INIT;
        key_process_guard = 0;
        // continue processing current key, so this path returns true
    }
  } else { // key release
    if(NG_TOP <= keycode && keycode <= NG_BOTTOM) { // key off
        switch(nicola_int_state) {
          case NICOLA_STATE_S1_INIT:
            break;
          case NICOLA_STATE_S2_M:
            if(nicola_m_key == keycode) {
              nicola_m_type();
              nicola_int_state = NICOLA_STATE_S1_INIT;
            }
            break;
          case NICOLA_STATE_S3_O:
            if(nicola_o_key == keycode) {
              nicola_o_type();
              nicola_int_state = NICOLA_STATE_S1_INIT;
            }
            break;
          case NICOLA_STATE_S4_MO:
            //【処理C】
            if(nicola_m_key == keycode) {
              // M ON --> O ON --> M OFF
              uint16_t t1 = nicola_o_time - nicola_m_time;
              uint16_t t2 = curr_time - nicola_o_time;
              if(t1>=t2 && t2 < OVERLAP_THRESHOLD) {
                // M ON --> O ON --> M OFF (M is output, but O is still open to combo)
                nicola_m_type();
                nicola_int_state = NICOLA_STATE_S3_O;
              } else {
                // M ON --> O ON --> M OFF (both M and O are output)
                nicola_om_type();
                nicola_int_state = NICOLA_STATE_S1_INIT;
              }
            }
            break;
          case NICOLA_STATE_S5_OM:
            //【処理D】
            if(nicola_o_key == keycode) {
              // O ON --> M ON --> O OFF
              uint16_t t1 = nicola_m_time - nicola_o_time;
              uint16_t t2 = curr_time - nicola_m_time;
              if(t1>=t2 && t2 < OVERLAP_THRESHOLD) {
                // O ON --> M ON --> O OFF (O is output, but M is still open to combo)
                nicola_o_type();
                nicola_int_state = NICOLA_STATE_S2_M;
              } else {
                // O ON --> M ON --> O OFF (both M and O are output)
                nicola_om_type();
                nicola_int_state = NICOLA_STATE_S1_INIT;
              }
            }
            break;
        }
        cont_process = false;
    }
  }
  key_process_guard = 0;
  return cont_process;
}

void keypress_timer_expired(void) {
    if(!key_process_guard) {
        switch(nicola_int_state) {
            case NICOLA_STATE_S1_INIT:
                break;
            case NICOLA_STATE_S2_M:
                //nicola_m_type();
                nicola_m_type();
                break;
            case NICOLA_STATE_S3_O:
                //nicola_o_type();
                nicola_o_TO_type();     // Oyayubi key Time Out
                break;
            case NICOLA_STATE_S4_MO:
                nicola_om_type();
                break;
            case NICOLA_STATE_S5_OM:
                nicola_om_type();
                break;
        }
        nicola_int_state = NICOLA_STATE_S1_INIT;
    }
}
