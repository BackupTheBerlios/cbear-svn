///////////////////////////////////////////////////////////////////////////////
//
//    (C) Copyright 1995 - 2003 OSR Open Systems Resources, Inc.
//    All Rights Reserved
//
//    This sofware is supplied for instructional purposes only.
//
//    OSR Open Systems Resources, Inc. (OSR) expressly disclaims any warranty
//    for this software.  THIS SOFTWARE IS PROVIDED  "AS IS" WITHOUT WARRANTY
//    OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION,
//    THE IMPLIED WARRANTIES OF MECHANTABILITY OR FITNESS FOR A PARTICULAR
//    PURPOSE.  THE ENTIRE RISK ARISING FROM THE USE OF THIS SOFTWARE REMAINS
//    WITH YOU.  OSR's entire liability and your exclusive remedy shall not
//    exceed the price paid for this material.  In no event shall OSR or its
//    suppliers be liable for any damages whatsoever (including, without
//    limitation, damages for loss of business profit, business interruption,
//    loss of business information, or any other pecuniary loss) arising out
//    of the use or inability to use this software, even if OSR has been
//    advised of the possibility of such damages.  Because some states/
//    jurisdictions do not allow the exclusion or limitation of liability for
//    consequential or incidental damages, the above limitation may not apply
//    to you.
//
//    OSR Open Systems Resources, Inc.
//    105 Route 101A Suite 19
//    Amherst, NH 03031  (603) 595-6500 FAX: (603) 595-6503
//    email bugs to: bugs@osr.com
//
//
//    MODULE:
//
//      USBFXTEST.cpp
//
//    ABSTRACT:
//
//      Test application for OSR's USBFX2 sample driver
//
//
//    AUTHOR(S):
//
//      OSR Open Systems Resources, Inc.
// 
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <windows.h>
#include <winioctl.h>
#include <initguid.h>

//#include <usbfx2lk_ioctl.h>
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable: 4201)
#include <public.h>
#pragma warning(pop)

#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

#include <stdlib.h>

// 'function': was declared deprecated
#pragma warning(disable: 4996)


//////////////////////////
// Forward Declarations //
//////////////////////////
BOOLEAN 
FindUSBFX2LKDevice(
    PHANDLE Handle
    );

int __cdecl main(ULONG /*argc*/, LPSTR * /*argv*/)
{
    HANDLE          deviceHandle;
    DWORD           code;
    ULONG           bytesRet;
    DWORD           function;

    BAR_GRAPH_STATE barGraphState;
    SWITCH_STATE    switchState;
    UCHAR           sevenSegment = 0;


    //
    // Let's see if we can find an OSR USB FX2 device
    //  in the system...
    //
    if (!FindUSBFX2LKDevice(&deviceHandle)) {

        //
        // Nope. Not much we can do, let's just get
        //  outta here...
        //
        printf("Unable to find any OSR FX2 devices!\n");

        return 1;

    }

    //
    // Infinitely print out the list of choices, ask for input, process
    // the request
    //
    for(;;)  {

        printf ("\nUSBFX TEST -- Functions:\n\n");
        printf ("\t1.  Light Bars\n");
        printf ("\t2.  Light entire Bar graph\n");
        printf ("\t3.  Clear entire Bar graph\n");
        printf ("\t4.  Get bar graph state\n");
        printf ("\t5.  Get Switch state\n");
        printf ("\t6.  Get Switch Interrupt Message\n");
        printf ("\t7.  Get 7 segment state\n");
        printf ("\t8.  Set 7 segment states\n");
        printf ("\n\t0. Exit\n");
        printf ("\n\tSelection: ");

        if (scanf ("%d", &function) <= 0) {

            printf("Error reading input!\n");
            return 1;

        }

        switch(function)  {

        case 1:

            for (UCHAR i = 0; i < 8; i++) {

                barGraphState.BarsAsUChar = 1 << i;

                if (!DeviceIoControl(deviceHandle,
                                     IOCTL_OSRUSBFX2_SET_BAR_GRAPH_DISPLAY  ,
                                     &barGraphState,             // Ptr to InBuffer
                                     sizeof(BAR_GRAPH_STATE),            // Length of InBuffer
                                     NULL,                 // Ptr to OutBuffer
                                     0,         // Length of OutBuffer
                                     &bytesRet,                     // BytesReturned
                                     0)) {                       // Ptr to Overlapped structure

                    code = GetLastError();

                    printf("DeviceIoControl failed with error 0x%x\n", code);

                    return(code);
                }

                printf("This is %d\n", i+1);
                Sleep(500);


            }
            break;
        case 2:

            barGraphState.BarsAsUChar = 0xFF;

            if (!DeviceIoControl(deviceHandle,
                                 IOCTL_OSRUSBFX2_SET_BAR_GRAPH_DISPLAY,
                                 &barGraphState,                 // Ptr to InBuffer
                                 sizeof(BAR_GRAPH_STATE),         // Length of InBuffer
                                 NULL,             // Ptr to OutBuffer
                                 0,            // Length of OutBuffer
                                 &bytesRet,                     // BytesReturned
                                 0)) {                       // Ptr to Overlapped structure

                code = GetLastError();

                printf("DeviceIoControl failed with error 0x%x\n", code);

                return(code);
            }

            break;

        case 3:

            barGraphState.BarsAsUChar = 0;

            if (!DeviceIoControl(deviceHandle,
                                 IOCTL_OSRUSBFX2_SET_BAR_GRAPH_DISPLAY,
                                 &barGraphState,                 // Ptr to InBuffer
                                 sizeof(BAR_GRAPH_STATE),         // Length of InBuffer
                                 NULL,             // Ptr to OutBuffer
                                 0,            // Length of OutBuffer
                                 &bytesRet,                     // BytesReturned
                                 0)) {                       // Ptr to Overlapped structure

                code = GetLastError();

                printf("DeviceIoControl failed with error 0x%x\n", code);

                return(code);
            }

            break;


        case 4:

            barGraphState.BarsAsUChar = 0;

            if (!DeviceIoControl(deviceHandle,
                                 IOCTL_OSRUSBFX2_GET_BAR_GRAPH_DISPLAY,
                                 NULL,             // Ptr to InBuffer
                                 0,            // Length of InBuffer
                                 &barGraphState,                 // Ptr to OutBuffer
                                 sizeof(BAR_GRAPH_STATE),         // Length of OutBuffer
                                 &bytesRet,                     // BytesReturned
                                 0)) {                       // Ptr to Overlapped structure

                code = GetLastError();

                printf("DeviceIoControl failed with error 0x%x\n", code);

                return(code);
            }

            printf("Bar Graph: \n");
            printf("    Bar8 is %s\n", barGraphState.Bar8 ? "ON" : "OFF");
            printf("    Bar7 is %s\n", barGraphState.Bar7 ? "ON" : "OFF");
            printf("    Bar6 is %s\n", barGraphState.Bar6 ? "ON" : "OFF");
            printf("    Bar5 is %s\n", barGraphState.Bar5 ? "ON" : "OFF");
            printf("    Bar4 is %s\n", barGraphState.Bar4 ? "ON" : "OFF");
            printf("    Bar3 is %s\n", barGraphState.Bar3 ? "ON" : "OFF");
            printf("    Bar2 is %s\n", barGraphState.Bar2 ? "ON" : "OFF");
            printf("    Bar1 is %s\n", barGraphState.Bar1 ? "ON" : "OFF");

            break;

        case 5:

            switchState.SwitchesAsUChar = 0;

            if (!DeviceIoControl(deviceHandle,
                                 IOCTL_OSRUSBFX2_READ_SWITCHES,
                                 NULL,             // Ptr to InBuffer
                                 0,            // Length of InBuffer
                                 &switchState,                 // Ptr to OutBuffer
                                 sizeof(SWITCH_STATE),         // Length of OutBuffer
                                 &bytesRet,                     // BytesReturned
                                 0)) {                       // Ptr to Overlapped structure

                code = GetLastError();

                printf("DeviceIoControl failed with error 0x%x\n", code);

                return(code);
            }

            printf("Switches: \n");
            printf("    Switch8 is %s\n", switchState.Switch8 ? "ON" : "OFF");
            printf("    Switch7 is %s\n", switchState.Switch7 ? "ON" : "OFF");
            printf("    Switch6 is %s\n", switchState.Switch6 ? "ON" : "OFF");
            printf("    Switch5 is %s\n", switchState.Switch5 ? "ON" : "OFF");
            printf("    Switch4 is %s\n", switchState.Switch4 ? "ON" : "OFF");
            printf("    Switch3 is %s\n", switchState.Switch3 ? "ON" : "OFF");
            printf("    Switch2 is %s\n", switchState.Switch2 ? "ON" : "OFF");
            printf("    Switch1 is %s\n", switchState.Switch1 ? "ON" : "OFF");
           
            break;

        case 6:   {
            switchState.SwitchesAsUChar = 0;

            if (!DeviceIoControl(deviceHandle,
                                 IOCTL_OSRUSBFX2_GET_INTERRUPT_MESSAGE,
                                 NULL,             // Ptr to InBuffer
                                 0,            // Length of InBuffer
                                 &switchState,                 // Ptr to OutBuffer
                                 sizeof(switchState),         // Length of OutBuffer
                                 &bytesRet,                     // BytesReturned
                                 0)) {                       // Ptr to Overlapped structure

                code = GetLastError();

                printf("DeviceIoControl failed with error 0x%x\n", code);

                return(code);
            }

            printf("Switches:\n");
            printf("    Switch8 is %s\n", switchState.Switch8 ? "ON" : "OFF");
            printf("    Switch7 is %s\n", switchState.Switch7 ? "ON" : "OFF");
            printf("    Switch6 is %s\n", switchState.Switch6 ? "ON" : "OFF");
            printf("    Switch5 is %s\n", switchState.Switch5 ? "ON" : "OFF");
            printf("    Switch4 is %s\n", switchState.Switch4 ? "ON" : "OFF");
            printf("    Switch3 is %s\n", switchState.Switch3 ? "ON" : "OFF");
            printf("    Switch2 is %s\n", switchState.Switch2 ? "ON" : "OFF");
            printf("    Switch1 is %s\n", switchState.Switch1 ? "ON" : "OFF");
            }
            break;

        case 7:

            sevenSegment = 0;

            if (!DeviceIoControl(deviceHandle,
                                 IOCTL_OSRUSBFX2_GET_7_SEGMENT_DISPLAY,
                                 NULL,             // Ptr to InBuffer
                                 0,            // Length of InBuffer
                                 &sevenSegment,                 // Ptr to OutBuffer
                                 sizeof(UCHAR),         // Length of OutBuffer
                                 &bytesRet,                     // BytesReturned
                                 0)) {                       // Ptr to Overlapped structure

                code = GetLastError();

                printf("DeviceIoControl failed with error 0x%x\n", code);

                return(code);
            }

            printf("7 Segment mask:  0x%x\n", sevenSegment);
            break;

        case 8:

            for (UCHAR i = 0; i < 8; i++) {

                sevenSegment = 1 << i;

                if (!DeviceIoControl(deviceHandle,
                                     IOCTL_OSRUSBFX2_SET_7_SEGMENT_DISPLAY,
                                     &sevenSegment,             // Ptr to InBuffer
                                     sizeof(UCHAR),            // Length of InBuffer
                                     NULL,                 // Ptr to OutBuffer
                                     0,         // Length of OutBuffer
                                     &bytesRet,                     // BytesReturned
                                     0)) {                       // Ptr to Overlapped structure

                    code = GetLastError();

                    printf("DeviceIoControl failed with error 0x%x\n", code);

                    return(code);
                }

                printf("This is %d\n", i+1);
                Sleep(500);

            }

            printf("7 Segment mask:  0x%x\n", sevenSegment);
            break;

        case 0:
        default:

            CloseHandle(deviceHandle);

            //
            // zero is get out!
            //
            return(0);

        }
    }   
}


///////////////////////////////////////////////////////////////////////////////
//
//  FindUSBFX2LKDevice
//
//    This routine tries to return a handle to a USB FX2 Learning Kit device.
//     If multiple devices are found, a handle to the first available
//     one found is returned;
//
//  INPUTS:
//
//      None
//
//  OUTPUTS:
//
//      Handle - Upon successful return, this is filled in 
//                with a valid, open handle to a USB FX2 device.
//                HANDLE must be closed by the caller. 
//
//  RETURNS:
//
//      TRUE if a device has been found and Handle contains
//       a valid HANDLE. FALSE otherwise.
//
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN 
FindUSBFX2LKDevice(
    PHANDLE Handle
    ) {

    HDEVINFO                         devInfo;
    SP_DEVICE_INTERFACE_DATA         devInterfaceData;
    PSP_DEVICE_INTERFACE_DETAIL_DATA devInterfaceDetailData = NULL;
    ULONG                            devIndex;
    ULONG                            requiredSize;
    ULONG                            code = ERROR_SUCCESS;
    // PCHAR                            devicePath = NULL;


    //
    // Open a handle to the device using the 
    //  device interface that the driver registers
    //
    //

    //
    // Get the device information set for all of the
    //  devices of our class (the GUID we defined
    //  in nothingioctl.h and registered in the driver
    //  with DfwDeviceCreateDeviceInterface) that are present in the 
    //  system
    //
    devInfo = SetupDiGetClassDevs(
			// &GUID_OSR_USBFX2LK_INTERFACE,
			&GUID_DEVINTERFACE_OSRUSBFX2,
      NULL,
      NULL,
      DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (devInfo == INVALID_HANDLE_VALUE) {

        printf("SetupDiGetClassDevs failed with error 0x%x\n", GetLastError());

        return FALSE;

    }

    //
    // Now get information about each device installed...
    //
    
    //
    // This needs to be set before calling
    //  SetupDiEnumDeviceInterfaces
    //
    devInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    //
    // Start with the first device...
    //
    devIndex = 0;

    while (SetupDiEnumDeviceInterfaces(devInfo,
                                       NULL,
                                       // &GUID_OSR_USBFX2LK_INTERFACE,
																			 &GUID_DEVINTERFACE_OSRUSBFX2,
                                       devIndex++, 
                                       &devInterfaceData)) {

        //
        // If you actually had a reason to keep
        //  track of all the devices in the system
        //  you obviously wouldn't want to just
        //  throw these away. Since we're just 
        //  running through to print them out
        //  and picking whatever the last one
        //  is we'll alloc and free these
        //  as we go...
        //
        if (devInterfaceDetailData != NULL) {

            free(devInterfaceDetailData);

            devInterfaceDetailData = NULL;

        }

        //
        // The entire point of this exercise is
        //  to get a string that we can hand to 
        //  CreateFile to get a handle to the device,
        //  so we need to call SetupDiGetDeviceInterfaceDetail
        //  (which will give us the string we need)
        //

        //
        // First call it with a NULL output buffer to
        //  get the number of bytes needed...
        //
        if (!SetupDiGetDeviceInterfaceDetail(devInfo,
                                             &devInterfaceData,
                                             NULL,
                                             0,
                                             &requiredSize,
                                             NULL)) {

            code = GetLastError();

            //
            // We're expecting ERROR_INSUFFICIENT_BUFFER.
            //  If we get anything else there's something
            //  wrong...
            //
            if (code != ERROR_INSUFFICIENT_BUFFER) {

                printf("SetupDiGetDeviceInterfaceDetail failed with error 0x%x\n", code);

                //
                // Clean up the mess...
                //
                SetupDiDestroyDeviceInfoList(devInfo);
                
                return FALSE;

            }

        }

        //
        // Allocated a PSP_DEVICE_INTERFACE_DETAIL_DATA...
        //
        devInterfaceDetailData = 
                (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(requiredSize);

        if (!devInterfaceDetailData) {

            printf("Unable to allocate resources...Exiting\n");

            //
            // Clean up the mess...
            //
            SetupDiDestroyDeviceInfoList(devInfo);

            return FALSE;

        }

        //
        // This needs to be set before calling
        //  SetupDiGetDeviceInterfaceDetail. You
        //  would *think* that you should be setting
        //  cbSize to requiredSize, but that's not the 
        //  case. 
        //
        devInterfaceDetailData->cbSize = 
                    sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);


        if (!SetupDiGetDeviceInterfaceDetail(devInfo,
                                             &devInterfaceData,
                                             devInterfaceDetailData,
                                             requiredSize,
                                             &requiredSize,
                                             NULL)) {

            printf("SetupDiGetDeviceInterfaceDetail failed with error 0x%x\n", GetLastError());

            //
            // Clean up the mess...
            //
            SetupDiDestroyDeviceInfoList(devInfo);

            free(devInterfaceDetailData);

            return FALSE;

        }

        //
        // Got one!
        //
        printf("Device found! %s\n", devInterfaceDetailData->DevicePath);

        //
        // We don't really care which one we get, 
        //  just try to open each one and quit when we succeeed...
        //
        *Handle = CreateFile(devInterfaceDetailData->DevicePath,  // Name of the NT "device" to open
                             GENERIC_READ|GENERIC_WRITE,  // Access rights requested
                             0,                           // Share access - NONE
                             0,                           // Security attributes - not used!
                             OPEN_EXISTING,               // Device must exist to open it.
                             0,                           // Open for overlapped I/O
                             0);                          // extended attributes - not used!

        if (*Handle == INVALID_HANDLE_VALUE) {

            printf("CreateFile failed with error 0x%x\n", GetLastError());

        } else {

            SetupDiDestroyDeviceInfoList(devInfo);
        
            free(devInterfaceDetailData);

            return TRUE;

        }

    }

    //
    // We're here if we ran our of devices to enumarate or if
    //  something went wrong with our initial call to 
    //  SetupDiEnumDeviceInterfaces
    //

    if (code != ERROR_NO_MORE_ITEMS) {

        //
        // Something tr
        //
        printf("SetupDiGetDeviceInterfaceDetail failed with error 0x%x\n", code);
        
        //
        // Clean up the mess...
        //
        return FALSE;

    }

    //
    // ERROR_NO_MORE_ITEMS means that there are either no
    //  devices to enumerate or all of the devices 
    //  refused our open request.
    //
    SetupDiDestroyDeviceInfoList (devInfo);
    
    printf("Unable to find or open any OSR USB FX2 devices!\n");

    return FALSE;

}
