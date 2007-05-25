#ifndef CBEAR_BERLIOS_DE_REMOTE_IN_HEADER_H_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_IN_HEADER_H_INCLUDED

#include <cbear.berlios.de/remote/uint16.h>

#ifndef __cplusplus
extern "C"
{
#endif

typedef struct 
{
	cbear_berlios_de_remote_uint16 in;
	cbear_berlios_de_remote_uint16 out;
	cbear_berlios_de_remote_uint16 command;	
} cbear_berlios_de_remote_in_header;

#ifndef __cplusplus
}
#endif

#endif
