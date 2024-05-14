// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define IS31FL3743A_I2C_ADDRESS_1 IS31FL3743A_I2C_ADDRESS_GND_GND
#define IS31FL3743A_SDB_PIN A4

#define CAPS_LOCK_INDEX 28
#define WIN_MOD_INDEX 16
#define MAC_MOD_INDEX 17

#define g_suspend_state rgb_matrix_get_suspend_state()

// IMEを監視する"observe_ime"を使用する場合、Num Lockでnicola on/offする。
// キーボード単体でnicola on/offを制御する場合はコメントアウトする。
#define USE_OBSERVE_IME

