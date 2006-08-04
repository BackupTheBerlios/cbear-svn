#ifndef CBEAR_BERLIOS_DE_REMOTE_COMMAND1_OUT_H_INCLUDED
#define CBEAR_BERLIOS_DE_REMOTE_COMMAND1_OUT_H_INCLUDED

#include <cbear.berlios.de/remoter/uuid.h>

#ifndef __cplusplus
extern "C"
{
#endif

typedef struct 
{
	cbear_berlios_de_remote_uuid uuid;
	uint8 pointer;
} cbear_berlios_de_remote_command1_out;

#ifndef __cplusplus
}
#endif

#endif
