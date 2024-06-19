#pragma once
#include <stdint.h>


struct hh_mm_ss_dd{
    uint_least8_t hh;
    uint_least8_t mm;
    uint_least8_t ss;
    uint_least32_t days;
	
	
    hh_mm_ss_dd(){}
    hh_mm_ss_dd(int_least32_t days,uint_least8_t hh,uint_least8_t mm,uint_least8_t ss = 0):
    hh(hh),mm(mm),ss(ss),days(days){}
	static	hh_mm_ss_dd from_sec(uint_least32_t m_sec){
		uint_least32_t m_min = m_sec/60;
		uint_least8_t sec_rm = m_sec%60;
		
		uint_least32_t m_hou = m_min/60;
		uint_least8_t min_rm = m_min%60;
		
		return {m_hou/24,m_hou%24,min_rm,sec_rm};
		
	}
	
		
	inline bool operator > (hh_mm_ss_dd const & other)const{
		if(days > other.days){
			return true;
		} else if (days < other.days) {
			return false;
		}
		
		if(hh > other.hh){
			return true;
		} else if (hh < other.hh) {
			return false;
		}
		
		if(mm > other.mm){
			return true;
		} else if (mm < other.mm) {
			return false;
		}
		
		if(ss > other.ss){
			return true;
		} else {
			return false;
		}
	}
	inline bool operator <(hh_mm_ss_dd const & other) const{
		return other > *this;
	}
	inline bool operator >=(hh_mm_ss_dd const & other) const{
		if(days > other.days){
			return true;
		} else if (days < other.days) {
			return false;
		}
		
		if(hh > other.hh){
			return true;
		} else if (hh < other.hh) {
			return false;
		}
		
		if(mm > other.mm){
			return true;
		} else if (mm < other.mm) {
			return false;
		}
		
		if(ss >= other.ss){
			return true;
		} else {
			return true;
		}
	}
	inline bool operator <=(hh_mm_ss_dd const & other) const{
		return other >= *this;
	}
	
	inline hh_mm_ss_dd & operator += (uint_least64_t msecs){
		msecs += ss;
		ss = msecs % 60;
		msecs/=60;
		
		msecs += mm;
		mm = msecs % 60;
		msecs/=60;
		
		msecs += hh;
		hh = msecs % 24;
		msecs/=24;
		
		days += msecs;
		return *this;
	}
	inline hh_mm_ss_dd operator + (uint_least64_t msecs)const{
		hh_mm_ss_dd ret = *this;
		ret+=msecs;
		return ret;
	}
	friend int_least64_t delta_secs(hh_mm_ss_dd const & _this,hh_mm_ss_dd const & _other){
		return ((int_least64_t)_this.days - _other.days)*3600*24 +
		((int_least32_t)_this.hh - _other.hh)*3600+
		((int_least32_t)_this.mm - _other.mm)*60+
		((int_least32_t)_this.ss - _other.ss);
	}
};

