#ifndef CBEAR_BERLIOS_DE_WINDOWS_WINUSER_H_INCLUDED
#define CBEAR_BERLIOS_DE_WINDOWS_WINUSER_H_INCLUDED

#include <winuser.h>

#include <cbear.berlios.de/windows/specstrings.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MSC_VER

#ifndef __GNUC__
typedef PVOID HDEVNOTIFY;
#endif

#if !defined(_USER32_)
#define WINUSERAPI DECLSPEC_IMPORT
#else
#define WINUSERAPI
#endif

#define DEVICE_NOTIFY_WINDOW_HANDLE 0x00000000
#define DEVICE_NOTIFY_SERVICE_HANDLE 0x00000001
      
WINUSERAPI HDEVNOTIFY WINAPI RegisterDeviceNotificationA(
	CBEAR_BERLIOS_DE_WINDOWS_IN HANDLE hRecipient,
	CBEAR_BERLIOS_DE_WINDOWS_IN LPVOID NotificationFilter,
	CBEAR_BERLIOS_DE_WINDOWS_IN DWORD Flags);

WINUSERAPI HDEVNOTIFY WINAPI RegisterDeviceNotificationW(
	CBEAR_BERLIOS_DE_WINDOWS_IN HANDLE hRecipient,
	CBEAR_BERLIOS_DE_WINDOWS_IN LPVOID NotificationFilter,
	CBEAR_BERLIOS_DE_WINDOWS_IN DWORD Flags);

WINUSERAPI BOOL WINAPI UnregisterDeviceNotification(
	CBEAR_BERLIOS_DE_WINDOWS_IN HDEVNOTIFY Handle);

#endif

#ifdef __cplusplus
}
#endif

#endif
