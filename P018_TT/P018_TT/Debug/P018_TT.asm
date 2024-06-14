
P018_TT.elf:     file format elf32-avr

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .data         00000000  00800100  00800100  0000017a  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  1 .text         00000106  00000000  00000000  00000074  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .bss          00000001  00800100  00800100  0000017a  2**0
                  ALLOC
  3 .comment      00000030  00000000  00000000  0000017a  2**0
                  CONTENTS, READONLY
  4 .note.gnu.avr.deviceinfo 00000040  00000000  00000000  000001ac  2**2
                  CONTENTS, READONLY
  5 .debug_aranges 00000030  00000000  00000000  000001ec  2**0
                  CONTENTS, READONLY, DEBUGGING
  6 .debug_info   000006d5  00000000  00000000  0000021c  2**0
                  CONTENTS, READONLY, DEBUGGING
  7 .debug_abbrev 00000646  00000000  00000000  000008f1  2**0
                  CONTENTS, READONLY, DEBUGGING
  8 .debug_line   00000201  00000000  00000000  00000f37  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .debug_frame  00000058  00000000  00000000  00001138  2**2
                  CONTENTS, READONLY, DEBUGGING
 10 .debug_str    00000379  00000000  00000000  00001190  2**0
                  CONTENTS, READONLY, DEBUGGING
 11 .debug_loc    00000049  00000000  00000000  00001509  2**0
                  CONTENTS, READONLY, DEBUGGING
 12 .debug_ranges 00000020  00000000  00000000  00001552  2**0
                  CONTENTS, READONLY, DEBUGGING

Disassembly of section .text:

00000000 <__vectors>:
   0:	0c 94 34 00 	jmp	0x68	; 0x68 <__ctors_end>
   4:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
   8:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
   c:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  10:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  14:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  18:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  1c:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  20:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  24:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  28:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  2c:	0c 94 48 00 	jmp	0x90	; 0x90 <__vector_11>
  30:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  34:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  38:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  3c:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  40:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  44:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  48:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  4c:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  50:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  54:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  58:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  5c:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  60:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>
  64:	0c 94 46 00 	jmp	0x8c	; 0x8c <__bad_interrupt>

00000068 <__ctors_end>:
  68:	11 24       	eor	r1, r1
  6a:	1f be       	out	0x3f, r1	; 63
  6c:	cf ef       	ldi	r28, 0xFF	; 255
  6e:	d8 e0       	ldi	r29, 0x08	; 8
  70:	de bf       	out	0x3e, r29	; 62
  72:	cd bf       	out	0x3d, r28	; 61

00000074 <__do_clear_bss>:
  74:	21 e0       	ldi	r18, 0x01	; 1
  76:	a0 e0       	ldi	r26, 0x00	; 0
  78:	b1 e0       	ldi	r27, 0x01	; 1
  7a:	01 c0       	rjmp	.+2      	; 0x7e <.do_clear_bss_start>

0000007c <.do_clear_bss_loop>:
  7c:	1d 92       	st	X+, r1

0000007e <.do_clear_bss_start>:
  7e:	a1 30       	cpi	r26, 0x01	; 1
  80:	b2 07       	cpc	r27, r18
  82:	e1 f7       	brne	.-8      	; 0x7c <.do_clear_bss_loop>
  84:	0e 94 5c 00 	call	0xb8	; 0xb8 <main>
  88:	0c 94 81 00 	jmp	0x102	; 0x102 <_exit>

0000008c <__bad_interrupt>:
  8c:	0c 94 00 00 	jmp	0	; 0x0 <__vectors>

00000090 <__vector_11>:
	OCR1AL = 0b10010010; //записываем в регистр число для сравнения
	TCCR1B |= (1<<CS12);//установим делитель.
}

ISR (TIMER1_COMPA_vect) //тело прерывания
{
  90:	1f 92       	push	r1
  92:	0f 92       	push	r0
  94:	0f b6       	in	r0, 0x3f	; 63
  96:	0f 92       	push	r0
  98:	11 24       	eor	r1, r1
  9a:	8f 93       	push	r24
  9c:	9f 93       	push	r25
	flag = !flag;
  9e:	90 91 00 01 	lds	r25, 0x0100	; 0x800100 <__DATA_REGION_ORIGIN__>
  a2:	81 e0       	ldi	r24, 0x01	; 1
  a4:	89 27       	eor	r24, r25
  a6:	80 93 00 01 	sts	0x0100, r24	; 0x800100 <__DATA_REGION_ORIGIN__>
}
  aa:	9f 91       	pop	r25
  ac:	8f 91       	pop	r24
  ae:	0f 90       	pop	r0
  b0:	0f be       	out	0x3f, r0	; 63
  b2:	0f 90       	pop	r0
  b4:	1f 90       	pop	r1
  b6:	18 95       	reti

000000b8 <main>:


int main(void){
    flag = 0;
  b8:	10 92 00 01 	sts	0x0100, r1	; 0x800100 <__DATA_REGION_ORIGIN__>
bool flag;


void timer_ini(void)
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
  bc:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__TEXT_REGION_LENGTH__+0x7f8081>
  c0:	88 60       	ori	r24, 0x08	; 8
  c2:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7f8081>
	TIMSK1 |= (1<<OCIE1A);	//устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
  c6:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7f806f>
  ca:	82 60       	ori	r24, 0x02	; 2
  cc:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7f806f>
	OCR1AH = 0b00111100; //записываем в регистр число для сравнения
  d0:	8c e3       	ldi	r24, 0x3C	; 60
  d2:	80 93 89 00 	sts	0x0089, r24	; 0x800089 <__TEXT_REGION_LENGTH__+0x7f8089>
	OCR1AL = 0b10010010; //записываем в регистр число для сравнения
  d6:	82 e9       	ldi	r24, 0x92	; 146
  d8:	80 93 88 00 	sts	0x0088, r24	; 0x800088 <__TEXT_REGION_LENGTH__+0x7f8088>
	TCCR1B |= (1<<CS12);//установим делитель.
  dc:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__TEXT_REGION_LENGTH__+0x7f8081>
  e0:	84 60       	ori	r24, 0x04	; 4
  e2:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7f8081>


int main(void){
    flag = 0;
	timer_ini();
	DDRD = 0xFF;
  e6:	8f ef       	ldi	r24, 0xFF	; 255
  e8:	8a b9       	out	0x0a, r24	; 10
	while (1) {
		if(flag){
			PORTD = 0xFF;
  ea:	9f ef       	ldi	r25, 0xFF	; 255
int main(void){
    flag = 0;
	timer_ini();
	DDRD = 0xFF;
	while (1) {
		if(flag){
  ec:	80 91 00 01 	lds	r24, 0x0100	; 0x800100 <__DATA_REGION_ORIGIN__>
  f0:	88 23       	and	r24, r24
  f2:	29 f0       	breq	.+10     	; 0xfe <main+0x46>
			PORTD = 0xFF;
  f4:	9b b9       	out	0x0b, r25	; 11
int main(void){
    flag = 0;
	timer_ini();
	DDRD = 0xFF;
	while (1) {
		if(flag){
  f6:	80 91 00 01 	lds	r24, 0x0100	; 0x800100 <__DATA_REGION_ORIGIN__>
  fa:	81 11       	cpse	r24, r1
  fc:	fb cf       	rjmp	.-10     	; 0xf4 <main+0x3c>
			PORTD = 0xFF;
		}
		else{
			PORTD = 0x00;
  fe:	1b b8       	out	0x0b, r1	; 11
 100:	f5 cf       	rjmp	.-22     	; 0xec <main+0x34>

00000102 <_exit>:
 102:	f8 94       	cli

00000104 <__stop_program>:
 104:	ff cf       	rjmp	.-2      	; 0x104 <__stop_program>
