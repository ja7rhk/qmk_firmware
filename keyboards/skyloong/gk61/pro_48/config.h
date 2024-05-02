// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define IS31FL3743A_I2C_ADDRESS_1 IS31FL3743A_I2C_ADDRESS_GND_GND
#define IS31FL3743A_SDB_PIN A4

#define CAPS_LOCK_INDEX 28
#define WIN_MOD_INDEX 16
#define MAC_MOD_INDEX 17
#define OYA_LEFT_INDEX 56
#define OYA_CENTER_INDEX 58
#define OYA_RIGHT_INDEX 59
#define FN_PU_INDEX 37       // L : PageUp
#define FN_PD_INDEX 50       // > : PageDown
#define FN_UP_INDEX 52       // SHIFT : ↑
#define FN_LEFT_INDEX 61     // ALT : ←
#define FN_DOWN_INDEX 62     // MENU : ↓
#define FN_RIGHT_INDEX 63    // CTRL : →

#define g_suspend_state rgb_matrix_get_suspend_state()
