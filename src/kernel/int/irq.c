/*
     This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+
   called GENADEV_OS Everything is openly developed on github:
   https://github.com/GENADEV/GENADEV_OS Copyright (C) 2021  Yves Vollmeier, Tim
   Thompson and Michael Buch

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
#include "../hardware/timer/timer.h"

void handle_irq_unknown(int esr, int elr) {
    debug(DBG_BOTH,
	  "************************************\n"
	  "Unhandled IRQ:\n"
	  "\tesr: 0x%lx\n"
	  "\telr: 0x%lx\n"
	  "************************************\n",
	  esr, elr);
}

void handle_irq(void) {
//    unsigned int irq = *IRQ_PENDING_1;
//    switch (irq) {
//	case SYSTEM_TIMER_1:
//	    handle_system_timer_irq();
//	    break;
	switch(*CORE0_IRQ_SOURCE) {
		case CORE_INT_SOURCE_CNTVIRQ:
			handle_timer_irq();
			break;
		default:
	    	debug(DBG_BOTH,
		  	  "[WARNING] Unknown IRQ received:\n"
		  	  "\tIRQ_PENDING_1: %x\n"
		  	  "\tIRQ_PENDING_2: %x\n"
		  	  "\tIRQ_BASIC_PENDING: %x\n"
		  	  "\tIRQ_CORE0_INTERRUPT_SOURCE: %x\n"
		  	  "\tIRQ_CORE1_INTERRUPT_SOURCE: %x\n"
		  	  "\tIRQ_CORE2_INTERRUPT_SOURCE: %x\n"
		  	  "\tIRQ_CORE3_INTERRUPT_SOURCE: %x\n",
		  	  *IRQ_PENDING_1, *IRQ_PENDING_2, *IRQ_BASIC_PENDING,
		  	  *CORE0_IRQ_SOURCE, *CORE1_IRQ_SOURCE, *CORE2_IRQ_SOURCE,
		  	  *CORE3_IRQ_SOURCE);
	    	break;
	}
//}
}

void enable_interrupt_controller(void) {
    // System timer is not emulated on QEMU so below line
    // doesn't habe an effect there
    *ENABLE_IRQS_1 = SYSTEM_TIMER_1;

    *ENABLE_BASIC_IRQS = BASE_IRQ_ARM_TIMER;
}
