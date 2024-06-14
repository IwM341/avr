#ifndef USART_H
#define USART_H
#include "../core/async_io.h"
#include "scheduler.h"
#include "guard.h"

#ifdef __AVR_ATmega328P__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#endif

#ifndef ASYNCRUINO_MAX_UART_BUFF
#define ASYNCRUINO_MAX_UART_BUFF 32
#endif




namespace asyncruino{
    
    struct hardware_uart_impl{
        inline hardware_uart_impl(){}
        public:
        bool write_if_ready(char c){
            #ifdef __AVR_ATmega328P__
            if(UCSR0A & (1<<UDRE0)){
                UDR0 = c;
                return true;
            } else {
                return false;
            }
            #endif
        }
        void write(char c){
            #ifdef __AVR_ATmega328P__
            UDR0 = c;
            #endif
        }

        #ifdef __AVR_ATmega328P__
        void debug_string(const char * str){
            UCSR0B = (1<<RXEN0)|( 1<<TXEN0);
            while(*str){
                while(!(UCSR0A & (1<<UDRE0))){
                }
				UDR0 = *str;
				++str;
            }
            
        }
        #else
        void debug_string(const char * str);
        #endif
                
        inline void init(uint32_t m_baud_rate,uint32_t f_cpu){
            #ifdef __AVR_ATmega328P__
            //usart speed BAUD  = F_CPU/(1+UBBRn)/16
            bool double_speed = false;
            uint32_t pot_speed_reg = f_cpu/(16*m_baud_rate) - 1; 
            if(2*pot_speed_reg < ((uint32_t)1<<16) ){
                pot_speed_reg = f_cpu/(8*m_baud_rate) - 1; 
                double_speed = true;
            }
            UBRR0H = (unsigned char)(pot_speed_reg>>8);
		    UBRR0L = (unsigned char)pot_speed_reg;
            if(double_speed){
                UCSR0A = UCSR0A  | (1<<U2X0); //double speed
            }
            UCSR0B = (1<<RXEN0)|( 1<<TXEN0); //enable uart
			
            UCSR0B =UCSR0B |( (1<<RXCIE0) | (1<<TXCIE0)); //enable interrupt
            UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
            #endif
        }
        inline void close(){
            #ifdef __AVR_ATmega328P__
            UBRR0H = 0;
            UBRR0L = 0;
            UCSR0A = 0;
            UCSR0B = 0;
            UCSR0C = 0;
            #endif
        }

        static hardware_uart_impl & instance(){
            static hardware_uart_impl m_writer;
            return m_writer;
        }
    };

    typedef async_input_impl<scheduler,default_guard,uint8_t,ASYNCRUINO_MAX_UART_BUFF> Input_t;
    typedef async_output_impl<scheduler,hardware_uart_impl,default_guard,uint8_t> Output_t; 

    struct uart : 
        public Input_t,
        public Output_t
        {
        
        
        private:
        inline uart(): Input_t(scheduler::instance()),
            Output_t(scheduler::instance(),hardware_uart_impl::instance()){
				#ifndef ASYNCRUINO_UART_ENABLE
				static_assert(false,"uart is working only if defined ASYNCRUINO_UART_ENABLE");
				#endif
				
                #ifdef F_CPU
                init(BAUD_9600,F_CPU);
                #endif
            }
        public:
        #define _DECL_BAUD(m_speed) BAUD_##m_speed = m_speed
        enum bauds:uint32_t{
            _DECL_BAUD(75),
            _DECL_BAUD(110),
            _DECL_BAUD(300),
            _DECL_BAUD(600),
            _DECL_BAUD(1200),
            _DECL_BAUD(1800),
            _DECL_BAUD(2400),
            _DECL_BAUD(4800),
            _DECL_BAUD(9600),
            _DECL_BAUD(19200),
            _DECL_BAUD(28800),
            _DECL_BAUD(38400),
            _DECL_BAUD(57600),
            _DECL_BAUD(76800), 
            _DECL_BAUD(115200)
        };
        #undef _DECL_BAUD
        inline static void init(
            uint32_t m_baud_rate,
            uint32_t f_cpu
            #ifdef F_CPU
            = F_CPU
            #endif
        ){
            hardware_uart_impl::instance().init(m_baud_rate,f_cpu);
        }
        inline static uart& instance(){
            static uart m_inst;
            return m_inst;
        }
        inline static auto ReadByte(){
            return instance().Input_t::ReadByte();
        }
        inline static auto ReadBytes(char * dest,uint8_t _size){
            return instance().Input_t::ReadBytes(dest,_size);
        }
        inline static auto ReadBytesUntil(char * dest,char esc_sym,uint8_t max_size){
            return instance().Input_t::ReadBytesUntil(dest,max_size,esc_sym);
        }
        inline static auto WriteByte(char c){
            return instance().Output_t::WriteByte(c);
        }
        inline static auto WriteBytes(const char *str,uint8_t _size){
            return instance().Output_t::WriteBytes(str,_size);
        }
		inline static auto WriteBytes(const char *str){
			return instance().Output_t::WriteBytes(str);
		}

        static void debug_crush(const char * data){
            hardware_uart_impl::instance().debug_string(data);
        }

    };
    

#ifdef ASYNCRUINO_UART_ENABLE
    ISR(USART_RX_vect){
        char c = UDR0;
        uart::instance().Input_t::interrupt(c);
    }
    //transmit
    ISR (USART_TX_vect){
        uart::instance().Output_t::interrupt();
    }
#endif
};


#endif//USART_H