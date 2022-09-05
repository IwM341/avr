#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

#define I2C_WRITE 0
#define I2C_READ 1

// Common status codes
#define I2C_STATUS_START_TRANSMITTED 0x8
#define I2C_STATUS_REPEATED_START_TRANSMITTED 0x10
#define I2C_STATUS_ARBITRATION_LOST 0x38

// Master transmitter status codes
#define I2C_STATUS_ADDRESS_WRITE_ACK_RECEIVED 0x18
#define I2C_STATUS_ADDRESS_WRITE_ACK_NOT_RECEIVED 0x20
#define I2C_STATUS_DATA_WRITE_ACK_RECEIVED 0x28
#define I2C_STATUS_DATA_WRITE_ACK_NOT_RECEIVED 0x30

// Master receiver status codes
#define I2C_STATUS_ADDRESS_READ_ACK_SENT 0x40
#define I2C_STATUS_ADDRESS_READ_ACK_NOT_SENT 0x48
#define I2C_STATUS_DATA_READ_ACK_SENT 0x50
#define I2C_STATUS_DATA_READ_ACK_NOT_SENT 0x58

struct i2c_hardware{
	i2c_hardware(uint8_t mTWBR = 0x20,uint8_t mTWPS = 0){
		TWBR = mTWBR;
		TWSR |= mTWPS & 0x00000011;
	}
	void init(uint8_t mTWBR = 0x20,uint8_t mTWPS = 0){
		TWBR = mTWBR;
		TWSR |= mTWPS & 0x00000011;
	}
	inline void wait() {
		while (!(TWCR & (1 << TWINT)));
	}
	
	void start() {
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
		wait();
	}
	
	void stop() {
		TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
		while ((TWCR & (1 << TWSTO)));
	}
	
	void sendData(uint8_t data) {
		TWDR = data;
		TWCR = (1 << TWINT) | (1 << TWEN);
		wait();
	}	
	
	uint8_t readDataAck() {
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		wait();
		return TWDR;
	}
	
	uint8_t readDataNotAck() {
		TWCR = (1 << TWINT) | (1 << TWEN);
		wait();
		return TWDR;
	}
	void sendSlaveAddress(uint8_t address, uint8_t readWriteMode) {
		sendData((address << 1) | readWriteMode);
	}	
	
	uint8_t getStatus() {
		return TWSR;
	}
};







    











#endif