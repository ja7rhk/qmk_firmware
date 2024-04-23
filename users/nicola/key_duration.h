/*
 * (C) 2020 Sadao Ikebe @bonyarou
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
 * ** koseki(2024.4.12)
 */

#pragma once

#include <ch.h>
//typedef void (*keypress_timer_expired_func_t)(void);
//void keypress_timer_init(keypress_timer_expired_func_t);
//void keypress_timer_start(uint16_t);
void keypress_timer_init(vtfunc_t);
void keypress_timer_start(uint16_t);	// (ms)
