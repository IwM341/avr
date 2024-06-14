#ifndef __GUARD_H__
#define __GUARD_H__

struct __guard__{
	uint8_t sregOld;
};

extern "C" void __guard__lock(__guard__ *g);
extern "C" void __guard__unlock(__guard__ *g);

#endif