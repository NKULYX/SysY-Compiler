	.cpu cortex-a72
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"standard.c"
	.text
	.global	a
	.data
	.align	2
	.type	a, %object
	.size	a, 4
a:
	.word	3
	.global	b
	.align	2
	.type	b, %object
	.size	b, 4
b:
	.word	5
	.text
	.align	1
	.global	main
	.arch armv8-a
	.arch_extension crc
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	r7, [sp, #-4]!
	add	r7, sp, #0
	ldr	r3, .L3
.LPIC0:
	add	r3, pc
	ldr	r2, [r3]
	ldr	r3, .L3+4
.LPIC1:
	add	r3, pc
	ldr	r3, [r3]
	add	r3, r3, r2
	mov	r0, r3
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
.L4:
	.align	2
.L3:
	.word	a-(.LPIC0+4)
	.word	b-(.LPIC1+4)
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",%progbits
