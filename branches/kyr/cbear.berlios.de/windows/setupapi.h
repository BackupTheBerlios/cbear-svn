#ifndef CBEAR_BERLIOS_DE_WINDOWS_SETUPAPI_H_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_SETUPAPI_H_INCLUDED

#include <setupapi.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MSC_VER

#define SPDRP_DEVICE_POWER_DATA 0x0000001E
#define SPDRP_REMOVAL_POLICY 0x0000001F
#define SPDRP_REMOVAL_POLICY_HW_DEFAULT 0x00000020
#define SPDRP_REMOVAL_POLICY_OVERRIDE 0x00000021

#endif

#ifdef __cplusplus
}
#endif

#endif
