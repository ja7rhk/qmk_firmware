/* Copyright 2018-2020 eswai <@eswai>
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

  OSで日本語キーボード(logical bit pairing)と設定/認識されているキーボードで、
  USキーキャップの文字、記号(typewriter pairing)を正しく出力する。

  例: Shift + 2 で @ を入力する

  変換された文字はキーリピートが無効です。

*/

/*
 * Modified to use with OASYS Lite F
 * ** koseki(2026.1.22)
 */

#include QMK_KEYBOARD_H
#include "nicola.h" // NICOLA親指シフト
#include "keymap_us.h"

const uint16_t oas2ansi[][2] = {
    {KC_AT,   KC_DQUO},
    {KC_CIRC, KC_AMPR},
    {KC_AMPR, KC_QUOT},
    {KC_ASTR, KC_LPRN},
    {KC_LPRN, KC_RPRN},
    {KC_RPRN, KC_QUOT},
    {KC_UNDS, KC_EQUAL},
    {KC_EQUAL, KC_AT},
    {KC_PLUS,  KC_DQUO},
    {KC_LBRC, KC_COLN},
    {KC_LCBR, KC_ASTR},
    {KC_COLN, KC_PLUS},
    {NG_LBRC, KC_UNDS}
};

bool twpair_on_ansi(uint16_t keycode, keyrecord_t *record, bool fn) {
    if (!record->event.pressed)
    	return true;

    uint16_t skeycode;
    bool lshifted = keyboard_report->mods & MOD_BIT(KC_LSFT);
    bool rshifted = keyboard_report->mods & MOD_BIT(KC_RSFT);
    bool shifted = lshifted | rshifted;

    if (shifted) {
        skeycode = QK_LSFT | keycode;
    } else {
        skeycode = keycode;
    }

    for (int i = 0; i < sizeof(oas2ansi) / sizeof(oas2ansi[0]); i++) {
        if (oas2ansi[i][0] == skeycode) {
        unregister_code(KC_LSFT);
        unregister_code(KC_RSFT);
        if ((oas2ansi[i][1] & QK_LSFT) == QK_LSFT || (oas2ansi[i][1] & QK_RSFT) == QK_RSFT) {
            register_code(KC_LSFT);
            tap_code(oas2ansi[i][1]);
            unregister_code(KC_LSFT);
        } else {
            tap_code(oas2ansi[i][1]);
        }
        if (lshifted) register_code(KC_LSFT);
        if (rshifted) register_code(KC_RSFT);
        return false;
        }
    }
    return true;
}
