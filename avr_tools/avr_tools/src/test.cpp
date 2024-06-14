#include <new.h>


void myfunc(char * data){
	new (data) char('a');
	aos::interrupt_guard g;
	g.lock();
	g.unlock();
}
