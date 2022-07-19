#ifndef PORTS_H
#define PORTS_H

#define set_port(PORT,mask,val) ( (PORT) = ((PORT) & ~(mask)) | (val&mask) )

#endif