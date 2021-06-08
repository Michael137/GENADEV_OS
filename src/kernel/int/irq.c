/*
     This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS
     Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
     Copyright (C) 2021  Yves Vollmeier, Tim Thompson and Michael Buch

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "irq.h"
#include "../../lib/debug/debug.h"

void handle_irq_unknown(int esr, int elr)
{
	debug(DBG_BOTH,
		  "************************************\n"
		  "Unhandled IRQ:\n"
		  "\tesr: 0x%lx\n"
		  "\telr: 0x%lx\n"
		  "************************************\n",
		  esr, elr
		 );

}

void handle_timer_irq(void)
{}

void handle_irq(void)
{
	unsigned int irq = get32(IRQ_PENDING_1);
	switch(irq) {
		case SYSTEM_TIMER_1:
			handle_timer_irq();
			break;
		default:
			debug(DBG_BOTH, "Unkown pending IRQ: %x\n", irq);
	}
}

void enable_interrupt_controller(void)
{
	put32(ENABLE_IRQS_1, SYSTEM_TIMER_1);
}
