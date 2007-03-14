#ifndef CBEAR_BERLIOS_DE_WINDOWS_DBT_H_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_DBT_H_INCLUDED

#include <dbt.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MSC_VER

#define DBT_DEVTYP_DEVICEINTERFACE 0x00000005

struct _DEV_BROADCAST_DEVICEINTERFACE_A 
{
	DWORD dbcc_size;
	DWORD dbcc_devicetype;
	DWORD dbcc_reserved;
	GUID dbcc_classguid;
	char dbcc_name[1];
};

struct _DEV_BROADCAST_DEVICEINTERFACE_W 
{
	DWORD dbcc_size;
	DWORD dbcc_devicetype;
	DWORD dbcc_reserved;
	GUID dbcc_classguid;
	wchar_t dbcc_name[1];
};
      
#endif

#ifdef __cplusplus
}
#endif

#endif
