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
	.align	1
	.global	f
	.arch armv8-a
	.arch_extension crc
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	f, %function
f:
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	r7, [sp, #-4]!
	sub	sp, sp, #20
	add	r7, sp, #0
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	str	r2, [r7, #4]
	str	r3, [r7]
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #8]
	add	r2, r2, r3
	ldr	r3, [r7, #4]
	add	r2, r2, r3
	ldr	r3, [r7]
	add	r2, r2, r3
	ldr	r3, [r7, #24]
	add	r3, r3, r2
	mov	r0, r3
	add	r7, r7, #20
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
	.size	f, .-f
	.global	abc
	.data
	.align	2
	.type	abc, %object
	.size	abc, 4
abc:
	.word	10
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	strd	r7, lr, [sp, #-8]!
	sub	sp, sp, #40
	add	r7, sp, #8
	mov	r3, #1
	str	r3, [r7]
	mov	r3, #2
	str	r3, [r7, #4]
	mov	r3, #3
	str	r3, [r7, #8]
	mov	r3, #4
	str	r3, [r7, #12]
	mov	r3, #5
	str	r3, [r7, #16]
	mov	r3, #6
	str	r3, [r7, #20]
	mov	r3, #7
	str	r3, [r7, #24]
	ldr	r3, abc
.LPIC0:
	add	r3, pc
	ldr	r2, [r3]
	ldr	r3, [r7, #16]
	str	r3, [sp]
	mov	r3, r2
	ldr	r2, [r7, #8]
	ldr	r1, [r7, #4]
	ldr	r0, [r7]
	bl	f(PLT)
	str	r0, [r7, #28]
	ldr	r3, abc
.LPIC1:
	add	r3, pc
	ldr	r3, [r3]
	ldr	r2, [r7, #28]
	add	r3, r3, r2
	str	r3, [r7, #28]
	ldr	r3, [r7, #28]
	mov	r0, r3
	add	r7, r7, #32
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L6:
	.align	2
.L5:
	.word	abc-(.LPIC0+4)
	.word	abc-(.LPIC1+4)
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",%progbits
