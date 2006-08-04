#ifndef CBEAR_BERLIOS_DE_REMOTE_COMMAND1_OUT_H_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_COMMAND1_OUT_H_INCLUDED

#include <cbear.berlios.de/remote/uuid.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct 
{
	cbear_berlios_de_remote_uuid uuid;
	cbear_berlios_de_remote_uint8 pointer;
} cbear_berlios_de_remote_command1_out;

#ifdef __cplusplus
}
#endif

#endif
