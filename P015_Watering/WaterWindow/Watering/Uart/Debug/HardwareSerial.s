	.file	"HardwareSerial.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text._ZN14HardwareSerial9availableEv,"ax",@progbits
.global	_ZN14HardwareSerial9availableEv
	.type	_ZN14HardwareSerial9availableEv, @function
_ZN14HardwareSerial9availableEv:
.LFB48:
	.file 1 ".././HardwareSerial.cpp"
	.loc 1 140 0
	.cfi_startproc
.LVL0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 141 0
	movw r30,r24
	ldd r18,Z+25
	ldi r19,0
	subi r18,-16
	sbci r19,-1
	ldd r24,Z+26
.LVL1:
	movw r20,r18
	sub r20,r24
	sbc r21,__zero_reg__
	movw r24,r20
	.loc 1 142 0
	andi r24,15
	clr r25
	ret
	.cfi_endproc
.LFE48:
	.size	_ZN14HardwareSerial9availableEv, .-_ZN14HardwareSerial9availableEv
	.section	.text._ZN14HardwareSerial4peekEv,"ax",@progbits
.global	_ZN14HardwareSerial4peekEv
	.type	_ZN14HardwareSerial4peekEv, @function
_ZN14HardwareSerial4peekEv:
.LFB49:
	.loc 1 145 0
	.cfi_startproc
.LVL2:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r30,r24
	.loc 1 146 0
	ldd r25,Z+25
	ldd r24,Z+26
.LVL3:
	cp r25,r24
	breq .L4
	.loc 1 149 0
	ldd r24,Z+26
	add r30,r24
	adc r31,__zero_reg__
.LVL4:
	ldd r24,Z+29
	ldi r25,0
	ret
.LVL5:
.L4:
	.loc 1 147 0
	ldi r24,lo8(-1)
	ldi r25,lo8(-1)
	.loc 1 151 0
	ret
	.cfi_endproc
.LFE49:
	.size	_ZN14HardwareSerial4peekEv, .-_ZN14HardwareSerial4peekEv
	.section	.text._ZN14HardwareSerial4readEv,"ax",@progbits
.global	_ZN14HardwareSerial4readEv
	.type	_ZN14HardwareSerial4readEv, @function
_ZN14HardwareSerial4readEv:
.LFB50:
	.loc 1 154 0
	.cfi_startproc
.LVL6:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r30,r24
.LBB14:
	.loc 1 156 0
	ldd r25,Z+25
	ldd r24,Z+26
.LVL7:
	cp r25,r24
	breq .L7
.LBB15:
	.loc 1 159 0
	ldd r24,Z+26
	movw r26,r30
	add r26,r24
	adc r27,__zero_reg__
	adiw r26,29
	ld r24,X
.LVL8:
	.loc 1 160 0
	ldd r25,Z+26
	subi r25,lo8(-(1))
	andi r25,lo8(15)
	std Z+26,r25
	.loc 1 161 0
	ldi r25,0
	ret
.LVL9:
.L7:
.LBE15:
	.loc 1 157 0
	ldi r24,lo8(-1)
	ldi r25,lo8(-1)
.LBE14:
	.loc 1 163 0
	ret
	.cfi_endproc
.LFE50:
	.size	_ZN14HardwareSerial4readEv, .-_ZN14HardwareSerial4readEv
	.section	.text._ZN14HardwareSerial17availableForWriteEv,"ax",@progbits
.global	_ZN14HardwareSerial17availableForWriteEv
	.type	_ZN14HardwareSerial17availableForWriteEv, @function
_ZN14HardwareSerial17availableForWriteEv:
.LFB51:
	.loc 1 166 0
	.cfi_startproc
.LVL10:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 171 0
	movw r30,r24
	ldd r18,Z+27
.LVL11:
	.loc 1 172 0
	ldd r19,Z+28
.LVL12:
	.loc 1 174 0
	cp r18,r19
	brlo .L9
	.loc 1 174 0 is_stmt 0 discriminator 1
	ldi r24,lo8(15)
	ldi r25,0
.LVL13:
	sub r24,r18
	sbc r25,__zero_reg__
	add r24,r19
	adc r25,__zero_reg__
	ret
.LVL14:
.L9:
	.loc 1 175 0 is_stmt 1
	mov r24,r19
.LVL15:
	ldi r25,0
	sub r24,r18
	sbc r25,__zero_reg__
	sbiw r24,1
	.loc 1 176 0
	ret
	.cfi_endproc
.LFE51:
	.size	_ZN14HardwareSerial17availableForWriteEv, .-_ZN14HardwareSerial17availableForWriteEv
	.section	.text._ZN14HardwareSerial5writeEh,"ax",@progbits
.global	_ZN14HardwareSerial5writeEh
	.type	_ZN14HardwareSerial5writeEh, @function
_ZN14HardwareSerial5writeEh:
.LFB53:
	.loc 1 199 0
	.cfi_startproc
.LVL16:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r30,r24
	.loc 1 200 0
	ldi r24,lo8(1)
.LVL17:
	std Z+24,r24
.LBB30:
	.loc 1 205 0
	ldd r25,Z+27
	ldd r24,Z+28
	cpse r25,r24
	rjmp .L26
	.loc 1 205 0 discriminator 1
	ldd r26,Z+16
	ldd r27,Z+17
	.loc 1 205 0 discriminator 1
	ld r24,X
	.loc 1 205 0 discriminator 1
	sbrc r24,5
	rjmp .L27
	.loc 1 205 0 is_stmt 0
	ldi r24,0
	rjmp .L12
.L26:
	ldi r24,0
	rjmp .L12
.L27:
	ldi r24,lo8(1)
.L12:
	.loc 1 205 0 discriminator 6
	tst r24
	breq .L13
.LBB31:
.LBB32:
	.loc 1 214 0 is_stmt 1
	in r25,__SREG__
.LVL18:
.LBB33:
.LBB34:
	.file 2 "d:\\soft\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\avr\\include\\util\\atomic.h"
	.loc 2 50 0
/* #APP */
 ;  50 "d:\soft\7.0\toolchain\avr8\avr8-gnu-toolchain\avr\include\util\atomic.h" 1
	cli
 ;  0 "" 2
/* #NOAPP */
.LBE34:
.LBE33:
	.loc 1 214 0
	ldi r24,lo8(1)
.L15:
.LVL19:
	.loc 1 214 0 is_stmt 0 discriminator 4
	tst r24
	breq .L14
	.loc 1 215 0 is_stmt 1 discriminator 3
	ldd r26,Z+22
	ldd r27,Z+23
	st X,r22
	.loc 1 217 0 discriminator 3
	ldd r26,Z+16
	ldd r27,Z+17
	.loc 1 217 0 discriminator 3
	ld r24,X
.LVL20:
	andi r24,lo8(3)
	ori r24,lo8(64)
	st X,r24
.LVL21:
	.loc 1 214 0 discriminator 3
	ldi r24,0
	rjmp .L15
.LVL22:
.L14:
.LBB35:
.LBB36:
	.loc 2 70 0
	out __SREG__,r25
	.loc 2 71 0
.LVL23:
.LBE36:
.LBE35:
.LBE32:
	.loc 1 222 0
	rjmp .L16
.LVL24:
.L13:
.LBE31:
.LBE30:
	.loc 1 224 0
	ldd r24,Z+27
	ldi r25,0
	adiw r24,1
	andi r24,15
	andi r25,128
	tst r25
	brge .L17
	sbiw r24,1
	ori r24,240
	ori r25,255
	adiw r24,1
.L17:
	mov r25,r24
.LVL25:
.L19:
	.loc 1 228 0
	ldd r24,Z+28
	cpse r25,r24
	rjmp .L18
	.loc 1 229 0
	in __tmp_reg__,__SREG__
	sbrc __tmp_reg__,7
	rjmp .L19
	.loc 1 234 0
	ldd r26,Z+16
	ldd r27,Z+17
	.loc 1 234 0
	ld r24,X
	.loc 1 234 0
	sbrs r24,5
	rjmp .L19
.LVL26:
.LBB37:
.LBB38:
	.file 3 ".././HardwareSerial.h"
	.loc 3 185 0
	ldd r24,Z+28
	movw r26,r30
	add r26,r24
	adc r27,__zero_reg__
	adiw r26,45
	ld r24,X
.LVL27:
	.loc 3 186 0
	ldd r18,Z+28
	ldi r19,0
	subi r18,-1
	sbci r19,-1
	andi r18,15
	andi r19,128
	tst r19
	brge .L21
	subi r18,1
	sbc r19,__zero_reg__
	ori r18,240
	ori r19,255
	subi r18,-1
	sbci r19,-1
.L21:
	std Z+28,r18
	.loc 3 188 0
	ldd r26,Z+22
	ldd r27,Z+23
	st X,r24
	.loc 3 196 0
	ldd r26,Z+16
	ldd r27,Z+17
	.loc 3 196 0
	ld r24,X
.LVL28:
	andi r24,lo8(3)
	ori r24,lo8(64)
	st X,r24
	.loc 3 201 0
	ldd r18,Z+27
	ldd r24,Z+28
	cpse r18,r24
	rjmp .L19
	.loc 3 203 0
	ldd r26,Z+18
	ldd r27,Z+19
	.loc 3 203 0
	ld r24,X
	andi r24,lo8(-33)
	st X,r24
	rjmp .L19
.LVL29:
.L18:
.LBE38:
.LBE37:
	.loc 1 241 0
	ldd r24,Z+27
	movw r26,r30
	add r26,r24
	adc r27,__zero_reg__
	adiw r26,45
	st X,r22
.LBB39:
	.loc 1 246 0
	in r18,__SREG__
.LVL30:
.LBB40:
.LBB41:
	.loc 2 50 0
/* #APP */
 ;  50 "d:\soft\7.0\toolchain\avr8\avr8-gnu-toolchain\avr\include\util\atomic.h" 1
	cli
 ;  0 "" 2
/* #NOAPP */
.LBE41:
.LBE40:
	.loc 1 246 0
	ldi r24,lo8(1)
.L25:
.LVL31:
	.loc 1 246 0 is_stmt 0 discriminator 4
	tst r24
	breq .L24
	.loc 1 247 0 is_stmt 1 discriminator 3
	std Z+27,r25
	.loc 1 248 0 discriminator 3
	ldd r26,Z+18
	ldd r27,Z+19
	.loc 1 248 0 discriminator 3
	ld r24,X
.LVL32:
	ori r24,lo8(32)
	st X,r24
.LVL33:
	.loc 1 246 0 discriminator 3
	ldi r24,0
	rjmp .L25
.LVL34:
.L24:
.LBB42:
.LBB43:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL35:
.L16:
.LBE43:
.LBE42:
.LBE39:
	.loc 1 252 0
	ldi r24,lo8(1)
	ldi r25,0
	ret
	.cfi_endproc
.LFE53:
	.size	_ZN14HardwareSerial5writeEh, .-_ZN14HardwareSerial5writeEh
	.section	.text._ZN14HardwareSerial5flushEv,"ax",@progbits
.global	_ZN14HardwareSerial5flushEv
	.type	_ZN14HardwareSerial5flushEv, @function
_ZN14HardwareSerial5flushEv:
.LFB52:
	.loc 1 179 0
	.cfi_startproc
.LVL36:
	push r28
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	movw r26,r24
	.loc 1 183 0
	adiw r26,24
	ld r24,X
	sbiw r26,24
.LVL37:
	tst r24
	brne .+2
	rjmp .L28
.L32:
	.loc 1 186 0
	adiw r26,18
	ld r30,X+
	ld r31,X
	sbiw r26,18+1
	.loc 1 186 0
	ld r25,Z
	.loc 1 186 0
	sbrc r25,5
	rjmp .L37
	.loc 1 186 0 discriminator 2
	adiw r26,16
	ld r28,X+
	ld r29,X
	sbiw r26,16+1
	.loc 1 186 0 discriminator 2
	ld r25,Y
	.loc 1 186 0 discriminator 2
	sbrc r25,6
	rjmp .L38
	.loc 1 186 0 is_stmt 0
	mov r25,r24
	rjmp .L30
.L37:
	mov r25,r24
	rjmp .L30
.L38:
	ldi r25,0
.L30:
	.loc 1 186 0 is_stmt 1 discriminator 6
	tst r25
	brne .+2
	rjmp .L28
	.loc 1 187 0
	in __tmp_reg__,__SREG__
	sbrc __tmp_reg__,7
	rjmp .L39
	.loc 1 187 0 discriminator 1
	ld r18,Z
	.loc 1 187 0 discriminator 1
	sbrc r18,5
	rjmp .L31
	.loc 1 187 0 is_stmt 0
	ldi r25,0
	rjmp .L31
.L39:
	ldi r25,0
.L31:
	.loc 1 187 0 is_stmt 1 discriminator 6
	tst r25
	breq .L32
	.loc 1 191 0
	adiw r26,16
	ld r30,X+
	ld r31,X
	sbiw r26,16+1
	.loc 1 191 0
	ld r25,Z
	.loc 1 191 0
	sbrs r25,5
	rjmp .L32
.LVL38:
.LBB46:
.LBB47:
	.loc 3 185 0
	adiw r26,28
	ld r25,X
	sbiw r26,28
	movw r30,r26
	add r30,r25
	adc r31,__zero_reg__
	ldd r25,Z+45
.LVL39:
	.loc 3 186 0
	adiw r26,28
	ld r18,X
	sbiw r26,28
	ldi r19,0
	subi r18,-1
	sbci r19,-1
	andi r18,15
	andi r19,128
	tst r19
	brge .L34
	subi r18,1
	sbc r19,__zero_reg__
	ori r18,240
	ori r19,255
	subi r18,-1
	sbci r19,-1
.L34:
	adiw r26,28
	st X,r18
	sbiw r26,28
	.loc 3 188 0
	adiw r26,22
	ld r30,X+
	ld r31,X
	sbiw r26,22+1
	st Z,r25
	.loc 3 196 0
	adiw r26,16
	ld r30,X+
	ld r31,X
	sbiw r26,16+1
	.loc 3 196 0
	ld r25,Z
.LVL40:
	andi r25,lo8(3)
	ori r25,lo8(64)
	st Z,r25
	.loc 3 201 0
	adiw r26,27
	ld r18,X
	sbiw r26,27
	adiw r26,28
	ld r25,X
	sbiw r26,28
	cpse r18,r25
	rjmp .L32
	.loc 3 203 0
	adiw r26,18
	ld r30,X+
	ld r31,X
	sbiw r26,18+1
	.loc 3 203 0
	ld r25,Z
	andi r25,lo8(-33)
	st Z,r25
	rjmp .L32
.LVL41:
.L28:
/* epilogue start */
.LBE47:
.LBE46:
	.loc 1 196 0
	pop r29
	pop r28
	ret
	.cfi_endproc
.LFE52:
	.size	_ZN14HardwareSerial5flushEv, .-_ZN14HardwareSerial5flushEv
	.section	.text._Z14serialEventRunv,"ax",@progbits
	.weak	_Z14serialEventRunv
	.type	_Z14serialEventRunv, @function
_Z14serialEventRunv:
.LFB45:
	.loc 1 63 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 65 0
	ldi r24,lo8(gs(_Z17Serial0_availablev))
	ldi r25,hi8(gs(_Z17Serial0_availablev))
	or r24,r25
	breq .L43
	.loc 1 65 0 is_stmt 0 discriminator 1
	ldi r24,lo8(gs(_Z11serialEventv))
	ldi r25,hi8(gs(_Z11serialEventv))
	or r24,r25
	breq .L44
	.loc 1 65 0 discriminator 3
	call _Z17Serial0_availablev
.LVL42:
	rjmp .L41
.L43:
	.loc 1 65 0
	ldi r24,0
	rjmp .L41
.L44:
	ldi r24,0
.L41:
	.loc 1 65 0 discriminator 8
	cpse r24,__zero_reg__
	.loc 1 65 0 discriminator 9
	call _Z11serialEventv
.LVL43:
.L40:
	ret
	.cfi_endproc
.LFE45:
	.size	_Z14serialEventRunv, .-_Z14serialEventRunv
	.section	.text._ZN14HardwareSerial5beginEmh,"ax",@progbits
.global	_ZN14HardwareSerial5beginEmh
	.type	_ZN14HardwareSerial5beginEmh, @function
_ZN14HardwareSerial5beginEmh:
.LFB46:
	.loc 1 91 0 is_stmt 1
	.cfi_startproc
.LVL44:
	push r11
.LCFI2:
	.cfi_def_cfa_offset 3
	.cfi_offset 11, -2
	push r12
.LCFI3:
	.cfi_def_cfa_offset 4
	.cfi_offset 12, -3
	push r13
.LCFI4:
	.cfi_def_cfa_offset 5
	.cfi_offset 13, -4
	push r14
.LCFI5:
	.cfi_def_cfa_offset 6
	.cfi_offset 14, -5
	push r15
.LCFI6:
	.cfi_def_cfa_offset 7
	.cfi_offset 15, -6
	push r16
.LCFI7:
	.cfi_def_cfa_offset 8
	.cfi_offset 16, -7
	push r17
.LCFI8:
	.cfi_def_cfa_offset 9
	.cfi_offset 17, -8
	push r28
.LCFI9:
	.cfi_def_cfa_offset 10
	.cfi_offset 28, -9
	push r29
.LCFI10:
	.cfi_def_cfa_offset 11
	.cfi_offset 29, -10
/* prologue: function */
/* frame size = 0 */
/* stack size = 9 */
.L__stack_usage = 9
	movw r28,r24
	movw r12,r20
	movw r14,r22
	mov r11,r18
	.loc 1 93 0
	movw r16,r24
	subi r16,-61
	sbci r17,-1
	movw r30,r16
	ld r24,Z
	ldd r25,Z+1
	ldd r26,Z+2
	ldd r27,Z+3
.LVL45:
	movw r22,r24
	movw r24,r26
	lsr r25
	ror r24
	ror r23
	ror r22
	lsr r25
	ror r24
	ror r23
	ror r22
	movw r20,r14
	movw r18,r12
.LVL46:
	call __udivmodsi4
	movw r26,r20
	movw r24,r18
	sbiw r24,1
	sbc r26,__zero_reg__
	sbc r27,__zero_reg__
	lsr r27
	ror r26
	ror r25
	ror r24
	movw r18,r24
.LVL47:
	.loc 1 94 0
	ldd r30,Y+16
	ldd r31,Y+17
	.loc 1 94 0
	ldi r24,lo8(2)
	st Z,r24
	.loc 1 101 0
	movw r30,r16
	ld r24,Z
	ldd r25,Z+1
	ldd r26,Z+2
	ldd r27,Z+3
	cp r24,__zero_reg__
	sbci r25,36
	sbci r26,-12
	cpc r27,__zero_reg__
	brne .L46
	.loc 1 101 0 is_stmt 0 discriminator 1
	cp r12,__zero_reg__
	ldi r20,-31
	cpc r13,r20
	cpc r14,__zero_reg__
	cpc r15,__zero_reg__
.LVL48:
	breq .L47
.L46:
	.loc 1 101 0 discriminator 3
	cp r18,__zero_reg__
	ldi r24,16
	cpc r19,r24
	brlo .L48
.L47:
	.loc 1 103 0 is_stmt 1
	ldd r30,Y+16
	ldd r31,Y+17
	st Z,__zero_reg__
	.loc 1 104 0
	movw r30,r28
	adiw r30,61
	ld r24,Z
	ldd r25,Z+1
	ldd r26,Z+2
	ldd r27,Z+3
	movw r22,r24
	movw r24,r26
	set
	bld __zero_reg__,3-1
	1:
	lsr r25
	ror r24
	ror r23
	ror r22
	lsr __zero_reg__
	brne 1b
	movw r20,r14
	movw r18,r12
	call __udivmodsi4
	movw r26,r20
	movw r24,r18
	sbiw r24,1
	sbc r26,__zero_reg__
	sbc r27,__zero_reg__
	lsr r27
	ror r26
	ror r25
	ror r24
	movw r18,r24
.L48:
.LVL49:
	.loc 1 108 0
	ldd r30,Y+12
	ldd r31,Y+13
	st Z,r19
	.loc 1 109 0
	ldd r30,Y+14
	ldd r31,Y+15
	st Z,r18
	.loc 1 111 0
	std Y+24,__zero_reg__
	.loc 1 117 0
	ldd r30,Y+20
	ldd r31,Y+21
	st Z,r11
	.loc 1 119 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 119 0
	ld r24,Z
	ori r24,lo8(16)
	st Z,r24
	.loc 1 120 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 120 0
	ld r24,Z
	ori r24,lo8(8)
	st Z,r24
	.loc 1 121 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 121 0
	ld r24,Z
	ori r24,lo8(-128)
	st Z,r24
	.loc 1 122 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 122 0
	ld r24,Z
	andi r24,lo8(-33)
	st Z,r24
/* epilogue start */
	.loc 1 123 0
	pop r29
	pop r28
.LVL50:
	pop r17
	pop r16
.LVL51:
	pop r15
	pop r14
	pop r13
	pop r12
.LVL52:
	pop r11
.LVL53:
	ret
	.cfi_endproc
.LFE46:
	.size	_ZN14HardwareSerial5beginEmh, .-_ZN14HardwareSerial5beginEmh
	.section	.text._ZN14HardwareSerial3endEv,"ax",@progbits
.global	_ZN14HardwareSerial3endEv
	.type	_ZN14HardwareSerial3endEv, @function
_ZN14HardwareSerial3endEv:
.LFB47:
	.loc 1 126 0
	.cfi_startproc
.LVL54:
	push r28
.LCFI11:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI12:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	movw r28,r24
	.loc 1 128 0
	ld r30,Y
	ldd r31,Y+1
	ldd __tmp_reg__,Z+6
	ldd r31,Z+7
	mov r30,__tmp_reg__
	icall
.LVL55:
	.loc 1 130 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 130 0
	ld r24,Z
	andi r24,lo8(-17)
	st Z,r24
	.loc 1 131 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 131 0
	ld r24,Z
	andi r24,lo8(-9)
	st Z,r24
	.loc 1 132 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 132 0
	ld r24,Z
	andi r24,lo8(127)
	st Z,r24
	.loc 1 133 0
	ldd r30,Y+18
	ldd r31,Y+19
	.loc 1 133 0
	ld r24,Z
	andi r24,lo8(-33)
	st Z,r24
	.loc 1 136 0
	ldd r24,Y+26
	std Y+25,r24
/* epilogue start */
	.loc 1 137 0
	pop r29
	pop r28
.LVL56:
	ret
	.cfi_endproc
.LFE47:
	.size	_ZN14HardwareSerial3endEv, .-_ZN14HardwareSerial3endEv
	.weak	_ZTV14HardwareSerial
	.section	.rodata._ZTV14HardwareSerial,"aG",@progbits,_ZTV14HardwareSerial,comdat
	.type	_ZTV14HardwareSerial, @object
	.size	_ZTV14HardwareSerial, 18
_ZTV14HardwareSerial:
	.word	0
	.word	0
	.word	gs(_ZN14HardwareSerial5writeEh)
	.word	gs(_ZN5Print5writeEPKhj)
	.word	gs(_ZN14HardwareSerial17availableForWriteEv)
	.word	gs(_ZN14HardwareSerial5flushEv)
	.word	gs(_ZN14HardwareSerial9availableEv)
	.word	gs(_ZN14HardwareSerial4readEv)
	.word	gs(_ZN14HardwareSerial4peekEv)
	.weak	_Z11serialEventv
	.weak	_Z17Serial0_availablev
	.text
.Letext0:
	.file 4 "d:\\soft\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\lib\\gcc\\avr\\5.4.0\\include\\stddef.h"
	.file 5 "d:\\soft\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\avr\\include\\stdint.h"
	.file 6 ".././Stream.h"
	.file 7 ".././Print.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xd8d
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF123
	.byte	0x4
	.long	.LASF124
	.long	.LASF125
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF3
	.byte	0x4
	.byte	0xd8
	.long	0x34
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF0
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.long	.LASF1
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF2
	.uleb128 0x2
	.long	.LASF4
	.byte	0x5
	.byte	0x7e
	.long	0x5b
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF5
	.uleb128 0x2
	.long	.LASF6
	.byte	0x5
	.byte	0x80
	.long	0x34
	.uleb128 0x2
	.long	.LASF7
	.byte	0x5
	.byte	0x82
	.long	0x78
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF8
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF9
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x2
	.long	.LASF11
	.byte	0x5
	.byte	0xbc
	.long	0x6d
	.uleb128 0x5
	.byte	0x2
	.long	0x9e
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF12
	.uleb128 0x6
	.long	.LASF126
	.byte	0x1
	.long	0x5b
	.byte	0x6
	.byte	0x29
	.long	0xc8
	.uleb128 0x7
	.long	.LASF13
	.byte	0
	.uleb128 0x7
	.long	.LASF14
	.byte	0x1
	.uleb128 0x7
	.long	.LASF15
	.byte	0x2
	.byte	0
	.uleb128 0x8
	.long	.LASF20
	.byte	0xc
	.byte	0x6
	.byte	0x31
	.long	0x97e
	.long	0x5d3
	.uleb128 0x9
	.long	.LASF127
	.byte	0x6
	.byte	0x6
	.byte	0x72
	.byte	0x2
	.long	0x110
	.uleb128 0xa
	.string	"str"
	.byte	0x6
	.byte	0x73
	.long	0x5d3
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.string	"len"
	.byte	0x6
	.byte	0x74
	.long	0x29
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0xb
	.long	.LASF16
	.byte	0x6
	.byte	0x75
	.long	0x29
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0xc
	.long	0x97e
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0x1
	.uleb128 0xd
	.long	.LASF17
	.byte	0x6
	.byte	0x34
	.long	0x78
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x2
	.uleb128 0xd
	.long	.LASF18
	.byte	0x6
	.byte	0x35
	.long	0x78
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0x2
	.uleb128 0xe
	.byte	0x1
	.long	.LASF19
	.long	.LASF21
	.byte	0x1
	.byte	0x1
	.long	0x14b
	.long	0x158
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0xf
	.long	0x3b
	.byte	0x1
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.long	.LASF20
	.long	.LASF22
	.byte	0x1
	.byte	0x1
	.long	0x16c
	.long	0x178
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x9f9
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.long	.LASF20
	.long	.LASF23
	.byte	0x1
	.byte	0x1
	.long	0x18c
	.long	0x198
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x9ff
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF24
	.byte	0x6
	.byte	0x36
	.long	.LASF26
	.long	0x3b
	.byte	0x2
	.byte	0x1
	.long	0x1b2
	.long	0x1b9
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF25
	.byte	0x6
	.byte	0x37
	.long	.LASF27
	.long	0x3b
	.byte	0x2
	.byte	0x1
	.long	0x1d3
	.long	0x1da
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF28
	.byte	0x6
	.byte	0x38
	.long	.LASF29
	.long	0x3b
	.byte	0x2
	.byte	0x1
	.long	0x1f4
	.long	0x205
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa5
	.uleb128 0x10
	.long	0x9c5
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF30
	.byte	0x6
	.byte	0x3b
	.long	.LASF32
	.long	0x3b
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.long	0xc8
	.byte	0x1
	.long	0x226
	.long	0x22d
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF31
	.byte	0x6
	.byte	0x3c
	.long	.LASF33
	.long	0x3b
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x5
	.long	0xc8
	.byte	0x1
	.long	0x24e
	.long	0x255
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF34
	.byte	0x6
	.byte	0x3d
	.long	.LASF35
	.long	0x3b
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x6
	.long	0xc8
	.byte	0x1
	.long	0x276
	.long	0x27d
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF20
	.byte	0x6
	.byte	0x3f
	.long	.LASF37
	.byte	0x1
	.long	0x292
	.long	0x299
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF36
	.byte	0x6
	.byte	0x43
	.long	.LASF38
	.byte	0x1
	.long	0x2ae
	.long	0x2ba
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x78
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF39
	.byte	0x6
	.byte	0x44
	.long	.LASF41
	.long	0x78
	.byte	0x1
	.long	0x2d3
	.long	0x2da
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF40
	.byte	0x6
	.byte	0x46
	.long	.LASF42
	.long	0x9c5
	.byte	0x1
	.long	0x2f3
	.long	0x2ff
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x98
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF40
	.byte	0x6
	.byte	0x47
	.long	.LASF43
	.long	0x9c5
	.byte	0x1
	.long	0x318
	.long	0x324
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa0a
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF40
	.byte	0x6
	.byte	0x4a
	.long	.LASF44
	.long	0x9c5
	.byte	0x1
	.long	0x33d
	.long	0x34e
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x98
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF40
	.byte	0x6
	.byte	0x4b
	.long	.LASF45
	.long	0x9c5
	.byte	0x1
	.long	0x367
	.long	0x378
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa0a
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF40
	.byte	0x6
	.byte	0x4e
	.long	.LASF46
	.long	0x9c5
	.byte	0x1
	.long	0x391
	.long	0x39d
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x9e
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF47
	.byte	0x6
	.byte	0x50
	.long	.LASF48
	.long	0x9c5
	.byte	0x1
	.long	0x3b6
	.long	0x3c7
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x98
	.uleb128 0x10
	.long	0x98
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF47
	.byte	0x6
	.byte	0x51
	.long	.LASF49
	.long	0x9c5
	.byte	0x1
	.long	0x3e0
	.long	0x3f1
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa0a
	.uleb128 0x10
	.long	0x98
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF47
	.byte	0x6
	.byte	0x53
	.long	.LASF50
	.long	0x9c5
	.byte	0x1
	.long	0x40a
	.long	0x425
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x98
	.uleb128 0x10
	.long	0x29
	.uleb128 0x10
	.long	0x98
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF47
	.byte	0x6
	.byte	0x54
	.long	.LASF51
	.long	0x9c5
	.byte	0x1
	.long	0x43e
	.long	0x459
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa0a
	.uleb128 0x10
	.long	0x29
	.uleb128 0x10
	.long	0x98
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF52
	.byte	0x6
	.byte	0x56
	.long	.LASF53
	.long	0x42
	.byte	0x1
	.long	0x472
	.long	0x483
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa5
	.uleb128 0x10
	.long	0x9e
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF54
	.byte	0x6
	.byte	0x5d
	.long	.LASF55
	.long	0xa10
	.byte	0x1
	.long	0x49c
	.long	0x4ad
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa5
	.uleb128 0x10
	.long	0x9e
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF56
	.byte	0x6
	.byte	0x60
	.long	.LASF57
	.long	0x29
	.byte	0x1
	.long	0x4c6
	.long	0x4d7
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x98
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF56
	.byte	0x6
	.byte	0x61
	.long	.LASF58
	.long	0x29
	.byte	0x1
	.long	0x4f0
	.long	0x501
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa0a
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF59
	.byte	0x6
	.byte	0x65
	.long	.LASF60
	.long	0x29
	.byte	0x1
	.long	0x51a
	.long	0x530
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x9e
	.uleb128 0x10
	.long	0x98
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF59
	.byte	0x6
	.byte	0x66
	.long	.LASF61
	.long	0x29
	.byte	0x1
	.long	0x549
	.long	0x55f
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x9e
	.uleb128 0x10
	.long	0xa0a
	.uleb128 0x10
	.long	0x29
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF52
	.byte	0x6
	.byte	0x6c
	.long	.LASF62
	.long	0x42
	.byte	0x2
	.byte	0x1
	.long	0x579
	.long	0x585
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x9e
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF54
	.byte	0x6
	.byte	0x6d
	.long	.LASF63
	.long	0xa10
	.byte	0x2
	.byte	0x1
	.long	0x59f
	.long	0x5ab
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0x9e
	.byte	0
	.uleb128 0x15
	.byte	0x1
	.long	.LASF64
	.byte	0x6
	.byte	0x7a
	.long	.LASF65
	.long	0x3b
	.byte	0x2
	.byte	0x1
	.long	0x5c1
	.uleb128 0xf
	.long	0x9f3
	.byte	0x1
	.uleb128 0x10
	.long	0xa17
	.uleb128 0x10
	.long	0x3b
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.long	0x5d9
	.uleb128 0x16
	.long	0x9e
	.uleb128 0x2
	.long	.LASF66
	.byte	0x3
	.byte	0x40
	.long	0x50
	.uleb128 0x2
	.long	.LASF67
	.byte	0x3
	.byte	0x45
	.long	0x50
	.uleb128 0x8
	.long	.LASF68
	.byte	0x41
	.byte	0x3
	.byte	0x6a
	.long	0x97e
	.long	0x97e
	.uleb128 0x17
	.byte	0x3
	.byte	0x6a
	.long	0x988
	.uleb128 0xc
	.long	0xc8
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0x1
	.uleb128 0xd
	.long	.LASF69
	.byte	0x3
	.byte	0x6d
	.long	0x9c0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0x2
	.uleb128 0xd
	.long	.LASF70
	.byte	0x3
	.byte	0x6e
	.long	0x9c0
	.byte	0x2
	.byte	0x23
	.uleb128 0xe
	.byte	0x2
	.uleb128 0xd
	.long	.LASF71
	.byte	0x3
	.byte	0x6f
	.long	0x9c0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0x2
	.uleb128 0xd
	.long	.LASF72
	.byte	0x3
	.byte	0x70
	.long	0x9c0
	.byte	0x2
	.byte	0x23
	.uleb128 0x12
	.byte	0x2
	.uleb128 0xd
	.long	.LASF73
	.byte	0x3
	.byte	0x71
	.long	0x9c0
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.byte	0x2
	.uleb128 0xd
	.long	.LASF74
	.byte	0x3
	.byte	0x72
	.long	0x9c0
	.byte	0x2
	.byte	0x23
	.uleb128 0x16
	.byte	0x2
	.uleb128 0xd
	.long	.LASF75
	.byte	0x3
	.byte	0x74
	.long	0x9c5
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.byte	0x2
	.uleb128 0xd
	.long	.LASF76
	.byte	0x3
	.byte	0x76
	.long	0x9cc
	.byte	0x2
	.byte	0x23
	.uleb128 0x19
	.byte	0x2
	.uleb128 0xd
	.long	.LASF77
	.byte	0x3
	.byte	0x77
	.long	0x9cc
	.byte	0x2
	.byte	0x23
	.uleb128 0x1a
	.byte	0x2
	.uleb128 0xd
	.long	.LASF78
	.byte	0x3
	.byte	0x78
	.long	0x9d1
	.byte	0x2
	.byte	0x23
	.uleb128 0x1b
	.byte	0x2
	.uleb128 0xd
	.long	.LASF79
	.byte	0x3
	.byte	0x79
	.long	0x9d1
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.byte	0x2
	.uleb128 0xd
	.long	.LASF80
	.byte	0x3
	.byte	0x7e
	.long	0x9d6
	.byte	0x2
	.byte	0x23
	.uleb128 0x1d
	.byte	0x2
	.uleb128 0xd
	.long	.LASF81
	.byte	0x3
	.byte	0x7f
	.long	0x9d6
	.byte	0x2
	.byte	0x23
	.uleb128 0x2d
	.byte	0x2
	.uleb128 0xd
	.long	.LASF82
	.byte	0x3
	.byte	0x80
	.long	0x8d
	.byte	0x2
	.byte	0x23
	.uleb128 0x3d
	.byte	0x2
	.uleb128 0x13
	.byte	0x1
	.long	.LASF68
	.byte	0x3
	.byte	0x82
	.long	.LASF83
	.byte	0x1
	.long	0x6fb
	.long	0x720
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x9b5
	.uleb128 0x10
	.long	0x9b5
	.uleb128 0x10
	.long	0x9b5
	.uleb128 0x10
	.long	0x9b5
	.uleb128 0x10
	.long	0x9b5
	.uleb128 0x10
	.long	0x9b5
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF84
	.byte	0x3
	.byte	0x8d
	.long	.LASF85
	.byte	0x1
	.long	0x735
	.long	0x741
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x8d
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF86
	.byte	0x3
	.byte	0x91
	.long	.LASF87
	.byte	0x1
	.long	0x756
	.long	0x762
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x78
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF86
	.byte	0x1
	.byte	0x5a
	.long	.LASF88
	.byte	0x1
	.long	0x777
	.long	0x788
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x78
	.uleb128 0x10
	.long	0x50
	.byte	0
	.uleb128 0x18
	.byte	0x1
	.string	"end"
	.byte	0x1
	.byte	0x7d
	.long	.LASF128
	.byte	0x1
	.long	0x79d
	.long	0x7a4
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF30
	.byte	0x1
	.byte	0x8b
	.long	.LASF89
	.long	0x3b
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x4
	.long	0x5f4
	.byte	0x1
	.long	0x7c5
	.long	0x7cc
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF34
	.byte	0x1
	.byte	0x90
	.long	.LASF90
	.long	0x3b
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x6
	.long	0x5f4
	.byte	0x1
	.long	0x7ed
	.long	0x7f4
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF31
	.byte	0x1
	.byte	0x99
	.long	.LASF91
	.long	0x3b
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x5
	.long	0x5f4
	.byte	0x1
	.long	0x815
	.long	0x81c
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF92
	.byte	0x1
	.byte	0xa5
	.long	.LASF93
	.long	0x3b
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x2
	.long	0x5f4
	.byte	0x1
	.long	0x83d
	.long	0x844
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x19
	.byte	0x1
	.long	.LASF129
	.byte	0x1
	.byte	0xb2
	.long	.LASF130
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0x3
	.long	0x5f4
	.byte	0x1
	.long	0x861
	.long	0x868
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF94
	.byte	0x1
	.byte	0xc6
	.long	.LASF95
	.long	0x29
	.byte	0x1
	.byte	0x2
	.byte	0x10
	.uleb128 0
	.long	0x5f4
	.byte	0x1
	.long	0x889
	.long	0x895
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x50
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF94
	.byte	0x3
	.byte	0x9a
	.long	.LASF96
	.long	0x29
	.byte	0x1
	.long	0x8ae
	.long	0x8ba
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x78
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF94
	.byte	0x3
	.byte	0x9b
	.long	.LASF97
	.long	0x29
	.byte	0x1
	.long	0x8d3
	.long	0x8df
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x42
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF94
	.byte	0x3
	.byte	0x9c
	.long	.LASF98
	.long	0x29
	.byte	0x1
	.long	0x8f8
	.long	0x904
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x34
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF94
	.byte	0x3
	.byte	0x9d
	.long	.LASF99
	.long	0x29
	.byte	0x1
	.long	0x91d
	.long	0x929
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.uleb128 0x10
	.long	0x3b
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.long	.LASF100
	.byte	0x3
	.byte	0x9f
	.long	.LASF101
	.long	0x9c5
	.byte	0x1
	.long	0x942
	.long	0x949
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.long	.LASF102
	.byte	0x3
	.byte	0xa2
	.long	.LASF103
	.byte	0x1
	.long	0x95e
	.long	0x965
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF104
	.byte	0x3
	.byte	0xb6
	.long	.LASF131
	.byte	0x1
	.long	0x976
	.uleb128 0xf
	.long	0x9ed
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x1b
	.long	.LASF132
	.byte	0x1
	.long	0x9af
	.uleb128 0x1c
	.byte	0x1
	.long	.LASF94
	.byte	0x7
	.byte	0x38
	.long	.LASF105
	.long	0x29
	.byte	0x1
	.long	0x99d
	.uleb128 0xf
	.long	0x9af
	.byte	0x1
	.uleb128 0x10
	.long	0x5d3
	.uleb128 0x10
	.long	0x29
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.long	0x97e
	.uleb128 0x5
	.byte	0x2
	.long	0x9bb
	.uleb128 0x1d
	.long	0x50
	.uleb128 0x16
	.long	0x9b5
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.long	.LASF106
	.uleb128 0x1d
	.long	0x5e9
	.uleb128 0x1d
	.long	0x5de
	.uleb128 0x1e
	.long	0x5b
	.long	0x9e6
	.uleb128 0x1f
	.long	0x9e6
	.byte	0xf
	.byte	0
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF107
	.uleb128 0x5
	.byte	0x2
	.long	0x5f4
	.uleb128 0x5
	.byte	0x2
	.long	0xc8
	.uleb128 0x20
	.byte	0x2
	.long	0xc8
	.uleb128 0x20
	.byte	0x2
	.long	0xa05
	.uleb128 0x16
	.long	0xc8
	.uleb128 0x5
	.byte	0x2
	.long	0x50
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.long	.LASF108
	.uleb128 0x5
	.byte	0x2
	.long	0xd8
	.uleb128 0x21
	.long	.LASF133
	.byte	0x2
	.byte	0x30
	.long	0x50
	.byte	0x3
	.uleb128 0x22
	.long	.LASF134
	.byte	0x2
	.byte	0x44
	.byte	0x3
	.long	0xa41
	.uleb128 0x23
	.string	"__s"
	.byte	0x2
	.byte	0x44
	.long	0xa41
	.byte	0
	.uleb128 0x5
	.byte	0x2
	.long	0xa47
	.uleb128 0x16
	.long	0x50
	.uleb128 0x24
	.long	0x7a4
	.long	.LFB48
	.long	.LFE48
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	0xa66
	.byte	0x1
	.long	0xa75
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST0
	.byte	0
	.uleb128 0x16
	.long	0x9ed
	.uleb128 0x24
	.long	0x7cc
	.long	.LFB49
	.long	.LFE49
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	0xa94
	.byte	0x1
	.long	0xaa3
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST1
	.byte	0
	.uleb128 0x24
	.long	0x7f4
	.long	.LFB50
	.long	.LFE50
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	0xabd
	.byte	0x1
	.long	0xae3
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST2
	.uleb128 0x26
	.long	.LBB15
	.long	.LBE15
	.uleb128 0x27
	.string	"c"
	.byte	0x1
	.byte	0x9f
	.long	0x5b
	.long	.LLST3
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	0x81c
	.long	.LFB51
	.long	.LFE51
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	0xafd
	.byte	0x1
	.long	0xb26
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST4
	.uleb128 0x28
	.long	.LASF110
	.byte	0x1
	.byte	0xa7
	.long	0x5de
	.byte	0x1
	.byte	0x62
	.uleb128 0x28
	.long	.LASF111
	.byte	0x1
	.byte	0xa8
	.long	0x5de
	.byte	0x1
	.byte	0x63
	.byte	0
	.uleb128 0x29
	.long	0x965
	.byte	0x3
	.long	0xb34
	.long	0xb48
	.uleb128 0x2a
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.uleb128 0x2b
	.string	"c"
	.byte	0x3
	.byte	0xb9
	.long	0x5b
	.byte	0
	.uleb128 0x24
	.long	0x868
	.long	.LFB53
	.long	.LFE53
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	0xb62
	.byte	0x1
	.long	0xc59
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST5
	.uleb128 0x2c
	.string	"c"
	.byte	0x1
	.byte	0xc6
	.long	0x50
	.byte	0x1
	.byte	0x66
	.uleb128 0x2b
	.string	"i"
	.byte	0x1
	.byte	0xe0
	.long	0x5de
	.uleb128 0x2d
	.long	.LBB32
	.long	.LBE32
	.long	0xbd8
	.uleb128 0x2e
	.long	.LASF112
	.byte	0x1
	.byte	0xd6
	.long	0x50
	.long	.LLST6
	.uleb128 0x2e
	.long	.LASF113
	.byte	0x1
	.byte	0xd6
	.long	0x50
	.long	.LLST7
	.uleb128 0x2f
	.long	0xa1d
	.long	.LBB33
	.long	.LBE33
	.byte	0x1
	.byte	0xd6
	.uleb128 0x30
	.long	0xa29
	.long	.LBB35
	.long	.LBE35
	.byte	0x1
	.byte	0xd6
	.uleb128 0x31
	.long	0xa35
	.long	.LLST8
	.byte	0
	.byte	0
	.uleb128 0x32
	.long	0xb26
	.long	.LBB37
	.long	.LBE37
	.byte	0x1
	.byte	0xeb
	.long	0xc08
	.uleb128 0x31
	.long	0xb34
	.long	.LLST9
	.uleb128 0x26
	.long	.LBB38
	.long	.LBE38
	.uleb128 0x33
	.long	0xb3e
	.long	.LLST10
	.byte	0
	.byte	0
	.uleb128 0x26
	.long	.LBB39
	.long	.LBE39
	.uleb128 0x2e
	.long	.LASF112
	.byte	0x1
	.byte	0xf6
	.long	0x50
	.long	.LLST11
	.uleb128 0x2e
	.long	.LASF113
	.byte	0x1
	.byte	0xf6
	.long	0x50
	.long	.LLST12
	.uleb128 0x2f
	.long	0xa1d
	.long	.LBB40
	.long	.LBE40
	.byte	0x1
	.byte	0xf6
	.uleb128 0x30
	.long	0xa29
	.long	.LBB42
	.long	.LBE42
	.byte	0x1
	.byte	0xf6
	.uleb128 0x31
	.long	0xa35
	.long	.LLST13
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x34
	.long	0x844
	.long	.LFB52
	.long	.LFE52
	.long	.LLST14
	.long	0xc73
	.byte	0x1
	.long	0xcae
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST15
	.uleb128 0x30
	.long	0xb26
	.long	.LBB46
	.long	.LBE46
	.byte	0x1
	.byte	0xc0
	.uleb128 0x31
	.long	0xb34
	.long	.LLST16
	.uleb128 0x26
	.long	.LBB47
	.long	.LBE47
	.uleb128 0x33
	.long	0xb3e
	.long	.LLST17
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x35
	.byte	0x1
	.long	.LASF114
	.byte	0x1
	.byte	0x3e
	.long	.LASF115
	.long	.LFB45
	.long	.LFE45
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xcde
	.uleb128 0x36
	.long	.LVL42
	.long	0xd6e
	.uleb128 0x36
	.long	.LVL43
	.long	0xd7f
	.byte	0
	.uleb128 0x34
	.long	0x762
	.long	.LFB46
	.long	.LFE46
	.long	.LLST18
	.long	0xcf8
	.byte	0x1
	.long	0xd34
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST19
	.uleb128 0x37
	.long	.LASF116
	.byte	0x1
	.byte	0x5a
	.long	0x78
	.long	.LLST20
	.uleb128 0x37
	.long	.LASF117
	.byte	0x1
	.byte	0x5a
	.long	0x50
	.long	.LLST21
	.uleb128 0x2e
	.long	.LASF118
	.byte	0x1
	.byte	0x5d
	.long	0x62
	.long	.LLST22
	.byte	0
	.uleb128 0x34
	.long	0x788
	.long	.LFB47
	.long	.LFE47
	.long	.LLST23
	.long	0xd4e
	.byte	0x1
	.long	0xd6e
	.uleb128 0x25
	.long	.LASF109
	.long	0xa75
	.byte	0x1
	.long	.LLST24
	.uleb128 0x38
	.long	.LVL55
	.uleb128 0x39
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x8c
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x3a
	.byte	0x1
	.byte	0x1
	.long	.LASF119
	.long	.LASF121
	.byte	0x1
	.byte	0x2c
	.long	.LASF119
	.uleb128 0x3a
	.byte	0x1
	.byte	0x1
	.long	.LASF120
	.long	.LASF122
	.byte	0x1
	.byte	0x2b
	.long	.LASF120
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
	.uleb128 0x3
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
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x19
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
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x64
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x10
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
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
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x1d
	.byte	0
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
	.uleb128 0x30
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
	.uleb128 0x31
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x32
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x36
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x38
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x3a
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
	.long	.LFE48
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST1:
	.long	.LVL2
	.long	.LVL3
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL3
	.long	.LVL4
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	.LVL4
	.long	.LVL5
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	.LVL5
	.long	.LFE49
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST2:
	.long	.LVL6
	.long	.LVL7
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL7
	.long	.LFE50
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST3:
	.long	.LVL8
	.long	.LVL9
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST4:
	.long	.LVL10
	.long	.LVL13
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL13
	.long	.LVL14
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	.LVL14
	.long	.LVL15
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL15
	.long	.LFE51
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST5:
	.long	.LVL16
	.long	.LVL17
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL17
	.long	.LFE53
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST6:
	.long	.LVL18
	.long	.LVL23
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST7:
	.long	.LVL19
	.long	.LVL20
	.word	0x1
	.byte	0x68
	.long	.LVL21
	.long	.LVL22
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL22
	.long	.LVL24
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST8:
	.long	.LVL22
	.long	.LVL23
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2961
	.sleb128 0
	.long	0
	.long	0
.LLST9:
	.long	.LVL26
	.long	.LVL29
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST10:
	.long	.LVL27
	.long	.LVL28
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST11:
	.long	.LVL30
	.long	.LVL35
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST12:
	.long	.LVL31
	.long	.LVL32
	.word	0x1
	.byte	0x68
	.long	.LVL33
	.long	.LVL34
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL34
	.long	.LVL35
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST13:
	.long	.LVL34
	.long	.LVL35
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3089
	.sleb128 0
	.long	0
	.long	0
.LLST14:
	.long	.LFB52
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
	.long	.LFE52
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST15:
	.long	.LVL36
	.long	.LVL37
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL37
	.long	.LFE52
	.word	0x6
	.byte	0x6a
	.byte	0x93
	.uleb128 0x1
	.byte	0x6b
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST16:
	.long	.LVL38
	.long	.LVL41
	.word	0x6
	.byte	0x6a
	.byte	0x93
	.uleb128 0x1
	.byte	0x6b
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST17:
	.long	.LVL39
	.long	.LVL40
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST18:
	.long	.LFB46
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI5
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI8
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI10
	.long	.LFE46
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	0
	.long	0
.LLST19:
	.long	.LVL44
	.long	.LVL45
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL45
	.long	.LVL50
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL50
	.long	.LVL51
	.word	0x3
	.byte	0x80
	.sleb128 -61
	.byte	0x9f
	.long	.LVL51
	.long	.LFE46
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST20:
	.long	.LVL44
	.long	.LVL48
	.word	0xc
	.byte	0x64
	.byte	0x93
	.uleb128 0x1
	.byte	0x65
	.byte	0x93
	.uleb128 0x1
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.long	.LVL48
	.long	.LVL52
	.word	0xc
	.byte	0x5c
	.byte	0x93
	.uleb128 0x1
	.byte	0x5d
	.byte	0x93
	.uleb128 0x1
	.byte	0x5e
	.byte	0x93
	.uleb128 0x1
	.byte	0x5f
	.byte	0x93
	.uleb128 0x1
	.long	.LVL52
	.long	.LFE46
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x64
	.byte	0x9f
	.long	0
	.long	0
.LLST21:
	.long	.LVL44
	.long	.LVL46
	.word	0x1
	.byte	0x62
	.long	.LVL46
	.long	.LVL53
	.word	0x1
	.byte	0x5b
	.long	.LVL53
	.long	.LFE46
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x62
	.byte	0x9f
	.long	0
	.long	0
.LLST22:
	.long	.LVL49
	.long	.LFE46
	.word	0x6
	.byte	0x62
	.byte	0x93
	.uleb128 0x1
	.byte	0x63
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST23:
	.long	.LFB47
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI12
	.long	.LFE47
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST24:
	.long	.LVL54
	.long	.LVL55-1
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL55-1
	.long	.LVL56
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL56
	.long	.LFE47
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x5c
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB48
	.long	.LFE48-.LFB48
	.long	.LFB49
	.long	.LFE49-.LFB49
	.long	.LFB50
	.long	.LFE50-.LFB50
	.long	.LFB51
	.long	.LFE51-.LFB51
	.long	.LFB53
	.long	.LFE53-.LFB53
	.long	.LFB52
	.long	.LFE52-.LFB52
	.long	.LFB45
	.long	.LFE45-.LFB45
	.long	.LFB46
	.long	.LFE46-.LFB46
	.long	.LFB47
	.long	.LFE47-.LFB47
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB48
	.long	.LFE48
	.long	.LFB49
	.long	.LFE49
	.long	.LFB50
	.long	.LFE50
	.long	.LFB51
	.long	.LFE51
	.long	.LFB53
	.long	.LFE53
	.long	.LFB52
	.long	.LFE52
	.long	.LFB45
	.long	.LFE45
	.long	.LFB46
	.long	.LFE46
	.long	.LFB47
	.long	.LFE47
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF120:
	.string	"_Z11serialEventv"
.LASF104:
	.string	"_tx_udr_empty_irq"
.LASF3:
	.string	"size_t"
.LASF101:
	.string	"_ZN14HardwareSerialcvbEv"
.LASF67:
	.string	"rx_buffer_index_t"
.LASF64:
	.string	"findMulti"
.LASF46:
	.string	"_ZN6Stream4findEc"
.LASF18:
	.string	"_startMillis"
.LASF134:
	.string	"__iRestore"
.LASF28:
	.string	"peekNextDigit"
.LASF10:
	.string	"long long unsigned int"
.LASF81:
	.string	"_tx_buffer"
.LASF70:
	.string	"_ubrrl"
.LASF68:
	.string	"HardwareSerial"
.LASF130:
	.string	"_ZN14HardwareSerial5flushEv"
.LASF79:
	.string	"_tx_buffer_tail"
.LASF44:
	.string	"_ZN6Stream4findEPcj"
.LASF9:
	.string	"long long int"
.LASF2:
	.string	"signed char"
.LASF20:
	.string	"Stream"
.LASF123:
	.string	"GNU C++14 5.4.0 -mn-flash=1 -mmcu=avr5 -g2 -Og -std=c++14 -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mn-flash=1 -mno-skip-bug -fno-rtti -fno-enforce-eh-specs -fno-exceptions"
.LASF50:
	.string	"_ZN6Stream9findUntilEPcjS0_j"
.LASF1:
	.string	"long int"
.LASF17:
	.string	"_timeout"
.LASF49:
	.string	"_ZN6Stream9findUntilEPhPc"
.LASF29:
	.string	"_ZN6Stream13peekNextDigitE13LookaheadModeb"
.LASF6:
	.string	"uint16_t"
.LASF122:
	.string	"serialEvent"
.LASF74:
	.string	"_udr"
.LASF109:
	.string	"this"
.LASF115:
	.string	"_Z14serialEventRunv"
.LASF127:
	.string	"MultiTarget"
.LASF11:
	.string	"uint_least32_t"
.LASF113:
	.string	"__ToDo"
.LASF52:
	.string	"parseInt"
.LASF73:
	.string	"_ucsrc"
.LASF59:
	.string	"readBytesUntil"
.LASF0:
	.string	"unsigned int"
.LASF55:
	.string	"_ZN6Stream10parseFloatE13LookaheadModec"
.LASF86:
	.string	"begin"
.LASF8:
	.string	"long unsigned int"
.LASF38:
	.string	"_ZN6Stream10setTimeoutEm"
.LASF95:
	.string	"_ZN14HardwareSerial5writeEh"
.LASF99:
	.string	"_ZN14HardwareSerial5writeEi"
.LASF42:
	.string	"_ZN6Stream4findEPc"
.LASF112:
	.string	"sreg_save"
.LASF97:
	.string	"_ZN14HardwareSerial5writeEl"
.LASF34:
	.string	"peek"
.LASF43:
	.string	"_ZN6Stream4findEPh"
.LASF121:
	.string	"Serial0_available"
.LASF88:
	.string	"_ZN14HardwareSerial5beginEmh"
.LASF61:
	.string	"_ZN6Stream14readBytesUntilEcPhj"
.LASF133:
	.string	"__iCliRetVal"
.LASF32:
	.string	"_ZN6Stream9availableEv"
.LASF93:
	.string	"_ZN14HardwareSerial17availableForWriteEv"
.LASF35:
	.string	"_ZN6Stream4peekEv"
.LASF106:
	.string	"bool"
.LASF92:
	.string	"availableForWrite"
.LASF54:
	.string	"parseFloat"
.LASF77:
	.string	"_rx_buffer_tail"
.LASF62:
	.string	"_ZN6Stream8parseIntEc"
.LASF82:
	.string	"_f_cpu"
.LASF94:
	.string	"write"
.LASF114:
	.string	"serialEventRun"
.LASF111:
	.string	"tail"
.LASF103:
	.string	"_ZN14HardwareSerial16_rx_complete_irqEv"
.LASF69:
	.string	"_ubrrh"
.LASF48:
	.string	"_ZN6Stream9findUntilEPcS0_"
.LASF98:
	.string	"_ZN14HardwareSerial5writeEj"
.LASF65:
	.string	"_ZN6Stream9findMultiEPNS_11MultiTargetEi"
.LASF22:
	.string	"_ZN6StreamC4EOS_"
.LASF96:
	.string	"_ZN14HardwareSerial5writeEm"
.LASF27:
	.string	"_ZN6Stream9timedPeekEv"
.LASF25:
	.string	"timedPeek"
.LASF83:
	.string	"_ZN14HardwareSerialC4EPVhS1_S1_S1_S1_S1_"
.LASF36:
	.string	"setTimeout"
.LASF41:
	.string	"_ZN6Stream10getTimeoutEv"
.LASF19:
	.string	"~Stream"
.LASF30:
	.string	"available"
.LASF84:
	.string	"set_f_cpu"
.LASF5:
	.string	"unsigned char"
.LASF58:
	.string	"_ZN6Stream9readBytesEPhj"
.LASF78:
	.string	"_tx_buffer_head"
.LASF56:
	.string	"readBytes"
.LASF33:
	.string	"_ZN6Stream4readEv"
.LASF21:
	.string	"_ZN6StreamD4Ev"
.LASF85:
	.string	"_ZN14HardwareSerial9set_f_cpuEm"
.LASF131:
	.string	"_ZN14HardwareSerial17_tx_udr_empty_irqEv"
.LASF110:
	.string	"head"
.LASF7:
	.string	"uint32_t"
.LASF116:
	.string	"baud"
.LASF105:
	.string	"_ZN5Print5writeEPKcj"
.LASF125:
	.string	"D:\\\\Tmp\\\\avr\\\\P015_Watering\\\\WaterWindow\\\\Watering\\\\Uart\\\\Debug"
.LASF12:
	.string	"char"
.LASF126:
	.string	"LookaheadMode"
.LASF124:
	.string	".././HardwareSerial.cpp"
.LASF117:
	.string	"config"
.LASF91:
	.string	"_ZN14HardwareSerial4readEv"
.LASF16:
	.string	"index"
.LASF102:
	.string	"_rx_complete_irq"
.LASF71:
	.string	"_ucsra"
.LASF72:
	.string	"_ucsrb"
.LASF37:
	.string	"_ZN6StreamC4Ev"
.LASF80:
	.string	"_rx_buffer"
.LASF45:
	.string	"_ZN6Stream4findEPhj"
.LASF87:
	.string	"_ZN14HardwareSerial5beginEm"
.LASF24:
	.string	"timedRead"
.LASF26:
	.string	"_ZN6Stream9timedReadEv"
.LASF132:
	.string	"Print"
.LASF90:
	.string	"_ZN14HardwareSerial4peekEv"
.LASF128:
	.string	"_ZN14HardwareSerial3endEv"
.LASF118:
	.string	"baud_setting"
.LASF89:
	.string	"_ZN14HardwareSerial9availableEv"
.LASF39:
	.string	"getTimeout"
.LASF129:
	.string	"flush"
.LASF13:
	.string	"SKIP_ALL"
.LASF100:
	.string	"operator bool"
.LASF66:
	.string	"tx_buffer_index_t"
.LASF60:
	.string	"_ZN6Stream14readBytesUntilEcPcj"
.LASF15:
	.string	"SKIP_WHITESPACE"
.LASF75:
	.string	"_written"
.LASF4:
	.string	"uint8_t"
.LASF108:
	.string	"float"
.LASF107:
	.string	"sizetype"
.LASF51:
	.string	"_ZN6Stream9findUntilEPhjPcj"
.LASF31:
	.string	"read"
.LASF40:
	.string	"find"
.LASF53:
	.string	"_ZN6Stream8parseIntE13LookaheadModec"
.LASF119:
	.string	"_Z17Serial0_availablev"
.LASF23:
	.string	"_ZN6StreamC4ERKS_"
.LASF14:
	.string	"SKIP_NONE"
.LASF47:
	.string	"findUntil"
.LASF63:
	.string	"_ZN6Stream10parseFloatEc"
.LASF76:
	.string	"_rx_buffer_head"
.LASF57:
	.string	"_ZN6Stream9readBytesEPcj"
	.ident	"GCC: (AVR_8_bit_GNU_Toolchain_3.6.2_1778) 5.4.0"
.global __do_copy_data
