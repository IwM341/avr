	.file	"HardwareSerial0.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text._ZN5Print17availableForWriteEv,"axG",@progbits,_ZN5Print17availableForWriteEv,comdat
	.weak	_ZN5Print17availableForWriteEv
	.type	_ZN5Print17availableForWriteEv, @function
_ZN5Print17availableForWriteEv:
.LFB9:
	.file 1 ".././Print.h"
	.loc 1 62 0
	.cfi_startproc
.LVL0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 62 0
	ldi r24,0
	ldi r25,0
.LVL1:
	ret
	.cfi_endproc
.LFE9:
	.size	_ZN5Print17availableForWriteEv, .-_ZN5Print17availableForWriteEv
	.section	.text._ZN5Print5flushEv,"axG",@progbits,_ZN5Print5flushEv,comdat
	.weak	_ZN5Print5flushEv
	.type	_ZN5Print5flushEv, @function
_ZN5Print5flushEv:
.LFB10:
	.loc 1 85 0
	.cfi_startproc
.LVL2:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE10:
	.size	_ZN5Print5flushEv, .-_ZN5Print5flushEv
	.section	.text._Z41__static_initialization_and_destruction_0ii,"ax",@progbits
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB39:
	.file 2 ".././HardwareSerial0.cpp"
	.loc 2 76 0
	.cfi_startproc
.LVL3:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 2 76 0
	sbiw r24,1
	brne .L3
	.loc 2 76 0 is_stmt 0 discriminator 1
	cpi r22,-1
	sbci r23,-1
.LVL4:
	brne .L3
.LVL5:
.LBB23:
.LBB24:
.LBB25:
.LBB26:
.LBB27:
.LBB28:
	.loc 1 45 0 is_stmt 1
	ldi r30,lo8(Serial)
	ldi r31,hi8(Serial)
	std Z+3,__zero_reg__
	std Z+2,__zero_reg__
.LVL6:
.LBE28:
.LBE27:
	.file 3 ".././Stream.h"
	.loc 3 63 0
	ldi r24,lo8(-24)
	ldi r25,lo8(3)
	ldi r26,0
	ldi r27,0
	std Z+4,r24
	std Z+5,r25
	std Z+6,r26
	std Z+7,r27
.LVL7:
.LBE26:
.LBE25:
	.file 4 ".././HardwareSerial.h"
	.loc 4 135 0
	ldi r24,lo8(_ZTV14HardwareSerial+4)
	ldi r25,hi8(_ZTV14HardwareSerial+4)
	std Z+1,r25
	st Z,r24
	ldi r24,lo8(-59)
	ldi r25,0
	std Z+13,r25
	std Z+12,r24
	ldi r24,lo8(-60)
	ldi r25,0
	std Z+15,r25
	std Z+14,r24
	ldi r24,lo8(-64)
	ldi r25,0
	std Z+17,r25
	std Z+16,r24
	ldi r24,lo8(-63)
	ldi r25,0
	std Z+19,r25
	std Z+18,r24
	ldi r24,lo8(-62)
	ldi r25,0
	std Z+21,r25
	std Z+20,r24
	ldi r24,lo8(-58)
	ldi r25,0
	std Z+23,r25
	std Z+22,r24
	std Z+25,__zero_reg__
	std Z+26,__zero_reg__
	std Z+27,__zero_reg__
	std Z+28,__zero_reg__
	ldi r24,0
	ldi r25,lo8(36)
	ldi r26,lo8(-12)
	ldi r27,0
	sts Serial+157,r24
	sts Serial+157+1,r25
	sts Serial+157+2,r26
	sts Serial+157+3,r27
.LVL8:
.L3:
	ret
.LBE24:
.LBE23:
	.cfi_endproc
.LFE39:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.section	.text.__vector_18,"ax",@progbits
.global	__vector_18
	.type	__vector_18, @function
__vector_18:
.LFB36:
	.loc 2 47 0
	.cfi_startproc
	push r1
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI2:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r24
.LCFI3:
	.cfi_def_cfa_offset 6
	.cfi_offset 24, -5
	push r25
.LCFI4:
	.cfi_def_cfa_offset 7
	.cfi_offset 25, -6
	push r26
.LCFI5:
	.cfi_def_cfa_offset 8
	.cfi_offset 26, -7
	push r27
.LCFI6:
	.cfi_def_cfa_offset 9
	.cfi_offset 27, -8
	push r30
.LCFI7:
	.cfi_def_cfa_offset 10
	.cfi_offset 30, -9
	push r31
.LCFI8:
	.cfi_def_cfa_offset 11
	.cfi_offset 31, -10
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 10 */
.L__stack_usage = 10
.LVL9:
.LBB29:
.LBB30:
	.loc 4 159 0
	lds r30,Serial+16
	lds r31,Serial+16+1
	.loc 4 159 0
	ld r24,Z
	.loc 4 159 0
	sbrc r24,2
	rjmp .L6
.LBB31:
	.loc 4 162 0
	ldi r30,lo8(Serial)
	ldi r31,hi8(Serial)
	ldd r26,Z+22
	ldd r27,Z+23
	ld r18,X
.LVL10:
	.loc 4 163 0
	ldd r24,Z+25
	subi r24,lo8(-(1))
	andi r24,lo8(63)
.LVL11:
	.loc 4 169 0
	ldd r25,Z+26
	cp r24,r25
	breq .L5
	.loc 4 170 0
	movw r26,r30
	ldd r30,Z+25
	ldi r31,0
	subi r30,lo8(-(Serial))
	sbci r31,hi8(-(Serial))
	std Z+29,r18
	.loc 4 171 0
	adiw r26,25
	st X,r24
	rjmp .L5
.LVL12:
.L6:
.LBE31:
	.loc 4 175 0
	lds r30,Serial+22
	lds r31,Serial+22+1
	ld r24,Z
.LVL13:
.L5:
/* epilogue start */
.LBE30:
.LBE29:
	.loc 2 49 0
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE36:
	.size	__vector_18, .-__vector_18
	.section	.text.__vector_19,"ax",@progbits
.global	__vector_19
	.type	__vector_19, @function
__vector_19:
.LFB37:
	.loc 2 62 0
	.cfi_startproc
	push r1
.LCFI9:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI10:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI11:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r24
.LCFI12:
	.cfi_def_cfa_offset 6
	.cfi_offset 24, -5
	push r25
.LCFI13:
	.cfi_def_cfa_offset 7
	.cfi_offset 25, -6
	push r26
.LCFI14:
	.cfi_def_cfa_offset 8
	.cfi_offset 26, -7
	push r27
.LCFI15:
	.cfi_def_cfa_offset 9
	.cfi_offset 27, -8
	push r30
.LCFI16:
	.cfi_def_cfa_offset 10
	.cfi_offset 30, -9
	push r31
.LCFI17:
	.cfi_def_cfa_offset 11
	.cfi_offset 31, -10
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 10 */
.L__stack_usage = 10
.LVL14:
.LBB34:
.LBB35:
	.loc 4 181 0
	ldi r26,lo8(Serial)
	ldi r27,hi8(Serial)
	adiw r26,28
	ld r30,X
	sbiw r26,28
	ldi r31,0
	subi r30,lo8(-(Serial+93))
	sbci r31,hi8(-(Serial+93))
	ld r18,Z
.LVL15:
	.loc 4 182 0
	adiw r26,28
	ld r24,X
	ldi r25,0
	adiw r24,1
	andi r24,63
	andi r25,128
	tst r25
	brge .L9
	sbiw r24,1
	ori r24,192
	ori r25,255
	adiw r24,1
.L9:
	ldi r30,lo8(Serial)
	ldi r31,hi8(Serial)
	std Z+28,r24
	.loc 4 184 0
	ldd r26,Z+22
	ldd r27,Z+23
	st X,r18
	.loc 4 192 0
	ldd r26,Z+16
	ldd r27,Z+17
	.loc 4 192 0
	ld r24,X
	andi r24,lo8(3)
	ori r24,lo8(64)
	st X,r24
	.loc 4 197 0
	ldd r25,Z+27
	ldd r24,Z+28
	cpse r25,r24
	rjmp .L8
	.loc 4 199 0
	lds r30,Serial+18
	lds r31,Serial+18+1
	.loc 4 199 0
	ld r24,Z
	andi r24,lo8(-33)
	st Z,r24
.LVL16:
.L8:
/* epilogue start */
.LBE35:
.LBE34:
	.loc 2 64 0
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE37:
	.size	__vector_19, .-__vector_19
	.section	.text._Z17Serial0_availablev,"ax",@progbits
.global	_Z17Serial0_availablev
	.type	_Z17Serial0_availablev, @function
_Z17Serial0_availablev:
.LFB38:
	.loc 2 74 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 2 75 0
	ldi r24,lo8(Serial)
	ldi r25,hi8(Serial)
	call _ZN14HardwareSerial9availableEv
.LVL17:
	ldi r18,lo8(1)
	or r24,r25
	brne .L12
	ldi r18,0
.L12:
	.loc 2 76 0
	mov r24,r18
	ret
	.cfi_endproc
.LFE38:
	.size	_Z17Serial0_availablev, .-_Z17Serial0_availablev
	.section	.text._GLOBAL__sub_I___vector_18,"ax",@progbits
	.type	_GLOBAL__sub_I___vector_18, @function
_GLOBAL__sub_I___vector_18:
.LFB40:
	.loc 2 76 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 2 76 0
	ldi r22,lo8(-1)
	ldi r23,lo8(-1)
	ldi r24,lo8(1)
	ldi r25,0
	call _Z41__static_initialization_and_destruction_0ii
.LVL18:
	ret
	.cfi_endproc
.LFE40:
	.size	_GLOBAL__sub_I___vector_18, .-_GLOBAL__sub_I___vector_18
	.global __do_global_ctors
	.section .ctors,"a",@progbits
	.p2align	1
	.word	gs(_GLOBAL__sub_I___vector_18)
	.weak	_ZTV6Stream
	.section	.rodata._ZTV6Stream,"aG",@progbits,_ZTV6Stream,comdat
	.type	_ZTV6Stream, @object
	.size	_ZTV6Stream, 18
_ZTV6Stream:
	.word	0
	.word	0
	.word	gs(__cxa_pure_virtual)
	.word	gs(_ZN5Print5writeEPKhj)
	.word	gs(_ZN5Print17availableForWriteEv)
	.word	gs(_ZN5Print5flushEv)
	.word	gs(__cxa_pure_virtual)
	.word	gs(__cxa_pure_virtual)
	.word	gs(__cxa_pure_virtual)
.global	Serial
	.section	.bss.Serial,"aw",@nobits
	.type	Serial, @object
	.size	Serial, 161
Serial:
	.zero	161
	.text
.Letext0:
	.file 5 "d:\\soft\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\avr\\include\\stdint.h"
	.file 6 "d:\\soft\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\lib\\gcc\\avr\\5.4.0\\include\\stddef.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xa44
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF93
	.byte	0x4
	.long	.LASF94
	.long	.LASF95
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF2
	.byte	0x5
	.byte	0x7e
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF3
	.byte	0x5
	.byte	0x80
	.long	0x54
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF8
	.uleb128 0x3
	.long	.LASF9
	.byte	0x6
	.byte	0xd8
	.long	0x54
	.uleb128 0x5
	.byte	0x2
	.long	0x88
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF10
	.uleb128 0x6
	.long	.LASF96
	.byte	0x1
	.long	0x3b
	.byte	0x3
	.byte	0x29
	.long	0xb2
	.uleb128 0x7
	.long	.LASF11
	.byte	0
	.uleb128 0x7
	.long	.LASF12
	.byte	0x1
	.uleb128 0x7
	.long	.LASF13
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.long	.LASF18
	.byte	0xc
	.byte	0x3
	.byte	0x31
	.long	0x668
	.long	0x5bd
	.uleb128 0x9
	.long	.LASF97
	.byte	0x6
	.byte	0x3
	.byte	0x72
	.byte	0x2
	.long	0xfa
	.uleb128 0xa
	.string	"str"
	.byte	0x3
	.byte	0x73
	.long	0x5bd
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.string	"len"
	.byte	0x3
	.byte	0x74
	.long	0x77
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0xb
	.long	.LASF14
	.byte	0x3
	.byte	0x75
	.long	0x77
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0xc
	.long	0x668
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0x1
	.uleb128 0xd
	.long	.LASF15
	.byte	0x3
	.byte	0x34
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x2
	.uleb128 0xd
	.long	.LASF16
	.byte	0x3
	.byte	0x35
	.long	0x62
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0x2
	.uleb128 0xe
	.byte	0x1
	.long	.LASF17
	.long	.LASF19
	.byte	0x1
	.byte	0x1
	.long	0x135
	.long	0x142
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0xf
	.long	0x42
	.byte	0x1
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.long	.LASF18
	.long	.LASF20
	.byte	0x1
	.byte	0x1
	.long	0x156
	.long	0x162
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x70d
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.long	.LASF18
	.long	.LASF21
	.byte	0x1
	.byte	0x1
	.long	0x176
	.long	0x182
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x713
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF22
	.byte	0x3
	.byte	0x36
	.long	.LASF24
	.long	0x42
	.byte	0x2
	.byte	0x1
	.long	0x19c
	.long	0x1a3
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF23
	.byte	0x3
	.byte	0x37
	.long	.LASF25
	.long	0x42
	.byte	0x2
	.byte	0x1
	.long	0x1bd
	.long	0x1c4
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF26
	.byte	0x3
	.byte	0x38
	.long	.LASF27
	.long	0x42
	.byte	0x2
	.byte	0x1
	.long	0x1de
	.long	0x1ef
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x8f
	.uleb128 0x10
	.long	0x71e
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF28
	.byte	0x3
	.byte	0x3b
	.long	.LASF30
	.long	0x42
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.long	0xb2
	.byte	0x1
	.long	0x210
	.long	0x217
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF29
	.byte	0x3
	.byte	0x3c
	.long	.LASF31
	.long	0x42
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x5
	.long	0xb2
	.byte	0x1
	.long	0x238
	.long	0x23f
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF32
	.byte	0x3
	.byte	0x3d
	.long	.LASF33
	.long	0x42
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x6
	.long	0xb2
	.byte	0x1
	.long	0x260
	.long	0x267
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF18
	.byte	0x3
	.byte	0x3f
	.long	.LASF35
	.byte	0x1
	.long	0x27c
	.long	0x283
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF34
	.byte	0x3
	.byte	0x43
	.long	.LASF36
	.byte	0x1
	.long	0x298
	.long	0x2a4
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x62
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF37
	.byte	0x3
	.byte	0x44
	.long	.LASF39
	.long	0x62
	.byte	0x1
	.long	0x2bd
	.long	0x2c4
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF38
	.byte	0x3
	.byte	0x46
	.long	.LASF40
	.long	0x71e
	.byte	0x1
	.long	0x2dd
	.long	0x2e9
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x82
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF38
	.byte	0x3
	.byte	0x47
	.long	.LASF41
	.long	0x71e
	.byte	0x1
	.long	0x302
	.long	0x30e
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x725
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF38
	.byte	0x3
	.byte	0x4a
	.long	.LASF42
	.long	0x71e
	.byte	0x1
	.long	0x327
	.long	0x338
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x82
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF38
	.byte	0x3
	.byte	0x4b
	.long	.LASF43
	.long	0x71e
	.byte	0x1
	.long	0x351
	.long	0x362
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x725
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF38
	.byte	0x3
	.byte	0x4e
	.long	.LASF44
	.long	0x71e
	.byte	0x1
	.long	0x37b
	.long	0x387
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x88
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF45
	.byte	0x3
	.byte	0x50
	.long	.LASF46
	.long	0x71e
	.byte	0x1
	.long	0x3a0
	.long	0x3b1
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x82
	.uleb128 0x10
	.long	0x82
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF45
	.byte	0x3
	.byte	0x51
	.long	.LASF47
	.long	0x71e
	.byte	0x1
	.long	0x3ca
	.long	0x3db
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x725
	.uleb128 0x10
	.long	0x82
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF45
	.byte	0x3
	.byte	0x53
	.long	.LASF48
	.long	0x71e
	.byte	0x1
	.long	0x3f4
	.long	0x40f
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x82
	.uleb128 0x10
	.long	0x77
	.uleb128 0x10
	.long	0x82
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF45
	.byte	0x3
	.byte	0x54
	.long	.LASF49
	.long	0x71e
	.byte	0x1
	.long	0x428
	.long	0x443
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x725
	.uleb128 0x10
	.long	0x77
	.uleb128 0x10
	.long	0x82
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF50
	.byte	0x3
	.byte	0x56
	.long	.LASF51
	.long	0x5b
	.byte	0x1
	.long	0x45c
	.long	0x46d
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x8f
	.uleb128 0x10
	.long	0x88
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF52
	.byte	0x3
	.byte	0x5d
	.long	.LASF53
	.long	0x72b
	.byte	0x1
	.long	0x486
	.long	0x497
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x8f
	.uleb128 0x10
	.long	0x88
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF54
	.byte	0x3
	.byte	0x60
	.long	.LASF55
	.long	0x77
	.byte	0x1
	.long	0x4b0
	.long	0x4c1
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x82
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF54
	.byte	0x3
	.byte	0x61
	.long	.LASF56
	.long	0x77
	.byte	0x1
	.long	0x4da
	.long	0x4eb
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x725
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF57
	.byte	0x3
	.byte	0x65
	.long	.LASF58
	.long	0x77
	.byte	0x1
	.long	0x504
	.long	0x51a
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x88
	.uleb128 0x10
	.long	0x82
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF57
	.byte	0x3
	.byte	0x66
	.long	.LASF59
	.long	0x77
	.byte	0x1
	.long	0x533
	.long	0x549
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x88
	.uleb128 0x10
	.long	0x725
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF50
	.byte	0x3
	.byte	0x6c
	.long	.LASF60
	.long	0x5b
	.byte	0x2
	.byte	0x1
	.long	0x563
	.long	0x56f
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x88
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF52
	.byte	0x3
	.byte	0x6d
	.long	.LASF61
	.long	0x72b
	.byte	0x2
	.byte	0x1
	.long	0x589
	.long	0x595
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x88
	.byte	0
	.uleb128 0x15
	.byte	0x1
	.long	.LASF62
	.byte	0x3
	.byte	0x7a
	.long	.LASF63
	.long	0x42
	.byte	0x2
	.byte	0x1
	.long	0x5ab
	.uleb128 0xf
	.long	0x707
	.byte	0x1
	.uleb128 0x10
	.long	0x732
	.uleb128 0x10
	.long	0x42
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.long	0x5c3
	.uleb128 0x16
	.long	0x88
	.uleb128 0x3
	.long	.LASF64
	.byte	0x4
	.byte	0x41
	.long	0x30
	.uleb128 0x17
	.long	.LASF65
	.byte	0x1
	.long	0x668
	.uleb128 0x18
	.byte	0x4
	.byte	0x66
	.long	0x672
	.uleb128 0x13
	.byte	0x1
	.long	.LASF65
	.byte	0x4
	.byte	0x7e
	.long	.LASF66
	.byte	0x1
	.long	0x5f9
	.long	0x61e
	.uleb128 0xf
	.long	0x774
	.byte	0x1
	.uleb128 0x10
	.long	0x77a
	.uleb128 0x10
	.long	0x77a
	.uleb128 0x10
	.long	0x77a
	.uleb128 0x10
	.long	0x77a
	.uleb128 0x10
	.long	0x77a
	.uleb128 0x10
	.long	0x77a
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF67
	.byte	0x4
	.byte	0x9e
	.long	.LASF68
	.byte	0x1
	.long	0x633
	.long	0x63a
	.uleb128 0xf
	.long	0x774
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF69
	.byte	0x4
	.byte	0xb2
	.long	.LASF70
	.byte	0x1
	.long	0x64f
	.long	0x656
	.uleb128 0xf
	.long	0x774
	.byte	0x1
	.byte	0
	.uleb128 0x19
	.byte	0x1
	.byte	0x1
	.long	.LASF98
	.long	.LASF28
	.byte	0x4
	.byte	0x90
	.long	.LASF98
	.byte	0
	.uleb128 0x17
	.long	.LASF71
	.byte	0x1
	.long	0x701
	.uleb128 0x14
	.byte	0x1
	.long	.LASF72
	.byte	0x1
	.byte	0x38
	.long	.LASF73
	.long	0x77
	.byte	0x1
	.long	0x68b
	.long	0x69c
	.uleb128 0xf
	.long	0x701
	.byte	0x1
	.uleb128 0x10
	.long	0x5bd
	.uleb128 0x10
	.long	0x77
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF71
	.byte	0x1
	.byte	0x2d
	.long	.LASF74
	.byte	0x1
	.long	0x6b1
	.long	0x6b8
	.uleb128 0xf
	.long	0x701
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF75
	.byte	0x1
	.byte	0x3e
	.long	.LASF76
	.long	0x42
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x2
	.long	0x668
	.byte	0x1
	.long	0x6d9
	.long	0x6e0
	.uleb128 0xf
	.long	0x701
	.byte	0x1
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF77
	.byte	0x1
	.byte	0x55
	.long	.LASF78
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x3
	.long	0x668
	.byte	0x1
	.long	0x6f9
	.uleb128 0xf
	.long	0x701
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.long	0x668
	.uleb128 0x5
	.byte	0x2
	.long	0xb2
	.uleb128 0x1b
	.byte	0x2
	.long	0xb2
	.uleb128 0x1b
	.byte	0x2
	.long	0x719
	.uleb128 0x16
	.long	0xb2
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.long	.LASF79
	.uleb128 0x5
	.byte	0x2
	.long	0x30
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.long	.LASF80
	.uleb128 0x5
	.byte	0x2
	.long	0xc2
	.uleb128 0x1c
	.long	0x69c
	.byte	0x3
	.long	0x746
	.long	0x751
	.uleb128 0x1d
	.long	.LASF81
	.long	0x751
	.byte	0x1
	.byte	0
	.uleb128 0x16
	.long	0x701
	.uleb128 0x1c
	.long	0x267
	.byte	0x3
	.long	0x764
	.long	0x76f
	.uleb128 0x1d
	.long	.LASF81
	.long	0x76f
	.byte	0x1
	.byte	0
	.uleb128 0x16
	.long	0x707
	.uleb128 0x5
	.byte	0x2
	.long	0x5d3
	.uleb128 0x5
	.byte	0x2
	.long	0x780
	.uleb128 0x1e
	.long	0x30
	.uleb128 0x1c
	.long	0x5e4
	.byte	0x3
	.long	0x793
	.long	0x7e0
	.uleb128 0x1d
	.long	.LASF81
	.long	0x7e0
	.byte	0x1
	.uleb128 0x1f
	.long	.LASF82
	.byte	0x4
	.byte	0x7f
	.long	0x77a
	.uleb128 0x1f
	.long	.LASF83
	.byte	0x4
	.byte	0x7f
	.long	0x77a
	.uleb128 0x1f
	.long	.LASF84
	.byte	0x4
	.byte	0x80
	.long	0x77a
	.uleb128 0x1f
	.long	.LASF85
	.byte	0x4
	.byte	0x80
	.long	0x77a
	.uleb128 0x1f
	.long	.LASF86
	.byte	0x4
	.byte	0x81
	.long	0x77a
	.uleb128 0x20
	.string	"udr"
	.byte	0x4
	.byte	0x81
	.long	0x77a
	.byte	0
	.uleb128 0x16
	.long	0x774
	.uleb128 0x1c
	.long	0x61e
	.byte	0x3
	.long	0x7f3
	.long	0x812
	.uleb128 0x1d
	.long	.LASF81
	.long	0x7e0
	.byte	0x1
	.uleb128 0x21
	.uleb128 0x22
	.string	"c"
	.byte	0x4
	.byte	0xa2
	.long	0x3b
	.uleb128 0x22
	.string	"i"
	.byte	0x4
	.byte	0xa3
	.long	0x5c8
	.byte	0
	.byte	0
	.uleb128 0x23
	.long	0x6b8
	.long	.LFB9
	.long	.LFE9
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	0x82c
	.byte	0x1
	.long	0x83b
	.uleb128 0x24
	.long	.LASF81
	.long	0x751
	.byte	0x1
	.long	.LLST0
	.byte	0
	.uleb128 0x23
	.long	0x6e0
	.long	.LFB10
	.long	.LFE10
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	0x855
	.byte	0x1
	.long	0x867
	.uleb128 0x25
	.long	.LASF81
	.long	0x751
	.byte	0x1
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0
	.uleb128 0x26
	.long	.LASF91
	.byte	0x1
	.long	.LFB39
	.long	.LFE39
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x915
	.uleb128 0x27
	.long	.LASF87
	.byte	0x2
	.byte	0x4c
	.long	0x42
	.long	.LLST1
	.uleb128 0x28
	.long	.LASF88
	.byte	0x2
	.byte	0x4c
	.long	0x42
	.byte	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.uleb128 0x29
	.long	0x785
	.long	.LBB23
	.long	.LBE23
	.byte	0x2
	.byte	0x45
	.uleb128 0x2a
	.long	0x7d4
	.long	.LLST2
	.uleb128 0x2a
	.long	0x7c9
	.long	.LLST3
	.uleb128 0x2a
	.long	0x7be
	.long	.LLST4
	.uleb128 0x2a
	.long	0x7b3
	.long	.LLST5
	.uleb128 0x2a
	.long	0x7a8
	.long	.LLST6
	.uleb128 0x2a
	.long	0x79d
	.long	.LLST7
	.uleb128 0x2b
	.long	0x793
	.uleb128 0x29
	.long	0x756
	.long	.LBB25
	.long	.LBE25
	.byte	0x4
	.byte	0x87
	.uleb128 0x2b
	.long	0x764
	.uleb128 0x29
	.long	0x738
	.long	.LBB27
	.long	.LBE27
	.byte	0x3
	.byte	0x3f
	.uleb128 0x2b
	.long	0x746
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF89
	.byte	0x2
	.byte	0x27
	.long	.LFB36
	.long	.LFE36
	.long	.LLST8
	.byte	0x1
	.long	0x960
	.uleb128 0x29
	.long	0x7e5
	.long	.LBB29
	.long	.LBE29
	.byte	0x2
	.byte	0x30
	.uleb128 0x2b
	.long	0x7f3
	.uleb128 0x2d
	.long	.LBB31
	.long	.LBE31
	.uleb128 0x2e
	.long	0x7fe
	.long	.LLST9
	.uleb128 0x2e
	.long	0x807
	.long	.LLST10
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.long	0x63a
	.byte	0x3
	.long	0x96e
	.long	0x982
	.uleb128 0x1d
	.long	.LASF81
	.long	0x7e0
	.byte	0x1
	.uleb128 0x22
	.string	"c"
	.byte	0x4
	.byte	0xb5
	.long	0x3b
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.long	.LASF90
	.byte	0x2
	.byte	0x3a
	.long	.LFB37
	.long	.LFE37
	.long	.LLST11
	.byte	0x1
	.long	0x9c4
	.uleb128 0x29
	.long	0x960
	.long	.LBB34
	.long	.LBE34
	.byte	0x2
	.byte	0x3f
	.uleb128 0x2b
	.long	0x96e
	.uleb128 0x2d
	.long	.LBB35
	.long	.LBE35
	.uleb128 0x2e
	.long	0x978
	.long	.LLST12
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2f
	.byte	0x1
	.long	.LASF99
	.byte	0x2
	.byte	0x4a
	.long	.LASF100
	.long	0x71e
	.long	.LFB38
	.long	.LFE38
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x9fe
	.uleb128 0x30
	.long	.LVL17
	.long	0x656
	.uleb128 0x31
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Serial
	.byte	0
	.byte	0
	.uleb128 0x26
	.long	.LASF92
	.byte	0x1
	.long	.LFB40
	.long	.LFE40
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xa35
	.uleb128 0x30
	.long	.LVL18
	.long	0x867
	.uleb128 0x31
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x1
	.byte	0x31
	.uleb128 0x31
	.byte	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x9
	.byte	0xff
	.byte	0
	.byte	0
	.uleb128 0x32
	.long	.LASF101
	.byte	0x2
	.byte	0x45
	.long	0x5d3
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	Serial
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1c
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0xa
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x8
	.byte	0
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x18
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0xa
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x10
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL0
	.long	.LVL1
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL1
	.long	.LFE9
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST1:
	.long	.LVL3
	.long	.LVL4
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL4
	.long	.LFE39
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST2:
	.long	.LVL5
	.long	.LVL8
	.word	0x3
	.byte	0x8
	.byte	0xc6
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL5
	.long	.LVL8
	.word	0x3
	.byte	0x8
	.byte	0xc2
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LVL5
	.long	.LVL8
	.word	0x3
	.byte	0x8
	.byte	0xc1
	.byte	0x9f
	.long	0
	.long	0
.LLST5:
	.long	.LVL5
	.long	.LVL8
	.word	0x3
	.byte	0x8
	.byte	0xc0
	.byte	0x9f
	.long	0
	.long	0
.LLST6:
	.long	.LVL5
	.long	.LVL8
	.word	0x3
	.byte	0x8
	.byte	0xc4
	.byte	0x9f
	.long	0
	.long	0
.LLST7:
	.long	.LVL5
	.long	.LVL8
	.word	0x3
	.byte	0x8
	.byte	0xc5
	.byte	0x9f
	.long	0
	.long	0
.LLST8:
	.long	.LFB36
	.long	.LCFI0
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI0
	.long	.LCFI1
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI1
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI5
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI8
	.long	.LFE36
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	0
	.long	0
.LLST9:
	.long	.LVL10
	.long	.LVL12
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST10:
	.long	.LVL11
	.long	.LVL12
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST11:
	.long	.LFB37
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI10
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI12
	.long	.LCFI13
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI13
	.long	.LCFI14
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI14
	.long	.LCFI15
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI15
	.long	.LCFI16
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI16
	.long	.LCFI17
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI17
	.long	.LFE37
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	0
	.long	0
.LLST12:
	.long	.LVL15
	.long	.LVL16
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x4c
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB9
	.long	.LFE9-.LFB9
	.long	.LFB10
	.long	.LFE10-.LFB10
	.long	.LFB39
	.long	.LFE39-.LFB39
	.long	.LFB36
	.long	.LFE36-.LFB36
	.long	.LFB37
	.long	.LFE37-.LFB37
	.long	.LFB38
	.long	.LFE38-.LFB38
	.long	.LFB40
	.long	.LFE40-.LFB40
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB9
	.long	.LFE9
	.long	.LFB10
	.long	.LFE10
	.long	.LFB39
	.long	.LFE39
	.long	.LFB36
	.long	.LFE36
	.long	.LFB37
	.long	.LFE37
	.long	.LFB38
	.long	.LFE38
	.long	.LFB40
	.long	.LFE40
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF66:
	.string	"_ZN14HardwareSerialC4EPVhS1_S1_S1_S1_S1_"
.LASF74:
	.string	"_ZN5PrintC4Ev"
.LASF73:
	.string	"_ZN5Print5writeEPKcj"
.LASF34:
	.string	"setTimeout"
.LASF49:
	.string	"_ZN6Stream9findUntilEPhjPcj"
.LASF51:
	.string	"_ZN6Stream8parseIntE13LookaheadModec"
.LASF45:
	.string	"findUntil"
.LASF75:
	.string	"availableForWrite"
.LASF14:
	.string	"index"
.LASF33:
	.string	"_ZN6Stream4peekEv"
.LASF9:
	.string	"size_t"
.LASF88:
	.string	"__priority"
.LASF11:
	.string	"SKIP_ALL"
.LASF53:
	.string	"_ZN6Stream10parseFloatE13LookaheadModec"
.LASF98:
	.string	"_ZN14HardwareSerial9availableEv"
.LASF26:
	.string	"peekNextDigit"
.LASF43:
	.string	"_ZN6Stream4findEPhj"
.LASF17:
	.string	"~Stream"
.LASF68:
	.string	"_ZN14HardwareSerial16_rx_complete_irqEv"
.LASF57:
	.string	"readBytesUntil"
.LASF54:
	.string	"readBytes"
.LASF48:
	.string	"_ZN6Stream9findUntilEPcjS0_j"
.LASF2:
	.string	"uint8_t"
.LASF70:
	.string	"_ZN14HardwareSerial17_tx_udr_empty_irqEv"
.LASF20:
	.string	"_ZN6StreamC4EOS_"
.LASF83:
	.string	"ubrrl"
.LASF25:
	.string	"_ZN6Stream9timedPeekEv"
.LASF27:
	.string	"_ZN6Stream13peekNextDigitE13LookaheadModeb"
.LASF79:
	.string	"bool"
.LASF56:
	.string	"_ZN6Stream9readBytesEPhj"
.LASF80:
	.string	"float"
.LASF23:
	.string	"timedPeek"
.LASF52:
	.string	"parseFloat"
.LASF29:
	.string	"read"
.LASF7:
	.string	"long long int"
.LASF46:
	.string	"_ZN6Stream9findUntilEPcS0_"
.LASF71:
	.string	"Print"
.LASF31:
	.string	"_ZN6Stream4readEv"
.LASF5:
	.string	"long int"
.LASF65:
	.string	"HardwareSerial"
.LASF32:
	.string	"peek"
.LASF50:
	.string	"parseInt"
.LASF44:
	.string	"_ZN6Stream4findEc"
.LASF97:
	.string	"MultiTarget"
.LASF39:
	.string	"_ZN6Stream10getTimeoutEv"
.LASF41:
	.string	"_ZN6Stream4findEPh"
.LASF85:
	.string	"ucsrb"
.LASF47:
	.string	"_ZN6Stream9findUntilEPhPc"
.LASF87:
	.string	"__initialize_p"
.LASF93:
	.string	"GNU C++14 5.4.0 -mn-flash=1 -mmcu=avr5 -g2 -Og -std=c++14 -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mn-flash=1 -mno-skip-bug -fno-rtti -fno-enforce-eh-specs -fno-exceptions"
.LASF63:
	.string	"_ZN6Stream9findMultiEPNS_11MultiTargetEi"
.LASF64:
	.string	"rx_buffer_index_t"
.LASF28:
	.string	"available"
.LASF1:
	.string	"unsigned char"
.LASF40:
	.string	"_ZN6Stream4findEPc"
.LASF35:
	.string	"_ZN6StreamC4Ev"
.LASF78:
	.string	"_ZN5Print5flushEv"
.LASF0:
	.string	"signed char"
.LASF99:
	.string	"Serial0_available"
.LASF8:
	.string	"long long unsigned int"
.LASF24:
	.string	"_ZN6Stream9timedReadEv"
.LASF4:
	.string	"unsigned int"
.LASF3:
	.string	"uint16_t"
.LASF62:
	.string	"findMulti"
.LASF61:
	.string	"_ZN6Stream10parseFloatEc"
.LASF76:
	.string	"_ZN5Print17availableForWriteEv"
.LASF101:
	.string	"Serial"
.LASF18:
	.string	"Stream"
.LASF96:
	.string	"LookaheadMode"
.LASF82:
	.string	"ubrrh"
.LASF10:
	.string	"char"
.LASF69:
	.string	"_tx_udr_empty_irq"
.LASF91:
	.string	"__static_initialization_and_destruction_0"
.LASF67:
	.string	"_rx_complete_irq"
.LASF81:
	.string	"this"
.LASF92:
	.string	"_GLOBAL__sub_I___vector_18"
.LASF37:
	.string	"getTimeout"
.LASF38:
	.string	"find"
.LASF77:
	.string	"flush"
.LASF22:
	.string	"timedRead"
.LASF59:
	.string	"_ZN6Stream14readBytesUntilEcPhj"
.LASF60:
	.string	"_ZN6Stream8parseIntEc"
.LASF84:
	.string	"ucsra"
.LASF6:
	.string	"long unsigned int"
.LASF86:
	.string	"ucsrc"
.LASF13:
	.string	"SKIP_WHITESPACE"
.LASF90:
	.string	"__vector_19"
.LASF36:
	.string	"_ZN6Stream10setTimeoutEm"
.LASF15:
	.string	"_timeout"
.LASF94:
	.string	".././HardwareSerial0.cpp"
.LASF42:
	.string	"_ZN6Stream4findEPcj"
.LASF58:
	.string	"_ZN6Stream14readBytesUntilEcPcj"
.LASF72:
	.string	"write"
.LASF21:
	.string	"_ZN6StreamC4ERKS_"
.LASF19:
	.string	"_ZN6StreamD4Ev"
.LASF100:
	.string	"_Z17Serial0_availablev"
.LASF16:
	.string	"_startMillis"
.LASF12:
	.string	"SKIP_NONE"
.LASF89:
	.string	"__vector_18"
.LASF30:
	.string	"_ZN6Stream9availableEv"
.LASF95:
	.string	"D:\\\\Tmp\\\\avr\\\\P015_Watering\\\\WaterWindow\\\\Watering\\\\Uart\\\\Debug"
.LASF55:
	.string	"_ZN6Stream9readBytesEPcj"
	.ident	"GCC: (AVR_8_bit_GNU_Toolchain_3.6.2_1778) 5.4.0"
.global __do_copy_data
.global __do_clear_bss
