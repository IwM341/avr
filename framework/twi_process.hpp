#ifndef TWI_PROCESS_HPP
#define TWI_PROCESS_HPP

#include "delegator.hpp"
#include "data.hpp"
#include <avr/interrupt.h>

#include "uart_debugger.hpp"

class twi_process{
	
	public:
	void init(uint8_t mTWBR = 0x20,uint8_t mTWPS = 0){
		TWBR = mTWBR;
		TWSR |= mTWPS & 0x00000011;
	}
	
	typedef enum : uint8_t{
		status_start_transmitted = 0x8,
		status_repeated_start_transmitted = 0x10,
		status_arbitration_lost = 0x38,
		status_address_write_ack_received = 0x18,
		status_address_write_ack_not_received = 0x20,
		status_data_write_ack_received = 0x28,
		status_data_write_ack_not_received = 0x30,
		status_address_read_ack_sent = 0x40,
		status_address_read_ack_not_sent = 0x48,
		status_data_read_ack_sent = 0x50,
		status_data_read_ack_not_sent = 0x58,
		status_stop_transmitted,
		status_init = 0
	} status;
	
	typedef enum : uint8_t{
		read_mode = 0,
		write_mode = 1
	} read_write;
	
	
		
	
	typedef enum : uint8_t{
		no_status,
		wait_start_send,
		wait_data_send,
		wait_data_read_ack,
		wait_data_read_nack,
		wait_slave_addr_send
	} wait_status;
	
	
	
	
	//inline void twiInterrupt(wait_status w);
	/*
	inline void interruptStart();
	inline void interruptReadDataAck(uint8_t data);
	inline void interruptReadDataNack(uint8_t data);
	inline void interruptDataSend();
	inline void interruptSlaveAddrSend();
	*/
	
	inline void sendStart(){
		//print("aaaaaa");
		TWCR = (0<<TWINT)|(1<<TWSTA)|(1<<TWEN) | (1<<TWIE);
		//_current_wait_status = wait_start_send;
	}
	inline void sendStop(){
		TWCR = (0<<TWINT)|(1<<TWSTO)|(1<<TWEN)| (1<<TWIE);
	}
	
	inline void sendSlaveAddress(uint8_t address, uint8_t readWriteMode){
		sendData((address << 1) | readWriteMode);
		//_current_wait_status = wait_slave_addr_send;
	}
	inline void sendData(uint8_t data){
		TWDR = data;
		TWCR = (0<<TWINT)|(1 << TWEN)| (1<<TWIE);
		//_current_wait_status = wait_data_send;
	}
	
	inline void readDataAck() {
		TWCR = (0<<TWINT)| (1 << TWEN) | (1 << TWEA)| (1<<TWIE);
		//_current_wait_status = wait_data_read_ack;
	}
	inline void readDataNotAck() {
		TWCR = (0<<TWINT)| (1 << TWEN)| (1<<TWIE);
		//_current_wait_status = wait_data_read_nack;
	}
	inline uint8_t getStatus(){
		return TWSR & 0b11111100;
	}
	//wait_status _current_wait_status;
	
	static twi_process& twi_process_r(){
		static twi_process U;
		return U;
	}
	static twi_process* twi_process_p(){
		return &twi_process_r();
	}
	
	inline uint8_t data() const{return TWDR;}
	
	private:
	twi_process(){}
	twi_process(const twi_process&){}
	twi_process(twi_process &&){}
	
};

#define STATIC_CONNECT_TWI_INTERRUPT(interrupt_twi_code) ISR(TWI_vect){TWCR &= ~(1<<TWIE); print("twi_interrupt1");interrupt_twi_code;}


#define STATIC_CONNECT_TWI_QUEUE_INTERRUPT(m_twi_queue) ISR(TWI_vect){TWCR &= ~(1<<TWIE);print("twi_interrupt2: ",(uint8_t)TWCR); m_twi_queue.process();}
	

	
typedef enum : uint8_t{
	action_start_send = 0x00,
	action_stop_send = 0b00000001,
	action_data_send_mask = 0b10000000,
	action_data_send= 0b10000001,
	action_data_read_ack_mask = 0b01000000,
	action_data_read_ack = 0b01000001,
	action_data_read_nack = 0b00000010,
	action_slave_addr_write_send = 0b00000011,
	action_slave_addr_read_send= 0b00000100
} twi_action;

template<template <typename...> typename DelegatorType>
struct twi_queue{
	DelegatorType<> delegator_end;
	DelegatorType<uint8_t> delegator_error;
	
	
	
	typedef enum : uint8_t{	
		error
	}errors;
	
	const twi_action *action_tmp;
	const twi_action * action_last;
	
	const uint8_t * tmp_write_buff;
	uint8_t * tmp_read_buff;
	
	uint8_t expextedStatus;
	
	uint8_t repeatAction = 0xFF;;
	
	twi_queue():expextedStatus (twi_process::status_init){}
	inline void set_action_queue(const twi_action *_action_first, const twi_action * _action_last){
		action_tmp = _action_first;
		action_last = _action_last;
	}
	inline void set_write_buff(const uint8_t * write_buff){
		tmp_write_buff = write_buff;
	}
	inline void set_read_buff(uint8_t * read_buff){
		tmp_read_buff= read_buff;
	}
	
	template <typename...FunctionInfo>
	inline void set_end_function(FunctionInfo...info){
		delegator_end = DelegatorType<>(info...);
	}
	
	template <typename...FunctionInfo>
	inline void set_error_function(FunctionInfo...info){
		delegator_error = DelegatorType<uint8_t>(info...);
	}
	
	void process(){
		auto & m_twi = twi_process::twi_process_r();
		
		print("status: ",expextedStatus,'\t',m_twi.getStatus());
		
		if(expextedStatus && (expextedStatus != m_twi.getStatus()) ){
			print("twi error:",expextedStatus ,'+',(char)m_twi.getStatus(),(uint8_t)m_twi.getStatus());
			delegator_error.call(12);
			return;
		}
		
		if(expextedStatus == twi_process::status_address_read_ack_not_sent ||
			expextedStatus == twi_process::status_address_read_ack_sent ||
			expextedStatus == twi_process::status_data_read_ack_not_sent ||
			expextedStatus == twi_process::status_data_read_ack_sent){
				*tmp_read_buff = m_twi.data();
				tmp_read_buff++;		
			}
		
		if(action_tmp == action_last){
			print("twi end");
			delegator_end.call();
			return;
		}
		
		
		switch(*action_tmp){
			case action_start_send:{
				m_twi.sendStart();
				expextedStatus = twi_process::status_start_transmitted;
				action_tmp++;
				break;
			}
			case action_stop_send:{
				m_twi.sendStop();
				expextedStatus = twi_process::status_stop_transmitted;
				action_tmp++;
				break;
			}
			case action_slave_addr_write_send:{
				m_twi.sendSlaveAddress(*tmp_write_buff,twi_process::write_mode);
				tmp_write_buff++;
				expextedStatus = twi_process::status_address_write_ack_received;
				action_tmp++;
				break;
			}
			case action_slave_addr_read_send:{
				m_twi.sendSlaveAddress(*tmp_write_buff,twi_process::write_mode);
				tmp_write_buff++;
				expextedStatus = twi_process::status_address_read_ack_sent;
				action_tmp++;
				break;
			}
			
			case  action_data_read_nack:{
				m_twi.readDataAck();
				expextedStatus = twi_process::status_data_read_ack_not_sent;
				action_tmp++;
				break;
			}
			case action_data_send:{
				m_twi.sendData(*tmp_write_buff);
				tmp_write_buff++;
				expextedStatus = twi_process::status_data_write_ack_received;
				break;
			}
			case action_data_read_ack:{
				m_twi.readDataAck();
				expextedStatus = twi_process::status_data_read_ack_sent;
				break;
			}
			default:{
				register uint8_t tmp_act = *action_tmp;
				if( tmp_act & action_data_read_ack_mask){
					if(repeatAction == 0xFF){
						repeatAction = tmp_act & 0b00111111;
						if(!repeatAction){
							tmp_act ++;
						}
					}
					m_twi.readDataAck();
					expextedStatus = twi_process::status_data_read_ack_sent;
					repeatAction--;
					if( repeatAction == 0){
						repeatAction = 0xFF;
						action_tmp ++;
					}
				}
				else if(tmp_act & action_data_send_mask){
					if(repeatAction  == 0xFF){
						repeatAction = tmp_act & 0b00111111;
						if(!repeatAction){
							tmp_act ++;
						}
					}
					m_twi.sendData(*tmp_write_buff);
					expextedStatus = twi_process::status_data_read_ack_sent;
					repeatAction--;
					if( repeatAction == 0){
						repeatAction = 0xFF;
						action_tmp ++;
					}
				}
				else{
					print("unexpected action");
					delegator_error.call(1);
					return;
				}
			}
		}

	}
	
	
};



#endif