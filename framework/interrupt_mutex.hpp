#ifndef INTERRUPT_MUTEX_H
#define INTERRUPT_MUTEX_H



static uint8_t m_mutex = 0;
inline void mutex_close(){
	cli();
	m_mutex ++;
}

inline void mutex_open(){
	if(m_mutex)
		m_mutex --;
	if(!m_mutex)
		sei();
}

#define INTERRUPT_LOCKED_CODE(code) {register uint8_t __was_interrupt = SREG&0b10000000;\
										 cli(); \
										 code;\
										 SREG |= __was_interrupt; }

#define INTERRUPT_LOCK register uint8_t __was_interrupt = SREG&0b10000000; cli();
#define INTERRUPT_UNLOCK SREG |= __was_interrupt; 

#endif