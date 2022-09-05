#ifndef BMP180_H
#define BMP180_H

#include <util/delay.h>

#include "../i2c.h"

#ifndef BMP180_ADDRESS
#define BMP180_ADDRESS 0x77
#endif

#define BMP180_OK 0
#define BMP180_ERROR_UT 1
#define BMP180_ERROR_UP 2

#define BMP180_OSS_ULTRA_LOW_POWER 0
#define BMP180_OSS_STANDARD 1
#define BMP180_OSS_HIGH_RESOLUTION 2
#define BMP180_OSS_ULTRA_HIGH_RESOLUTION 3

typedef struct Bmp180CalibrationData {
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;
} Bmp180CalibrationData;

typedef struct Bmp180Data {
	float temperatureC;
	long pressurePa;
} Bmp180Data;

struct bmp180{
	Bmp180CalibrationData m_calibration;
	i2c_hardware *m_i2c;
	Bmp180Data m_data;
	int32_t b5;
	private:
	void calculateTemperature(uint16_t uncompensatedTemperature) {
		int32_t x1 = ((uncompensatedTemperature - m_calibration.ac6) * (int32_t) m_calibration.ac5) >> 15;
		int32_t x2 = ((int32_t) m_calibration.mc << 11) / (x1 + m_calibration.md);
		b5 = x1 + x2;
		float temperature = (int32_t) ((b5 + 8) >> 4);
		temperature /= (float) 10;
		m_data.temperatureC = temperature;
	}
	
	void calculatePressure(uint32_t uncompensatedPressure, uint8_t oss = BMP180_OSS_STANDARD) {
		int32_t b6 = b5 - 4000;
		int32_t x1 = ((int32_t) m_calibration.b2 * (b6 * b6 >> 12)) >> 11;
		int32_t x2 = (int32_t) m_calibration.ac2 * b6 >> 11;
		int32_t x3 = x1 + x2;
		int32_t b3 = ((((int32_t) m_calibration.ac1 * 4 + x3) << oss) + 2) >> 2;
		x1 = (int32_t) m_calibration.ac3 * b6 >> 13;
		x2 = ((int32_t) m_calibration.b1 * (b6 * b6 >> 12)) >> 16;
		x3 = ((x1 + x2) + 2) >> 2;
		uint32_t b4 = (uint32_t) m_calibration.ac4 * (x3 + 32768) >> 15;
		uint32_t b7 = ((uncompensatedPressure - b3) * (50000 >> oss));

		long p;
		if (b7 < 0x80000000) {
			p = ((b7 * 2) / b4);
			} else {
			p = ((b7 / b4) * 2);
		}

		x1 = (p >> 8) * (p >> 8);
		x1 = (x1 * 3038) >> 16;
		x2 = (-7357 * p) >> 16;
		p = p + ((x1 + x2 + 3791) >> 4);

		m_data.pressurePa = p;
	}
	
	public:	
	
	bmp180(i2c_hardware *m_i2c):m_i2c(m_i2c){}
	
	uint8_t readCalibrationData() {
		m_i2c->start();

		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_WRITE);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendData(0xAA);
		if (m_i2c->getStatus() != I2C_STATUS_DATA_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->stop();

		m_i2c->start();
		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_READ);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_READ_ACK_SENT) {
			return m_i2c->getStatus();
		}

		for (int reg = 0xAA; reg <= 0xBE; reg += 2) {
			uint16_t bits = 0;
			uint8_t msb = m_i2c->readDataAck();
			if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_SENT) {
				return m_i2c->getStatus();
			}

			uint8_t lsb;
			if (reg == 0xBE) {
				lsb = m_i2c->readDataNotAck();
				if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_NOT_SENT) {
					return m_i2c->getStatus();
				}
			} 
			else {
				lsb = m_i2c->readDataAck();
				if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_SENT) {
					return m_i2c->getStatus();
				}	
			}

			bits |= (msb << 8) | lsb;

			switch (reg) {
				case 0xAA:
				m_calibration.ac1 = bits;
				break;
				case 0xAC:
				m_calibration.ac2 = bits;
				break;
				case 0xAE:
				m_calibration.ac3 = bits;
				break;
				case 0xB0:
				m_calibration.ac4 = bits;
				break;
				case 0xB2:
				m_calibration.ac5 = bits;
				break;
				case 0xB4:
				m_calibration.ac6 = bits;
				break;
				case 0xB6:
				m_calibration.b1 = bits;
				break;
				case 0xB8:
				m_calibration.b2 = bits;
				break;
				case 0xBA:
				m_calibration.mb = bits;
				break;
				case 0xBC:
				m_calibration.mc = bits;
				break;
				case 0xBE:
				m_calibration.md = bits;
				break;
			}
		}

		m_i2c->stop();

		return BMP180_OK;
	}	
	uint8_t updateTemperature() {
		
		
		m_i2c->init();
		m_i2c->start();

		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_WRITE);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendData(0xF4);
		if (m_i2c->getStatus() != I2C_STATUS_DATA_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendData(0x2E);
		if (m_i2c->getStatus() != I2C_STATUS_DATA_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->stop();
		_delay_us(4500);

		m_i2c->start();
		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_WRITE);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendData(0xF6);
		if (m_i2c->getStatus() != I2C_STATUS_DATA_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->stop();
		m_i2c->start();
		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_READ);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_READ_ACK_SENT) {
			return m_i2c->getStatus();
		}

		uint8_t msb = m_i2c->readDataAck();
		if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_SENT) {
			return m_i2c->getStatus();
		}

		uint8_t lsb = m_i2c->readDataNotAck();
		if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_NOT_SENT) {
			return m_i2c->getStatus();
		}

		m_i2c->stop();

		uint16_t result = 0;
		result |= (msb << 8) | lsb;

		calculateTemperature(result);

		return BMP180_OK;
	}
	
	uint8_t updatePressure(uint8_t oss = BMP180_OSS_STANDARD) {
		m_i2c->init();
		m_i2c->start();
		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_WRITE);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendData(0xF4);
		if (m_i2c->getStatus() != I2C_STATUS_DATA_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendData(0x34 | (oss << 6));
		if (m_i2c->getStatus() != I2C_STATUS_DATA_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->stop();

		switch (oss) {
			case BMP180_OSS_ULTRA_LOW_POWER:
			_delay_us(4500);
			break;
			case BMP180_OSS_STANDARD:
			_delay_us(7500);
			break;
			case BMP180_OSS_HIGH_RESOLUTION:
			_delay_us(13500);
			break;
			case BMP180_OSS_ULTRA_HIGH_RESOLUTION:
			_delay_us(25500);
			break;
		}

		m_i2c->start();
		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_WRITE);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendData(0xF6);
		if (m_i2c->getStatus() != I2C_STATUS_DATA_WRITE_ACK_RECEIVED) {
			return m_i2c->getStatus();
		}

		m_i2c->stop();
		m_i2c->start();
		if (m_i2c->getStatus() != I2C_STATUS_START_TRANSMITTED) {
			return m_i2c->getStatus();
		}

		m_i2c->sendSlaveAddress(BMP180_ADDRESS, I2C_READ);
		if (m_i2c->getStatus() != I2C_STATUS_ADDRESS_READ_ACK_SENT) {
			return m_i2c->getStatus();
		}

		uint8_t msb = m_i2c->readDataAck();
		if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_SENT) {
			return m_i2c->getStatus();
		}

		uint8_t lsb = m_i2c->readDataAck();
		if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_SENT) {
			return m_i2c->getStatus();
		}

		uint8_t xlsb = m_i2c->readDataNotAck();
		if (m_i2c->getStatus() != I2C_STATUS_DATA_READ_ACK_NOT_SENT) {
			return m_i2c->getStatus();
		}

		m_i2c->stop();

		uint32_t result = 0;
		result |= ((uint16_t) msb << 8) | lsb;
		result <<= 8;
		result |= xlsb;

		result >>= (8 - oss);
		
		calculatePressure(result,oss);

		return BMP180_OK;
	}

	static float ConvertPressurePaToMmHg(const long &pressurePa) {
		return (float) (pressurePa * 0.00750062);
	}

	static int CalculateAltitudeMeters(const long & pressurePa) {
		return 44330 * (1 - pow((double) pressurePa / 101325, 1/5.255));
	}
	
	uint8_t updateAll(uint8_t oss = BMP180_OSS_STANDARD) {
		uint8_t result = updateTemperature();
		if (result != BMP180_OK) {
			return BMP180_ERROR_UT;
		}
		result = updatePressure(oss);

		if (result != BMP180_OK) {
			return BMP180_ERROR_UP;
		}
		return BMP180_OK;
	}
};














#endif