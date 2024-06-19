#include "global.h"


guarded<float,atomic_guard> Temp = 0;
guarded<water_plan_array_t &> water_plan( 
	*reinterpret_cast<water_plan_array_t*>(
		calloc(sizeof(water_plan_array_t),1)
	)
);
guarded<water_every_array_t &> water_every(
	*reinterpret_cast<water_every_array_t*>(
		calloc(sizeof(water_every_array_t),1)
	)
);

Pump_t water_impl;

guarded<Settings> settings(Settings::load());
guarded<Clocks,guard_timer0> clocks;
