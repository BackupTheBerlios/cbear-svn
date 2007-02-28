///////////////////////////////////////////////////////////////////////////////
//
//    (C) Copyright 2005 OSR Open Systems Resources, Inc.
//    Copyright (c) 1997-1998  Microsoft Corporation
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
//        OSRBulk.CPP -- Contains string values for various
//                          constants used in the driver.
//                          Entire module for debugging
//                          output purposes onlu...
//
//    ABSTRACT:
//
//      Console test app for USBFx2LK.sys driver
//
//    AUTHOR(S):
//
//        OSR Open Systems Resources, Inc.
// 
//    REVISION:   
//
//      $Revision: 1 $ , $Date: 3/09/05 3:26p $  
//
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "devioctl.h"

#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

#include <basetyps.h>
#include <initguid.h>

// #include <usbfx2lk_ioctl.h>
//#include <usbfx2lk_ioctl.h>
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable: 4201)
#include <public.h>
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable : 4200)
#include <usbdi.h>
#pragma warning(pop)

// 'function': was declared deprecated
#pragma warning(disable: 4996)

#define NOISY(_x_) printf _x_ ;
#define NPERLN 8


char inPipe[32] = "";     // pipe name for bulk input pipe on our test board
char outPipe[32] = "";    // pipe name for bulk output pipe on our test board
wchar_t completeDeviceName[256] = L"";  //generated from the GUID registered by the driver itself

BOOL fDumpUsbConfig = FALSE;    // flags set in response to console command line switches
BOOL fDumpReadData = FALSE;
BOOL fRead = FALSE;
BOOL fWrite = FALSE;
BOOL fShowSegment = FALSE;
ULONG successes = 0;
ULONG errors = 0;

int gDebugLevel = 1;      // higher == more verbose, default is 1, 0 turns off all

ULONG IterationCount = 1; //count of iterations of the test we are to perform
int WriteLen = 0;         // #bytes to write
int ReadLen = 0;          // #bytes to read
int SegmentNumber = 0;    // #number to display in segment register

// functions


/*++
Routine Description:

Given the HardwareDeviceInfo, representing a handle to the plug and
play information, and deviceInfoData, representing a specific usb device,
open that device and fill in all the relevant information in the given
USB_DEVICE_DESCRIPTOR structure.

Arguments:

HardwareDeviceInfo:  handle to info obtained from Pnp mgr via SetupDiGetClassDevs()
DeviceInfoData:      ptr to info obtained via SetupDiEnumDeviceInterfaces()

Return Value:

return HANDLE if the open and initialization was successfull,
else INVLAID_HANDLE_VALUE.

--*/
HANDLE OpenOneDevice (IN       HDEVINFO                    HardwareDeviceInfo,
                      IN       PSP_DEVICE_INTERFACE_DATA   DeviceInfoData,
                      /*IN       char *devName*/
											IN wchar_t *devName)
{
    PSP_DEVICE_INTERFACE_DETAIL_DATA     functionClassDeviceData = NULL;
    ULONG                                predictedLength = 0;
    ULONG                                requiredLength = 0;
    HANDLE                                                           hOut = INVALID_HANDLE_VALUE;

    //
    // allocate a function class device data structure to receive the
    // goods about this particular device.
    //
    SetupDiGetDeviceInterfaceDetail (
        HardwareDeviceInfo,
        DeviceInfoData,
        NULL, // probing so no output buffer yet
        0, // probing so output buffer length of zero
        &requiredLength,
        NULL); // not interested in the specific dev-node


    predictedLength = requiredLength;
    // sizeof (SP_FNCLASS_DEVICE_DATA) + 512;

    functionClassDeviceData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) new UCHAR[predictedLength];
    if(NULL == functionClassDeviceData) {
        return INVALID_HANDLE_VALUE;
    }
    functionClassDeviceData->cbSize = sizeof (SP_DEVICE_INTERFACE_DETAIL_DATA);

    //
    // Retrieve the information from Plug and Play.
    //
    if (! SetupDiGetDeviceInterfaceDetail (
        HardwareDeviceInfo,
        DeviceInfoData,
        functionClassDeviceData,
        predictedLength,
        &requiredLength,
        NULL)) {
            delete []functionClassDeviceData;
            return INVALID_HANDLE_VALUE;
        }

        // strcpy( devName,functionClassDeviceData->DevicePath) ;
				wcscpy( devName,functionClassDeviceData->DevicePath) ;
        printf( "Attempting to open %s\n", devName );

        hOut = CreateFile (
            functionClassDeviceData->DevicePath,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL, // no SECURITY_ATTRIBUTES structure
            OPEN_EXISTING, // No special create flags
            0, // No special attributes
            NULL); // No template file

        if (INVALID_HANDLE_VALUE == hOut) {
            printf( "FAILED to open %s\n", devName );
        }
        delete []functionClassDeviceData;
        return hOut;
}


/*++
Routine Description:

Do the required PnP things in order to find
the next available proper device in the system at this time.

Arguments:

pGuid:      ptr to GUID registered by the driver itself
outNameBuf: the generated name for this device

Return Value:

return HANDLE if the open and initialization was successful,
else INVLAID_HANDLE_VALUE.
--*/
HANDLE OpenUsbDevice( LPGUID  pGuid, /*char */ wchar_t *outNameBuf)
{
    ULONG NumberDevices, OldNumberDevices;
    HANDLE hOut = INVALID_HANDLE_VALUE;
    HDEVINFO                 hardwareDeviceInfo;
    SP_DEVICE_INTERFACE_DATA deviceInfoData;
    ULONG                    i;
    BOOLEAN                  done;
    PUSB_DEVICE_DESCRIPTOR   usbDeviceInst;
    PUSB_DEVICE_DESCRIPTOR       *UsbDevices = &usbDeviceInst;
    PUSB_DEVICE_DESCRIPTOR   tempDevDesc;

    *UsbDevices = NULL;
    tempDevDesc = NULL;
    NumberDevices = 0;
    OldNumberDevices = 0;

    //
    // Open a handle to the plug and play dev node.
    // SetupDiGetClassDevs() returns a device information set that contains info on all
    // installed devices of a specified class.
    //
    hardwareDeviceInfo = SetupDiGetClassDevs (
        pGuid,
        NULL, // Define no enumerator (global)
        NULL, // Define no
        (DIGCF_PRESENT | // Only Devices present
        DIGCF_DEVICEINTERFACE)); // Function class devices.

    //
    // Take a wild guess at the number of devices we have;
    // Be prepared to realloc and retry if there are more than we guessed
    //
    NumberDevices = 4;
    done = FALSE;
    deviceInfoData.cbSize = sizeof (SP_DEVICE_INTERFACE_DATA);

    i=0;
    while (!done) {
        OldNumberDevices = NumberDevices;
        NumberDevices *= 2;

        if (*UsbDevices) {
            tempDevDesc = (PUSB_DEVICE_DESCRIPTOR) new UCHAR[(NumberDevices * sizeof (USB_DEVICE_DESCRIPTOR))];
            if(tempDevDesc) {
                memcpy(tempDevDesc,*UsbDevices,OldNumberDevices*sizeof (USB_DEVICE_DESCRIPTOR));
                delete []*UsbDevices;
                *UsbDevices = tempDevDesc;
                tempDevDesc = NULL;
            } else {
                delete []*UsbDevices;
                *UsbDevices = NULL;
            }
        } else {
            *UsbDevices = (PUSB_DEVICE_DESCRIPTOR) new UCHAR[(NumberDevices*sizeof (USB_DEVICE_DESCRIPTOR))];
        }

        if (NULL == *UsbDevices) {

            // SetupDiDestroyDeviceInfoList destroys a device information set
            // and frees all associated memory.

            SetupDiDestroyDeviceInfoList (hardwareDeviceInfo);
            return INVALID_HANDLE_VALUE;
        }

        usbDeviceInst = *UsbDevices + i;

        for (; i < NumberDevices; i++) {

            // SetupDiEnumDeviceInterfaces() returns information about device interfaces
            // exposed by one or more devices. Each call returns information about one interface;
            // the routine can be called repeatedly to get information about several interfaces
            // exposed by one or more devices.

            if (SetupDiEnumDeviceInterfaces (hardwareDeviceInfo,
                0, // We don't care about specific PDOs
                pGuid,
                i,
                &deviceInfoData)) {

                hOut = OpenOneDevice (hardwareDeviceInfo, &deviceInfoData, outNameBuf);
                if ( hOut != INVALID_HANDLE_VALUE ) {
                    done = TRUE;
                    break;
                }

            } else {
                if (ERROR_NO_MORE_ITEMS == GetLastError()) {
                    done = TRUE;
                    break;
                }
            }
        }
    }

    NumberDevices = i;

    // SetupDiDestroyDeviceInfoList() destroys a device information set
    // and frees all associated memory.

    SetupDiDestroyDeviceInfoList (hardwareDeviceInfo);
    delete []*UsbDevices;
    return hOut;
}




/*++
Routine Description:

Given a ptr to a driver-registered GUID, give us a string with the device name
that can be used in a CreateFile() call.
Actually briefly opens and closes the device and sets outBuf if successfull;
returns FALSE if not

Arguments:

pGuid:      ptr to GUID registered by the driver itself
outNameBuf: the generated zero-terminated name for this device

Return Value:

TRUE on success else FALSE

--*/
BOOL GetUsbDeviceFileName( LPGUID  pGuid, /*char */ wchar_t *outNameBuf)
{
    HANDLE hDev = OpenUsbDevice( pGuid, outNameBuf );
    if ( hDev != INVALID_HANDLE_VALUE )
    {
        CloseHandle( hDev );
        return TRUE;
    }
    return FALSE;

}

/*++
Routine Description:

Called by dumpUsbConfig() to open an instance of our device

Arguments:

None

Return Value:

Device handle on success else NULL

--*/
HANDLE open_dev()
{

    HANDLE hDEV = OpenUsbDevice( 
			// (LPGUID)&GUID_OSR_USBFX2LK_INTERFACE, 
			(LPGUID)&GUID_DEVINTERFACE_OSRUSBFX2,
			completeDeviceName);


    if (hDEV == INVALID_HANDLE_VALUE) {
        printf("Failed to open (%s) = %d", completeDeviceName, GetLastError());
    } else {
        printf("DeviceName = (%s)\n", completeDeviceName);
    }           

    return hDEV;
}


/*++
Routine Description:

Called by main() to open an instance of our device after obtaining its name

Arguments:

None

Return Value:

Device handle on success else NULL

--*/
HANDLE open_file( wchar_t *filename,ULONG Flags)
{

    int success = 1;
    HANDLE h;

    if ( !GetUsbDeviceFileName(
        // (LPGUID) &GUID_OSR_USBFX2LK_INTERFACE,
				(LPGUID)&GUID_DEVINTERFACE_OSRUSBFX2,
        completeDeviceName) )
    {
        NOISY(("Failed to GetUsbDeviceFileName err - %d\n", GetLastError()));
        return  INVALID_HANDLE_VALUE;
    }

    if((wcslen(completeDeviceName) + wcslen(filename)) > 255) {
        NOISY(("Failed to open handle - possibly long filename\n"));
        return INVALID_HANDLE_VALUE;
    }

    wcscat (completeDeviceName,
        filename
        );                                      

    printf("completeDeviceName = (%s)\n", completeDeviceName);

    h = CreateFile(completeDeviceName,
        Flags,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL);

    if (h == INVALID_HANDLE_VALUE) {
        NOISY(("Failed to open (%s) = %d", completeDeviceName, GetLastError()));
        success = 0;
    } else {
        NOISY(("Opened successfully.\n"));
    }           

    return h;
}

/*++
Routine Description:

Called by main() to dump usage info to the console when
the app is called with no parms or with an invalid parm

Arguments:

None

Return Value:

None

--*/
void usage()
{
    static int i=1;

    if (i) {
        printf("Usage for Read/Write test:\n");
        printf("-t [n] where n is number of bytes to read and write\n");
        printf("-c [n] where n is number of iterations (default = 1)\n");
        printf("-v verbose -- dumps read data\n");

        printf("\nUsage for USB and Endpoint info:\n");
        printf("-u to dump USB configuration and pipe info \n");
        i = 0;
    }
}


/*++
Routine Description:

Called by main() to parse command line parms

Arguments:

argc and argv that was passed to main()

Return Value:

Sets global flags as per user function request

--*/
void parse(int argc,char *argv[] )
{
    int i;

    if ( argc < 2 ) // give usage if invoked with no parms
        usage();

    for (i=0; i<argc; i++) {
        if (argv[i][0] == '-' ||
            argv[i][0] == '/') {
                switch(argv[i][1]) {
            case 't':
            case 'T':
                ReadLen = atoi(&argv[i+1][0]);
                WriteLen = ReadLen;
                fWrite = TRUE;
                fRead = TRUE;
                i++;
                break;
            case 'c':
            case 'C':
                IterationCount = atoi(&argv[i+1][0]);
                i++;
                break;
            case 'u':
            case 'U':
                fDumpUsbConfig = TRUE;
                i++;
                break;
            case 'v':
            case 'V':
                fDumpReadData = TRUE;
                i++;
                break;
            default:
                usage();
                }
            }
    }
}

/*++
Routine Description:

Called to verify read and write buffers match for loopback test

Arguments:

buffers to compare and length

Return Value:

TRUE if buffers match, else FALSE

--*/
BOOL compare_buffs(char *buff1, char *buff2, int length)
{
    int ok = 1;

    if (memcmp(buff1, buff2, length )) {

        // Edi, and Esi point to the mismatching char and ecx indicates the
        // remaining length.
        ok = 0;
    }


    return ok;
}

///////////////////////////////////////////////////////////////////////////////
//
// Dump
//
//  Called to do formatted ascii dump to console from io buffer.
//
//  INPUTS:
//
//      b  -  Address of buffer
//      len - length
//
//  OUTPUTS:
//
//      None
//
//  RETURNS:
//
//      None
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
void Dump(CHAR *b,int len)
     /*++
     Routine Description:

     Called to do formatted ascii dump to console of the io buffer

     Arguments:

     buffer and length

     Return Value:

     none

     --*/
{
    ULONG i;
    ULONG longLen = (ULONG)len / sizeof( ULONG );
    PULONG pBuf = (PULONG) b;

    // dump an ordinal ULONG for each sizeof(ULONG)'th byte
    printf("\n****** BEGIN DUMP LEN decimal %d, 0x%x\n", len,len);
    for (i=0; i<longLen; i++) {
        printf("%04X ", *pBuf++);
        if (i % NPERLN == (NPERLN - 1)) {
            printf("\n");
        }
    }
    if (i % NPERLN != 0) {
        printf("\n");
    }
    printf("\n****** END DUMP LEN decimal %d, 0x%x\n", len,len);
}





// Begin, routines for USB configuration dump (Cmdline "rwbulk -u" )


/*++
Routine Description:

Called to get ascii string of USB descriptor

Arguments:

PUSB_ENDPOINT_DESCRIPTOR->bDescriptorType or
PUSB_DEVICE_DESCRIPTOR->bDescriptorType or
PUSB_INTERFACE_DESCRIPTOR->bDescriptorType or
PUSB_STRING_DESCRIPTOR->bDescriptorType or
PUSB_POWER_DESCRIPTOR->bDescriptorType or
PUSB_CONFIGURATION_DESCRIPTOR->bDescriptorType

Return Value:

ptr to string

--*/
char *usbDescriptorTypeString(UCHAR bDescriptorType )
{

switch(bDescriptorType) {

        case USB_DEVICE_DESCRIPTOR_TYPE:
            return "USB_DEVICE_DESCRIPTOR_TYPE";

        case USB_CONFIGURATION_DESCRIPTOR_TYPE:
            return "USB_CONFIGURATION_DESCRIPTOR_TYPE";


        case USB_STRING_DESCRIPTOR_TYPE:
            return "USB_STRING_DESCRIPTOR_TYPE";


        case USB_INTERFACE_DESCRIPTOR_TYPE:
            return "USB_INTERFACE_DESCRIPTOR_TYPE";


        case USB_ENDPOINT_DESCRIPTOR_TYPE:
            return "USB_ENDPOINT_DESCRIPTOR_TYPE";


#ifdef USB_POWER_DESCRIPTOR_TYPE // this is the older definintion which is actually obsolete
            // workaround for temporary bug in 98ddk, older USB100.h file
        case USB_POWER_DESCRIPTOR_TYPE:
            return "USB_POWER_DESCRIPTOR_TYPE";
#endif

#ifdef USB_RESERVED_DESCRIPTOR_TYPE  // this is the current version of USB100.h as in NT5DDK

        case USB_RESERVED_DESCRIPTOR_TYPE:
            return "USB_RESERVED_DESCRIPTOR_TYPE";

        case USB_CONFIG_POWER_DESCRIPTOR_TYPE:
            return "USB_CONFIG_POWER_DESCRIPTOR_TYPE";

        case USB_INTERFACE_POWER_DESCRIPTOR_TYPE:
            return "USB_INTERFACE_POWER_DESCRIPTOR_TYPE";
#endif // for current nt5ddk version of USB100.h

        default:
            return "??? UNKNOWN!!"; 
}
}


/*++
Routine Description:

Called to get ascii string of endpt descriptor type

Arguments:

PUSB_ENDPOINT_DESCRIPTOR->bmAttributes

Return Value:

ptr to string

--*/
char *usbEndPointTypeString(UCHAR bmAttributes)
{
    UINT typ = bmAttributes & USB_ENDPOINT_TYPE_MASK;


    switch( typ) {
        case USB_ENDPOINT_TYPE_INTERRUPT:
            return "USB_ENDPOINT_TYPE_INTERRUPT";

        case USB_ENDPOINT_TYPE_BULK:
            return "USB_ENDPOINT_TYPE_BULK";        

        case USB_ENDPOINT_TYPE_ISOCHRONOUS:
            return "USB_ENDPOINT_TYPE_ISOCHRONOUS"; 

        case USB_ENDPOINT_TYPE_CONTROL:
            return "USB_ENDPOINT_TYPE_CONTROL";     

        default:
            return "??? UNKNOWN!!"; 
    }
}


/*++
Routine Description:

Called to get ascii string of USB_CONFIGURATION_DESCRIPTOR attributes

Arguments:

PUSB_CONFIGURATION_DESCRIPTOR->bmAttributes

Return Value:

ptr to string

--*/
char *usbConfigAttributesString(UCHAR bmAttributes)
{
    UINT typ = bmAttributes & USB_CONFIG_POWERED_MASK;
    static CHAR usbAttributesBuffer[256];

    memset(usbAttributesBuffer,0,sizeof(usbAttributesBuffer));

    switch( typ) {

        case USB_CONFIG_BUS_POWERED:
            strcat(usbAttributesBuffer,"USB_CONFIG_BUS_POWERED");
            break;

        case USB_CONFIG_SELF_POWERED:
            strcat(usbAttributesBuffer,"USB_CONFIG_SELF_POWERED");
            break;

        default:
            break;

    }

    if(bmAttributes & USB_CONFIG_REMOTE_WAKEUP) {
        strcat(usbAttributesBuffer," USB_CONFIG_REMOTE_WAKEUP");
    }

    return usbAttributesBuffer;
}


/*++
Routine Description:

Called to do formatted ascii dump to console of a USB config descriptor

Arguments:

ptr to USB configuration descriptor

Return Value:

none

--*/
void print_USB_CONFIGURATION_DESCRIPTOR(PUSB_CONFIGURATION_DESCRIPTOR cd)
{
    printf("\n===================\nUSB_CONFIGURATION_DESCRIPTOR\n");

    printf(
        "bLength = 0x%x, decimal %d\n", cd->bLength, cd->bLength
        );

    printf(
        "bDescriptorType = 0x%x ( %s )\n", cd->bDescriptorType, usbDescriptorTypeString( cd->bDescriptorType )
        );

    printf(
        "wTotalLength = 0x%x, decimal %d\n", cd->wTotalLength, cd->wTotalLength
        );

    printf(
        "bNumInterfaces = 0x%x, decimal %d\n", cd->bNumInterfaces, cd->bNumInterfaces
        );

    printf(
        "bConfigurationValue = 0x%x, decimal %d\n", cd->bConfigurationValue, cd->bConfigurationValue
        );

    printf(
        "iConfiguration = 0x%x, decimal %d\n", cd->iConfiguration, cd->iConfiguration
        );

    printf(
        "bmAttributes = 0x%x ( %s )\n", cd->bmAttributes, usbConfigAttributesString( cd->bmAttributes )
        );

    printf(
        "MaxPower = 0x%x, decimal %d\n", cd->MaxPower, cd->MaxPower
        );
}


/*++
Routine Description:

Called to do formatted ascii dump to console of a USB interface descriptor

Arguments:

ptr to USB interface descriptor

Return Value:

none

--*/
void print_USB_INTERFACE_DESCRIPTOR(PUSB_INTERFACE_DESCRIPTOR id, UINT ix)
{
    printf("\n-----------------------------\nUSB_INTERFACE_DESCRIPTOR #%d\n", ix);


    printf(
        "bLength = 0x%x\n", id->bLength
        );


    printf(
        "bDescriptorType = 0x%x ( %s )\n", id->bDescriptorType, usbDescriptorTypeString( id->bDescriptorType )
        );


    printf(
        "bInterfaceNumber = 0x%x\n", id->bInterfaceNumber
        );
    printf(
        "bAlternateSetting = 0x%x\n", id->bAlternateSetting
        );
    printf(
        "bNumEndpoints = 0x%x\n", id->bNumEndpoints
        );
    printf(
        "bInterfaceClass = 0x%x\n", id->bInterfaceClass
        );
    printf(
        "bInterfaceSubClass = 0x%x\n", id->bInterfaceSubClass
        );
    printf(
        "bInterfaceProtocol = 0x%x\n", id->bInterfaceProtocol
        );
    printf(
        "bInterface = 0x%x\n", id->iInterface
        );
}
/*++
Routine Description:

Called to do formatted ascii dump to console of a USB pipe information

Arguments:

ptr to USB pipe information

Return Value:

none

--*/
void print_USBD_PIPE_INFORMATION(PUSBD_PIPE_INFORMATION PipeInfo,ULONG PipeNumber)
{
    PUCHAR text = 0;
    printf("\n-----------------------------\nUSBD_PIPE_INFORMATION #%d\n", PipeNumber);

    printf(
        "MaximumPacketSize = 0x%x\n", PipeInfo->MaximumPacketSize
    );
    printf(
        "EndpointAddress = 0x%x\n", PipeInfo->EndpointAddress
    );
    printf(
        "Interval = 0x%x\n", PipeInfo->Interval
    );
    switch(PipeInfo->PipeType) {
        case UsbdPipeTypeControl:
            text = (PUCHAR) "UsbdPipeTypeControl";
            break;
        case UsbdPipeTypeIsochronous:
            text = (PUCHAR) "UsbdPipeTypeIsochronous";
            break;
        case UsbdPipeTypeBulk:
            text = (PUCHAR) "UsbdPipeTypeBulk";
            break;
        case UsbdPipeTypeInterrupt:
            text = (PUCHAR) "UsbdPipeTypeInterrupt";
            break;
    }
    printf(
        "PipeType = 0x%x %s\n", PipeInfo->PipeType,text
    );
    printf(
        "PipeHandle = 0x%p\n", PipeInfo->PipeHandle
    );
    printf(
        "MaximumTransferSize = 0x%x\n", PipeInfo->MaximumPacketSize
    );

}

/*++
Routine Description:

Called to do formatted ascii dump to console of a USB interface information

Arguments:

ptr to USB interface information

Return Value:

none

--*/
void print_USBD_INTERFACE_INFORMATION(PUSBD_INTERFACE_INFORMATION InterfaceInformation)
{
    printf("\n-----------------------------\nUSBD_INTERFACE_INFORMATION\n");


    printf(
        "Length = 0x%x\n", InterfaceInformation->Length
        );


    printf(
        "InterfaceNumber = 0x%x\n", InterfaceInformation->InterfaceNumber
        );


    printf(
        "AlternateSetting = 0x%x\n", InterfaceInformation->AlternateSetting
        );
    printf(
        "Class = 0x%x\n", InterfaceInformation->Class
        );
    printf(
        "SubClass = 0x%x\n", InterfaceInformation->SubClass
        );
    printf(
        "Protocol = 0x%x\n", InterfaceInformation->Protocol
        );
    printf(
        "InterfaceHandle = 0x%p\n", InterfaceInformation->InterfaceHandle
        );
    printf(
        "NumberofPipes = 0x%x\n", InterfaceInformation->NumberOfPipes
        );
    for(ULONG index = 0; index < InterfaceInformation->NumberOfPipes; index++) {
        print_USBD_PIPE_INFORMATION(&InterfaceInformation->Pipes[index],index);
    }
}

/*++
Routine Description:

Called to do formatted ascii dump to console of a USB endpoint descriptor

Arguments:

ptr to USB endpoint descriptor,
index of this endpt in interface desc

Return Value:

none

--*/
void print_USB_ENDPOINT_DESCRIPTOR(PUSB_ENDPOINT_DESCRIPTOR ed, int i)
{
    printf(
        "------------------------------\nUSB_ENDPOINT_DESCRIPTOR for Pipe%02d\n", i
        );

    printf(
        "bLength = 0x%x\n", ed->bLength
        );

    printf(
        "bDescriptorType = 0x%x ( %s )\n", ed->bDescriptorType, usbDescriptorTypeString( ed->bDescriptorType )
        );


    if ( USB_ENDPOINT_DIRECTION_IN( ed->bEndpointAddress ) ) {
        printf(
            "bEndpointAddress= 0x%x ( INPUT )\n", ed->bEndpointAddress
            );
    } else {
        printf(
            "bEndpointAddress= 0x%x ( OUTPUT )\n", ed->bEndpointAddress
            );
    }

    printf(
        "bmAttributes= 0x%x ( %s )\n", ed->bmAttributes, usbEndPointTypeString ( ed->bmAttributes )
        );


    printf(
        "wMaxPacketSize= 0x%x, decimal %d\n", ed->wMaxPacketSize, ed->wMaxPacketSize
        );
    printf(
        "bInterval = 0x%x, decimal %d\n", ed->bInterval, ed->bInterval
        );
}

/*++
Routine Description:

Called to do formatted ascii dump to console of  USB
configuration, interface, and endpoint descriptors
(Cmdline "rwbulk -u" )

Arguments:

handle to device

Return Value:

none

--*/
void rw_dev( HANDLE hDEV )
{
    UINT success;
    DWORD siz, nBytes;
    char buf[2048];
    PUSB_CONFIGURATION_DESCRIPTOR cd;
		/*
    PUSBD_INTERFACE_INFORMATION interfaceInformation;
		*/

    siz = sizeof(buf);

    if (hDEV == INVALID_HANDLE_VALUE) {
        NOISY(("DEV not open"));
        return;
    }

    success = DeviceIoControl(hDEV,
        // IOCTL_OSRUSBFX2_GET_CONFIGURATION_DESCRIPTOR,
				IOCTL_OSRUSBFX2_GET_CONFIG_DESCRIPTOR,
        0,
        0,
        buf,
        siz,
        &nBytes,
        NULL);


    if (success) {
        // ULONG i;
        // UINT  j, n;
        char *pch;

        pch = buf;
        // n = 0;

        cd = (PUSB_CONFIGURATION_DESCRIPTOR) pch;

        print_USB_CONFIGURATION_DESCRIPTOR( cd );

/*
        success = DeviceIoControl(hDEV,
            IOCTL_OSRUSBFX2_GET_INTERFACE_INFORMATION,
            0,
            0,
            buf,
            siz,
            &nBytes,
            NULL);

        if (success) {
            interfaceInformation = (PUSBD_INTERFACE_INFORMATION) buf;
            print_USBD_INTERFACE_INFORMATION(interfaceInformation);

        } else {
            NOISY(("IOCTL_OSRUSBFX2_GET_INTERFACE_INFORMATION complete, error = %d nBytes = %d\n", GetLastError(), nBytes));
        }
*/
    } else {
        NOISY(("IOCTL_OSRUSBFX2_GET_CONFIGURATION_DESCRIPTOR complete, error = %d nBytes = %d\n", GetLastError(), nBytes));
    }

    return;

}

/*++
Routine Description:

Called to do formatted ascii dump to console of  USB
configuration, interface, and endpoint descriptors
(Cmdline "rwbulk -u" )

Arguments:

handle to device

Return Value:

none

--*/
void segment_dev( HANDLE hDEV )
{
    UINT success;
    DWORD /*siz,*/ nBytes;
    unsigned char segmentToDisplay;

    if(SegmentNumber < 0 || SegmentNumber > 8) {
        NOISY(("Invalid Number"));
        return;
    }

    if (hDEV == INVALID_HANDLE_VALUE) {
        NOISY(("DEV not open"));
        return;
    }

    segmentToDisplay = (unsigned char) SegmentNumber;

    success = DeviceIoControl(hDEV,
        IOCTL_OSRUSBFX2_SET_BAR_GRAPH_DISPLAY,
        &segmentToDisplay,
        sizeof(unsigned char),
        NULL,
        0,
        &nBytes,
        NULL);

    NOISY(("request complete, success = %d nBytes = %d\n", success, nBytes));

    return;

}

int  setSegmentLight()
{
    HANDLE hDEV = open_dev();

    if ( hDEV )
    {
        segment_dev( hDEV );
        CloseHandle(hDEV);
    }

    return 0;
}

/*++
Routine Description:

Called to do formatted ascii dump to console of  USB
configuration, interface, and endpoint descriptors
(Cmdline "rwbulk -u" )

Arguments:

none

Return Value:

none

--*/
int  dumpUsbConfig()
{

    HANDLE hDEV = open_dev();

    if ( hDEV )
    {
        rw_dev( hDEV );
        CloseHandle(hDEV);
    }

    return 0;
}
//  End, routines for USB configuration and pipe info dump  (Cmdline "rwbulk -u" )



/*++
Routine Description:

Entry point to rwbulk.exe
Parses cmdline, performs user-requested tests

Arguments:

argc, argv  standard console  'c' app arguments

Return Value:

Zero

--*/
int _cdecl main(int argc,char *argv[])
{
    char *pinBuf = NULL, *poutBuf = NULL;
    DWORD nBytesRead, nBytesWrite /*, nBytes*/;
    ULONG i, j;
    int ok;
    UINT success;
    HANDLE hRead = INVALID_HANDLE_VALUE, hWrite = INVALID_HANDLE_VALUE;
    // char buf[1024];
    // clock_t start, finish;
    // ULONG totalBytes = 0L;
    // double seconds;
    ULONG fail = 0L;
    OVERLAPPED  rOverlapped;
    OVERLAPPED  wOverlapped;
    HANDLE      handleArray[2];
    HANDLE      hDEV;    
    UCHAR       bigBuf[512];


    parse(argc, argv );

    // dump USB configuation and pipe info
    if( fDumpUsbConfig ) {
        dumpUsbConfig();
        return 0;
    }

    if ( fShowSegment ) {
        setSegmentLight();
        return 0;
    }

    hDEV = open_dev();

    if(hDEV == INVALID_HANDLE_VALUE) {
        return 1;
    }

    if(fRead) {
        memset(&rOverlapped,0,sizeof(rOverlapped));
        rOverlapped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
        if(!rOverlapped.hEvent) {
            printf("CreateEvent Error %d.\n",GetLastError());
            return 1;
        }
        handleArray[0] = rOverlapped.hEvent;
    }

    if(fWrite) {
        memset(&wOverlapped,0,sizeof(wOverlapped));
        wOverlapped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
        if(!wOverlapped.hEvent) {
            printf("CreateEvent Error %d.\n",GetLastError());
            return 1;
        }
        handleArray[1] = wOverlapped.hEvent;
    }

    // doing a read, write, or both test
    if ((fRead) || (fWrite)) {

        if (fRead) {
            //
            // open the output file
            //
            if ( fDumpReadData ) { // round size to sizeof ULONG for readable dumping
                while( ReadLen % sizeof( ULONG ) )
                    ReadLen++;
            }

            hRead = hDEV;

            pinBuf = new CHAR[ReadLen];

        }

        if (fWrite) {

            if ( fDumpReadData ) { // round size to sizeof ULONG for readable dumping
                while( WriteLen % sizeof( ULONG ) )
                    WriteLen++;
            }

            hWrite = hDEV;
            poutBuf = new CHAR[WriteLen];
        }

        if(fRead) {
						/*
            //
            // Reset the Pipe.
            //
            USBFX2_PIPE_ENUM    pipeEnum = USBFx2BulkInPipe;
            ULONG               bytesReturned = 0;
            if(!DeviceIoControl(hRead,IOCTL_OSRUSBFX2_RESET_PIPE,
                            &pipeEnum,sizeof(USBFX2_PIPE_ENUM),
                            NULL,0,
                            &bytesReturned,NULL)) {
                DWORD error = GetLastError();
                printf("Failed To Reset  USBFx2BulkInPipe. %d\n",error);
                goto loopExit;
            }
						*/
        }
        if(fWrite) {
						/*
            //
            // Reset the Pipe.
            //
            USBFX2_PIPE_ENUM    pipeEnum = USBFx2BulkOutPipe;
            ULONG               bytesReturned = 0;
            if(!DeviceIoControl(hWrite,IOCTL_OSRUSBFX2_RESET_PIPE,
                            &pipeEnum,sizeof(USBFX2_PIPE_ENUM),
                            NULL,0,
                            &bytesReturned,NULL)) {
                DWORD error = GetLastError();
                printf("Failed To Reset  USBFx2BulkOutPipe. %d\n",error);
                goto loopExit;
            }
						*/
        }

        for (i=0; i<IterationCount; i++) {

            if (fWrite && poutBuf && hWrite != INVALID_HANDLE_VALUE) {

                PULONG pOut = (PULONG) poutBuf;
                ULONG  numLongs = WriteLen / sizeof( ULONG );
                //
                // put some data in the output buffer
                //

                for (j=0; j<numLongs; j++) {
                    *(pOut+j) = j;
                }

                //
                // send the write
                //

                if(WriteFile(hWrite,
                    poutBuf,
                    WriteLen,
                    &nBytesWrite,
                    &wOverlapped)) {
                        successes++;
                    } else {
                        DWORD status = GetLastError();
                        if(status != ERROR_IO_PENDING) {
                            errors++;
                            printf("WriteFile Error %d.\n",status);
                            goto loopExit;
                        } else {
                            successes++;
                        }
                    }

            }

            if (fRead && pinBuf) {

                success = ReadFile(hRead,
                    pinBuf,
                    ReadLen,
                    &nBytesRead,
                    &rOverlapped);

                if(success) {
                    successes++;
                } else {
                    DWORD status = GetLastError();
                    if(status != ERROR_IO_PENDING) {
                        errors++;
                        printf("ReadFile Error %d.\n",status);
                        goto loopExit;
                    } else {
                        successes++;
                    }
                }

                GetOverlappedResult(hRead,&rOverlapped,&nBytesRead,TRUE);
                GetOverlappedResult(hWrite,&wOverlapped,&nBytesWrite,TRUE);

                ResetEvent(handleArray[0]);
                ResetEvent(handleArray[1]);

                assert(static_cast<int>(nBytesWrite) == WriteLen);

                sprintf((char *)bigBuf,"W,R (%04.4d) : request %06.6d bytes -- %06.6d bytes written %06.6d bytes read",
                    i, ReadLen, nBytesWrite, nBytesRead );
                
                SetConsoleTitleA((char *)bigBuf);

                if (fWrite) {

                    //
                    // validate the input buffer against what
                    // we sent to the 82930 (loopback test)
                    //

                    ok = compare_buffs(pinBuf, poutBuf,  nBytesRead);

                    if( fDumpReadData ) {
                        printf("Dumping read buffer\n");
                        Dump( pinBuf, nBytesRead );     
                        printf("Dumping write buffer\n");
                        Dump( poutBuf, nBytesRead );

                    }

                    assert(ok);

                    if(ok != 1)
                        fail++;

                    assert(ReadLen == WriteLen);
                    assert(static_cast<int>(nBytesRead) == ReadLen);
                    assert(static_cast<int>(nBytesWrite) == WriteLen);
                }
            }

        }

loopExit:
        printf("successes = %d, errors = %d\n",successes++,errors++);

        if (pinBuf) {
            delete []pinBuf;
            pinBuf = NULL;
        }

        if (poutBuf) {
            delete []poutBuf;
            pinBuf = NULL;
        }

    }           

    if(hDEV !=  INVALID_HANDLE_VALUE)
        CloseHandle(hDEV);

    return 0;
}


