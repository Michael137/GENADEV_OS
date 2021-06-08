/*
 *   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+
 * called GENADEV_OS Everything is openly developed on github:
 * https://github.com/GENADEV/GENADEV_OS Copyright (C) 2021 Michael Buch
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "timer.h"

#include "../../../lib/debug/debug.h"

static unsigned int const interval = 5000000;

void system_timer_init(void) {
    *TIMER_C1 = *TIMER_CLO + interval;
    debug(DBG_BOTH,
	  "Initialized system timer 1 at [interval = %u] [TIMER_CLO = %u]\n",
	  interval, *TIMER_CLO);
}

void handle_timer_irq(void) {
    unsigned int curNumTicks = *TIMER_CLO;
    curNumTicks += interval;

    *TIMER_C1 = curNumTicks;
    *TIMER_CS = TIMER_CS_M1;
    debug(DBG_BOTH, "Received timer IRQ");
}

void timer_init(void) {
    uint32_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
    asm volatile("msr cntv_tval_el0, %0" ::"r"(freq));

    uint32_t cntv_tval;
    asm volatile("mrs %0, cntv_tval_el0" : "=r"(cntv_tval));

    debug(DBG_BOTH, "[cntrfrq_el0 = 0x%x] [cntv_tval_el0 = 0x%x]\n", freq,
	  cntv_tval);

	*CORE0_TIMER_IRQCNTL = CNTVIRQ_CTL;

	// Enable virtual timer
	uint32_t enable = 1;
	asm volatile ("msr cntv_ctl_el0, %0" ::"r" (enable));
}
