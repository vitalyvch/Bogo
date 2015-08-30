/*
 *  linux/arch/arm/lib/delay.S
 *
 *  Copyright (C) 1995, 1996 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
//#include <linux/linkage.h>
//#include <asm/assembler.h>

#define RETINSTR(instr, regs...)\
        instr##s        regs

#define ALIGN .align 0
#define SYMBOL_NAME_LABEL(X) X##:
#define SYMBOL_NAME(X) X

#define ENTRY(name) \
  .globl SYMBOL_NAME(name); \
  ALIGN; \
  SYMBOL_NAME_LABEL(name)

		.global HZ
.data
		.align 2
		.type	HZ,object
		.size	HZ,4
HZ:
		.word HZ_VALUE

		.text

LC0:		.word	SYMBOL_NAME(loops_per_jiffy)

/*
 * 0 <= r0 <= 2000
 */
ENTRY(udelay)
		mov	r2,     #0x6800
		orr	r2, r2, #0x00db
		mul	r1, r0, r2
		ldr	r2, LC0
		ldr	r2, [r2]
		mov	r1, r1, lsr #11
		mov	r2, r2, lsr #11
		mul	r0, r1, r2
		movs	r0, r0, lsr #6
		RETINSTR(moveq,pc,lr)

/*
 * loops = (r0 * 0x10c6 * 100 * loops_per_jiffie) / 2^32
 */

@ Delay routine
ENTRY(delay)
		subs	r0, r0, #1
		RETINSTR(movcc,pc,lr)
		subs	r0, r0, #1
		RETINSTR(movcc,pc,lr)
		subs	r0, r0, #1
		RETINSTR(movcc,pc,lr)
		subs	r0, r0, #1
		RETINSTR(movcc,pc,lr)
		subs	r0, r0, #1
		RETINSTR(movcc,pc,lr)
		subs	r0, r0, #1
		RETINSTR(movcc,pc,lr)
		subs	r0, r0, #1
		RETINSTR(movcc,pc,lr)
		subs	r0, r0, #1
		bcs	SYMBOL_NAME(delay)
		RETINSTR(mov,pc,lr)
