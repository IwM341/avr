#ifndef BMP180_HPP
#define BMP180_HPP

#include "twi_process.hpp"
#include "data.hpp"

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


static const uint8_t readCalibrationDataActions []= {
	twi_action::action_start_send,
	twi_action::action_slave_addr_write_send,
	twi_action::action_data_send,
	twi_action::action_stop_send,
	
	twi_action::action_start_send,
	twi_action::action_slave_addr_read_send,
	twi_action::action_data_read_ack_mask + 21,
	twi_action::action_data_read_nack,
	twi_action::action_stop_send
};

static const uint8_t  writeData_calibration []= {
	BMP180_ADDRESS,
	0xAA,
	BMP180_ADDRESS,
};

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

template <template <typename...> typename DelegatorType>
class bmp180{
	
	
	Bmp180CalibrationData mCalibration;
	twi_queue<AnyClassDelegator> *twi_q;
	
	public:
	bmp180(twi_queue<AnyClassDelegator>  *twi_q = 0):twi_q (twi_q ){}
	void setTwiQueue(twi_queue<AnyClassDelegator>  *_twi_q){twi_q = _twi_q;}
	
	
	
	
	
	DelegatorType<> delegator_calibration_read;
	
	template <typename...FunctionInfo>
	void setDelegatorCalibrationRead(FunctionInfo...fInfo){
		delegator_calibration_read = DelegatorType<>(fInfo...);
	}
	void setDelegatorCalibrationRead(){
		delegator_calibration_read = DelegatorType<>();
	}
	
	void endReadCalibration(){
		debug("endReadCalibration");
		for(uint8_t i=0;i < sizeof(Bmp180CalibrationData);i += 2){
			uint8_t _tmp = reinterpret_cast<uint8_t*>(&mCalibration)[i];
			reinterpret_cast<uint8_t*>(&mCalibration)[i] = reinterpret_cast<uint8_t*>(&mCalibration)[i+1];
			reinterpret_cast<uint8_t*>(&mCalibration)[i+1] = _tmp;
		}
		delegator_calibration_read.call();
	}
	
	inline const Bmp180CalibrationData & calibrationData() const{return mCalibration;}
	void startReadCalibrationData(){
		
		twi_q->set_action_queue((twi_action*)readCalibrationDataActions,(twi_action*)readCalibrationDataActions + static_array_len(readCalibrationDataActions));
		twi_q->set_write_buff(writeData_calibration);
		twi_q->set_end_function(this,&bmp180::endReadCalibration);
		twi_q->set_read_buff(reinterpret_cast<uint8_t*>(&mCalibration));
		print("start calib");
		INTERRUPT_LOCK
		twi_q->process();
		INTERRUPT_UNLOCK
		print("processed");
	}
	
};

#endif