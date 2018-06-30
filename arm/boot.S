//
// Created by YoYo kernel team on 21.06.18.
// YoYo project
// Copyright (c) 2018 Addiction, All rights reserved.
//

.section ".text.boot"

.global _start

_start:
    // read cpu id, stop slave cores
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    // cpu id > 0, stop
1:  wfe
    b       1b
2:  // cpu id == 0

    // set stack before our code
    ldr     x1, =_start

    // set up EL1
    mrs     x0, CurrentEL
    and     x0, x0, #12 // clear reserved bits

    // running at EL3?
    cmp     x0, #12
    bne     5f
    // should never be executed, just for completeness
    mov     x2, #0x5b1
    msr     scr_el3, x2
    mov     x2, #0x3c9
    msr     spsr_el3, x2
    adr     x2, 5f
    msr     elr_el3, x2
    eret

    // running at EL2?
5:  cmp     x0, #4
    beq     5f
    msr     sp_el1, x1
    // enable CNTP for EL1
    mrs     x0, cnthctl_el2
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr
    // enable AArch64 in EL1
    mov     x0, #(1 << 31)      // AArch64
    orr     x0, x0, #(1 << 1)   // SWIO hardwired on Pi3
    msr     hcr_el2, x0
    mrs     x0, hcr_el2
    // Setup SCTLR access
    mov     x2, #0x0800
    movk    x2, #0x30d0, lsl #16
    msr     sctlr_el1, x2
    // change execution level to EL1
    mov     x2, #0x3c4
    msr     spsr_el2, x2
    adr     x2, 5f
    msr     elr_el2, x2
    eret

5:  mov     sp, x1

    // clear bss
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
3:  cbz     w2, 4f
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b

    // TODO
    // setup vector table
    	adr	x0, vectorTable		// load VBAR_EL1 with virtual
    	msr	vbar_el1, x0		// vector table address
    // TODO

    // jump to C code, should not return
4:  bl      kernelInit
    // for failsafe, halt this core too
    b       1b

// vector table

#define S_FRAME_SIZE			256 		// size of all saved registers

// Offsets to errorMessages array of strings.
#define SYNC_INVALID_EL1t		0
#define IRQ_INVALID_EL1t		1
#define FIQ_INVALID_EL1t		2
#define ERROR_INVALID_EL1t		3

#define SYNC_INVALID_EL1h		4
#define IRQ_INVALID_EL1h		5
#define FIQ_INVALID_EL1h		6
#define ERROR_INVALID_EL1h		7

#define SYNC_INVALID_EL0_64	    	8
#define IRQ_INVALID_EL0_64	    	9
#define FIQ_INVALID_EL0_64		10
#define ERROR_INVALID_EL0_64		11

#define SYNC_INVALID_EL0_32		12
#define IRQ_INVALID_EL0_32		13
#define FIQ_INVALID_EL0_32		14
#define ERROR_INVALID_EL0_32	15

/* creating entry in vector table */
.macro createEntry       label
    /* every exception vector should be located at offset 0x80 bytes one from another */
    .align 7
    b   \label
.endm

/* Saves values of x0-x30 registers */
.macro	pushCurrentContext
	sub	sp, sp, #S_FRAME_SIZE
	stp	x0, x1, [sp, #16 * 0]
	stp	x2, x3, [sp, #16 * 1]
	stp	x4, x5, [sp, #16 * 2]
	stp	x6, x7, [sp, #16 * 3]
	stp	x8, x9, [sp, #16 * 4]
	stp	x10, x11, [sp, #16 * 5]
	stp	x12, x13, [sp, #16 * 6]
	stp	x14, x15, [sp, #16 * 7]
	stp	x16, x17, [sp, #16 * 8]
	stp	x18, x19, [sp, #16 * 9]
	stp	x20, x21, [sp, #16 * 10]
	stp	x22, x23, [sp, #16 * 11]
	stp	x24, x25, [sp, #16 * 12]
	stp	x26, x27, [sp, #16 * 13]
	stp	x28, x29, [sp, #16 * 14]
	str	x30, [sp, #16 * 15]
.endm

/* Restores values of x0-x30 registers */
.macro	popCurrentContext
	ldp	x0, x1, [sp, #16 * 0]
	ldp	x2, x3, [sp, #16 * 1]
	ldp	x4, x5, [sp, #16 * 2]
	ldp	x6, x7, [sp, #16 * 3]
	ldp	x8, x9, [sp, #16 * 4]
	ldp	x10, x11, [sp, #16 * 5]
	ldp	x12, x13, [sp, #16 * 6]
	ldp	x14, x15, [sp, #16 * 7]
	ldp	x16, x17, [sp, #16 * 8]
	ldp	x18, x19, [sp, #16 * 9]
	ldp	x20, x21, [sp, #16 * 10]
	ldp	x22, x23, [sp, #16 * 11]
	ldp	x24, x25, [sp, #16 * 12]
	ldp	x26, x27, [sp, #16 * 13]
	ldp	x28, x29, [sp, #16 * 14]
	ldr	x30, [sp, #16 * 15]
	add	sp, sp, #S_FRAME_SIZE
	eret
.endm

/* Handling vector table's entries with invalid postfixes */
.macro handleInvalidEntry type
    pushCurrentContext
    mov x0, #\type      /* which exception handler has been executed */
    mrs x1, esr_el1     /* extracted exception reason from ESR register */
    mrs x2, elr_el1     /* address of instruction that threw exception */
    bl showInvalidEntryMessage  /* show exception message */
    b errorHang                 /* infinity loop */
.endm

/* Vector table */
.align	11
.globl vectorTable
vectorTable:
/* All handlers that should never be executed in normal flow have invalid postfix */
/* They will be only executed in case of some hardware exception */
	createEntry	sync_invalid_el1t			// Synchronous EL1t
	createEntry	irq_invalid_el1t			// IRQ EL1t
	createEntry	fiq_invalid_el1t			// FIQ EL1t
	createEntry	error_invalid_el1t			// Error EL1t

/* for kernel the most important */
	createEntry	sync_invalid_el1h			// Synchronous EL1h
	createEntry	EL1_IRQ					    // IRQ EL1h
	createEntry	fiq_invalid_el1h			// FIQ EL1h
	createEntry	error_invalid_el1h			// Error EL1h
/* */

	createEntry	sync_invalid_el0_64			// Synchronous 64-bit EL0
	createEntry	irq_invalid_el0_64			// IRQ 64-bit EL0
	createEntry	fiq_invalid_el0_64			// FIQ 64-bit EL0
	createEntry	error_invalid_el0_64		// Error 64-bit EL0

	createEntry	sync_invalid_el0_32			// Synchronous 32-bit EL0
	createEntry	irq_invalid_el0_32			// IRQ 32-bit EL0
	createEntry	fiq_invalid_el0_32			// FIQ 32-bit EL0
    createEntry error_invalid_el0_32        // Error 32-bit EL0

sync_invalid_el1t:
	handleInvalidEntry  SYNC_INVALID_EL1t

irq_invalid_el1t:
	handleInvalidEntry  IRQ_INVALID_EL1t

fiq_invalid_el1t:
	handleInvalidEntry  FIQ_INVALID_EL1t

error_invalid_el1t:
	handleInvalidEntry  ERROR_INVALID_EL1t

sync_invalid_el1h:
	handleInvalidEntry  SYNC_INVALID_EL1h

fiq_invalid_el1h:
	handleInvalidEntry  FIQ_INVALID_EL1h

error_invalid_el1h:
	handleInvalidEntry  ERROR_INVALID_EL1h

sync_invalid_el0_64:
	handleInvalidEntry  SYNC_INVALID_EL0_64

irq_invalid_el0_64:
	handleInvalidEntry  IRQ_INVALID_EL0_64

fiq_invalid_el0_64:
	handleInvalidEntry  FIQ_INVALID_EL0_64

error_invalid_el0_64:
	handleInvalidEntry  ERROR_INVALID_EL0_64

sync_invalid_el0_32:
	handleInvalidEntry  SYNC_INVALID_EL0_32

irq_invalid_el0_32:
	handleInvalidEntry  IRQ_INVALID_EL0_32

fiq_invalid_el0_32:
	handleInvalidEntry  FIQ_INVALID_EL0_32

error_invalid_el0_32:
	handleInvalidEntry  ERROR_INVALID_EL0_32

EL1_IRQ:
	pushCurrentContext
	bl	handleIRQ
	popCurrentContext

.globl errorHang
errorHang:
    b errorHang
