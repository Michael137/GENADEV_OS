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

#ifndef TIMER_H_IN
#define TIMER_H_IN

#include <stdint.h>

#include "../gpio/mmio_base.h"

/* See BCM2835 ARM Peripherals Manual, Section "System Timer" */
#define TIMER_CS ((uint32_t*)(MMIO_BASE + 0x00003000))
#define TIMER_CLO ((uint32_t*)(MMIO_BASE + 0x00003004))
#define TIMER_CHI ((uint32_t*)(MMIO_BASE + 0x00003008))
#define TIMER_C0 ((uint32_t*)(MMIO_BASE + 0x0000300c))
#define TIMER_C1 ((uint32_t*)(MMIO_BASE + 0x00003010))
#define TIMER_C2 ((uint32_t*)(MMIO_BASE + 0x00003014))
#define TIMER_C3 ((uint32_t*)(MMIO_BASE + 0x00003018))

#define TIMER_CS_M1 (1 << 0)
#define TIMER_CS_M2 (1 << 1)
#define TIMER_CS_M3 (1 << 2)
#define TIMER_CS_M4 (1 << 3)

void system_timer_init(void);
void handle_system_timer_irq(void);

/* See BCM2836 perihperal manual QA7. Works with qemu-raspi3 */
#define CORE0_TIMER_IRQCNTL ((uint32_t*)0x40000040)
#define CORE1_TIMER_IRQCNTL ((uint32_t*)0x40000044)
#define CORE2_TIMER_IRQCNTL ((uint32_t*)0x40000048)
#define CORE3_TIMER_IRQCNTL ((uint32_t*)0x4000004C)

#define CORE0_IRQ_SOURCE ((uint32_t*)0x40000060)
#define CORE1_IRQ_SOURCE ((uint32_t*)0x40000064)
#define CORE2_IRQ_SOURCE ((uint32_t*)0x40000068)
#define CORE3_IRQ_SOURCE ((uint32_t*)0x4000006C)

#define CORE_INT_SOURCE_CNTPSIRQ (1 << 0)
#define CORE_INT_SOURCE_CNTPNSIRQ (1 << 1)
#define CORE_INT_SOURCE_CNTHPIRQ (1 << 2)
#define CORE_INT_SOURCE_CNTVIRQ (1 << 3)

#define CNTPSIRQ_CTL (1 << 0)
#define CNTPNSIRQ_CTL (1 << 1)
#define CNTHPIRQ_CTL (1 << 2)
#define CNTVIRQ_CTL (1 << 3)

void timer_init(void);
void handle_timer_irq(void);

#endif	// _H
