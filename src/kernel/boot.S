/*
     This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS
     Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
     Copyright (C) 2021  Yves Vollmeier and Tim Thompson

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

// .section .text.boot
// 
// .global _start
// _start:
// 	//For now all but the primary core will be suspended
// 	mrs x0, mpidr_el1 //Multiprocessor Affinity Register
// 	and x0, x0, #0xFF //Lower 8 bits indicate the core no.
// 	cbz x0, 2f		  //Is the Core ID == 0? (Main core)
// 	b hang			  //Stop the core
// 
// //Main core is the only thing executing useful code from here on
// 2:
// 	//Setup stack
// 	ldr x1, = _start
// 	mov sp, x1
// 
// 	bl bss_zero 	// Zero out bss
// 	bl main			// Kernel entry point
// 	b hang
// 
// bss_zero:
// 	//Get size of bss section
// 	ldr x0, = __bss_start
// 	ldr x1, = __bss_size
// 	sub x3, x0, x1
// 
// 1:
// 	sub x3, x1, x0      //Decrement the counter which specifies when the bss section is all zero
// 	str xzr, [x0], #8   //clear out a section of bss data in byte sized chunks
// 	bgt 1b		    //goto 1 if x3 > 0x0
// 	ret
// 
// hang:
// 	wfi
// 	b hang

.section ".text.boot"
 
// Make _start global.
.globl _start
 
_start:
    // in QEMU all of 4 ARM CPUs are started simultaniously
    // by default. I don't know if this is the real hw behaviour,
    // but here I jump to halt if CPU ID (stored in MPIDR
    // register, first 2 bits) is not 0
    mrs   x1, mpidr_el1
    and   x1, x1, #3
    cmp   x1, #0
    bne   hang 

    // address for stack pointer
    ldr   x1, =_start

    // drop to EL2
    mov   x2, #0x5b1    // RW=1, HCE=1, SMD=1, RES=1, NS=1
    msr   scr_el3, x2
    mov   x2, #0x3c9    // D=1, A=1, I=1, F=1 M=EL2h
    msr   spsr_el3, x2
    mov x3, #0x300000
	msr cpacr_el1, x3
    adr   x2, start_el2
    msr   elr_el3, x2
    eret

start_el2:
    // set sp in EL1
    msr   sp_el1, x1
    // enable AArch64 in EL1
    mov   x0, #(1 << 31)      // AArch64
    orr   x0, x0, #(1 << 1)   // SWIO hardwired on Pi3
    msr   hcr_el2, x0
    mrs   x0, hcr_el2
    // set vector address in EL1.
    ldr x0, =vector
    msr vbar_el1, x0 
    // change execution level to EL1
    mov   x2, #0x3c4         // D=1, A=1, I=1, F=1 M=EL1t
    msr   spsr_el2, x2
    adr   x2, start_el1
    msr   elr_el2, x2
    eret

start_el1:
    // set sp
    mov   sp, x1
    // Clear bss.
    ldr   x1, =__bss_start
    ldr   w2, =__bss_size
1:  cbz   w2, 2f
    str   xzr, [x1], #8
    sub   w2, w2, #1
    cbnz  w2, 1b

2:  bl main

hang:
    wfi
    b     hang

.globl enable_irq
enable_irq:
    msr   daifclr, #2
    ret

.globl disable_irq
disable_irq:
    msr   daifset, #2
    ret

irq:
    stp   x0,  x1,  [sp, #-16]!
    stp   x2,  x3,  [sp, #-16]!
    stp   x4,  x5,  [sp, #-16]!
    stp   x6,  x7,  [sp, #-16]!
    stp   x8,  x9,  [sp, #-16]!
    stp   x10, x11, [sp, #-16]!
    stp   x12, x13, [sp, #-16]!
    stp   x14, x15, [sp, #-16]!
    stp   x16, x17, [sp, #-16]!
    stp   x18, x19, [sp, #-16]!

    bl    handle_irq

    ldp   x18, x19, [sp], #16
    ldp   x16, x17, [sp], #16
    ldp   x14, x15, [sp], #16
    ldp   x12, x13, [sp], #16
    ldp   x10, x11, [sp], #16
    ldp   x8,  x9,  [sp], #16
    ldp   x6,  x7,  [sp], #16
    ldp   x4,  x5,  [sp], #16
    ldp   x2,  x3,  [sp], #16
    ldp   x0,  x1,  [sp], #16
    eret

.balign 4096
vector:
.balign 128
    b hang
.balign 128
    b irq
.balign 128
    b hang
.balign 128
    b hang
.balign 128
    b hang
.balign 128
    b irq
.balign 128
    b hang
.balign 128
    b hang
.balign 128
    b hang
.balign 128
    b irq
.balign 128
    b hang
.balign 128
    b hang
.balign 128
    b hang
.balign 128
    b irq
.balign 128
    b hang
.balign 128
    b hang

.section .data
	.extern handle_irq_unknown
	loaded_irq_msg: .asciz "Installed IRQ's\n"
