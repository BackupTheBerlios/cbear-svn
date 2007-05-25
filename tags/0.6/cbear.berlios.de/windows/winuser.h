/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
