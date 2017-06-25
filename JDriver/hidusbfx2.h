/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
    PURPOSE.

Module Name:

    hidusbfx2.h
    
Abstract:

    common header file

Author:


Environment:

    kernel mode only

Notes:


Revision History:


--*/
#ifndef _HIDUSBFX2_H_

#define _HIDUSBFX2_H_

#pragma warning(disable:4200)  // suppress nameless struct/union warning
#pragma warning(disable:4201)  // suppress nameless struct/union warning
#pragma warning(disable:4214)  // suppress bit field types other than int warning
#include <initguid.h>
#include <wdm.h>
#include "usbdi.h"
#include "usbdlib.h"

#pragma warning(default:4200)
#pragma warning(default:4201)
#pragma warning(default:4214)
#include <wdf.h>
#include "wdfusb.h"

#pragma warning(disable:4201)  // suppress nameless struct/union warning
#pragma warning(disable:4214)  // suppress bit field types other than int warning
#include <hidport.h>

#define NTSTRSAFE_LIB
#include <ntstrsafe.h>

#include "trace.h"

#define _DRIVER_NAME_                 "HIDUSBFX2: "
#define POOL_TAG                      (ULONG) 'H2XF'
#define INPUT_REPORT_BYTES            1

#define CONSUMER_CONTROL_REPORT_ID    1
#define SYSTEM_CONTROL_REPORT_ID      2
#define DIP_SWITCHES_REPORT_ID        3
#define SEVEN_SEGMENT_REPORT_ID       4
#define BARGRAPH_REPORT_ID            5

#define CONSUMER_CONTROL_BUTTONS_BIT_MASK   ((UCHAR)0x7f)   // (first 7 bits)
#define SYSTEM_CONTROL_BUTTONS_BIT_MASK     ((UCHAR)0x80)

#define INTERRUPT_ENDPOINT_INDEX     (0)

#define SWICTHPACK_DEBOUNCE_TIME_IN_MS   10 

typedef UCHAR HID_REPORT_DESCRIPTOR, *PHID_REPORT_DESCRIPTOR;

//
// Define the vendor commands supported by device
//
#define HIDFX2_READ_SWITCH_STATE          0xD6
#define HIDFX2_READ_7SEGMENT_DISPLAY      0xD4
#define HIDFX2_READ_BARGRAPH_DISPLAY      0xD7
#define HIDFX2_SET_BARGRAPH_DISPLAY       0xD8
#define HIDFX2_IS_HIGH_SPEED              0xD9
#define HIDFX2_REENUMERATE                0xDA
#define HIDFX2_SET_7SEGMENT_DISPLAY       0xDB

//
// Bit masks for 7 segment display to be used with vendor command 
//
#define SEGMENT_BIT_1   (UCHAR)0x1
#define SEGMENT_BIT_2   (UCHAR)0x2
#define SEGMENT_BIT_3   (UCHAR)0x4
#define SEGMENT_BIT_4   (UCHAR)0x8
#define SEGMENT_BIT_5   (UCHAR)0x10
#define SEGMENT_BIT_6   (UCHAR)0x20
#define SEGMENT_BIT_7   (UCHAR)0x40
#define SEGMENT_BIT_8   (UCHAR)0x80

#define SEGMENT_DISPLAY_1 \
        SEGMENT_BIT_2     \
     |  SEGMENT_BIT_3

#define SEGMENT_DISPLAY_2 \
        SEGMENT_BIT_1     \
     |  SEGMENT_BIT_2     \
     |  SEGMENT_BIT_6     \
     |  SEGMENT_BIT_5     \
     |  SEGMENT_BIT_8     

#define SEGMENT_DISPLAY_3 \
        SEGMENT_BIT_1     \
     |  SEGMENT_BIT_2     \
     |  SEGMENT_BIT_6     \
     |  SEGMENT_BIT_3     \
     |  SEGMENT_BIT_8     

#define SEGMENT_DISPLAY_4 \
        SEGMENT_BIT_2     \
     |  SEGMENT_BIT_3     \
     |  SEGMENT_BIT_6     \
     |  SEGMENT_BIT_7     

#define SEGMENT_DISPLAY_5 \
        SEGMENT_BIT_1     \
     |  SEGMENT_BIT_3     \
     |  SEGMENT_BIT_6     \
     |  SEGMENT_BIT_7     \
     |  SEGMENT_BIT_8     

#define SEGMENT_DISPLAY_6 \
        SEGMENT_BIT_1     \
     |  SEGMENT_BIT_3     \
     |  SEGMENT_BIT_5     \
     |  SEGMENT_BIT_6     \
     |  SEGMENT_BIT_7     \
     |  SEGMENT_BIT_8     

#define SEGMENT_DISPLAY_7 \
        SEGMENT_BIT_1     \
     |  SEGMENT_BIT_2     \
     |  SEGMENT_BIT_3     

#define SEGMENT_DISPLAY_8 \
        SEGMENT_BIT_1     \
     |  SEGMENT_BIT_2     \
     |  SEGMENT_BIT_3     \
     |  SEGMENT_BIT_5     \
     |  SEGMENT_BIT_6     \
     |  SEGMENT_BIT_7     \
     |  SEGMENT_BIT_8     

#define BARGRAPH_LED_1_ON       0x1
#define BARGRAPH_LED_2_ON       0x2
#define BARGRAPH_LED_3_ON       0x4
#define BARGRAPH_LED_4_ON       0x8
#define BARGRAPH_LED_5_ON       0x10
#define BARGRAPH_LED_6_ON       0x20
#define BARGRAPH_LED_7_ON       0x40
#define BARGRAPH_LED_8_ON       0x80
#define BARGRAPH_LED_ALL_ON     0xff
#define BARGRAPH_LED_ALL_OFF    0x00

//
// This is the default report descriptor for the Hid device provided
// by the mini driver in response to IOCTL_HID_GET_REPORT_DESCRIPTOR.
// 
// AC: Aplication Control
// AL: Application Launch

//#ifdef USE_HARDCODED_HID_REPORT_DESCRIPTOR

//
// The default descriptor exposes three top level collections.
// The DIP switches trigger consumer control and system control
// buttons.
//

CONST  HID_REPORT_DESCRIPTOR           G_DefaultReportDescriptor[] = {
	// Consumer control collection
	0x05,0x01,                      // USAGE_PAGE (GENERAL DESKTOP)
	0x09,0x04,                      // USAGE (Joystick)
	0xa1, 0x01,                     // COLLECTION (Application)
	0xa1, 0x00,                     //   COLLECTION (Physical)



	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x30,                    //     USAGE (Y)
	0x09, 0x31,                    //     USAGE (X)
	0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
	0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x02,                    //     REPORT_COUNT (2)
	0x81, 0x02,                    //     INPUT (Data,Var,Rel)


	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x36,                    //     USAGE (WHEEL)
	0x15, 0x0,                     //     LOGICAL_MINIMUM (0)
	0x25, 0xff,                    //     LOGICAL_MAXIMUM (256)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Rel)

	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x39,                    //     USAGE (hat switch)
	0x15, 0x0,                     //     LOGICAL_MINIMUM (0)
	0x25, 0x08,                    //     LOGICAL_MAXIMUM (8)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x81, 0x06,                    //     INPUT (Data,Var,Rel)

	0x05, 0x09,                     //     USAGE_PAGE (Button)
	0x19, 0x01,                     //     USAGE_MINIMUM (Button 1)
	0x29, 0x08,                     //     USAGE_MAXIMUM (Button 8)
	0x15, 0x00,                     //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                     //     LOGICAL_MAXIMUM (1)
	0x95, 0x08,                     //     REPORT_COUNT (8)
	0x75, 0x01,                     //     REPORT_SIZE (1)
	0x81, 0x02,                     //     INPUT (Data,Var,Abs)

	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x36,                    //     USAGE (WHEEL)
	0x15, 0x0,                     //     LOGICAL_MINIMUM (0)
	0x25, 0xff,                    //     LOGICAL_MAXIMUM (256)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Rel)



	0xc0,                           //   END_COLLECTION
	0xc0
};

//
// This is the default HID descriptor returned by the mini driver
// in response to IOCTL_HID_GET_DEVICE_DESCRIPTOR. The size
// of report descriptor is currently the size of G_DefaultReportDescriptor.
//
CONST HID_DESCRIPTOR G_DefaultHidDescriptor = {
    0x09,   // length of HID descriptor
    0x21,   // descriptor type == HID  0x21
    0x0100, // hid spec release
    0x00,   // country code == Not Specified
    0x01,   // number of HID class descriptors
    { 0x22,   // descriptor type 
    sizeof(G_DefaultReportDescriptor) }  // total length of report descriptor
};

//#endif // USE_HARDCODED_HID_REPORT_DESCRIPTOR

#include <pshpack1.h>
typedef struct _HIDFX2_INPUT_REPORT {

	BYTE osx;

	BYTE osy;

	BYTE bWheel;

	BYTE hSwitch;

	BYTE btns;

	BYTE fWheel;

}HIDFX2_INPUT_REPORT, *PHIDFX2_INPUT_REPORT;


typedef struct _HIDFX2_FEATURE_REPORT {
    //
    //Report ID for the collection
    //
    BYTE ReportId;

    //
    //one-byte feature data from 7-segment display or bar graph
    //
    BYTE FeatureData;

}HIDFX2_FEATURE_REPORT, *PHIDFX2_FEATURE_REPORT;
#include <poppack.h>


typedef struct _DEVICE_EXTENSION{

    //
    //WDF handles for USB Target 
    //
    WDFUSBDEVICE      UsbDevice;
    WDFUSBINTERFACE   UsbInterface;
    WDFUSBPIPE        InterruptPipe;

    //
    //Device descriptor for the USB device
    //
    WDFMEMORY DeviceDescriptor;

    //
    // Switch state.
    //
    UCHAR    CurrentSwitchState;

    //
    // This variable stores state for the swicth that got toggled most recently
    // (the device returns the state of all the switches and not just the 
    // one that got toggled).
    //
    UCHAR    LatestToggledSwitch;

    //
    // Interrupt endpoints sends switch state when first started 
    // or when resuming from suspend. We need to ignore that data.
    //
    BOOLEAN  IsPowerUpSwitchState;
    
    //
    // WDF Queue for read IOCTLs from hidclass that get satisfied from 
    // USB interrupt endpoint
    //
    WDFQUEUE   InterruptMsgQueue;

    //
    // Handle debouncing of switchpack
    //
    WDFTIMER DebounceTimer;

} DEVICE_EXTENSION, * PDEVICE_EXTENSION;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_EXTENSION, GetDeviceContext)

//
// driver routine declarations
//
// This type of function declaration is for Prefast for drivers. 
// Because this declaration specifies the function type, PREfast for Drivers
// does not need to infer the type or to report an inference. The declaration
// also prevents PREfast for Drivers from misinterpreting the function type 
// and applying inappropriate rules to the function. For example, PREfast for
// Drivers would not apply rules for completion routines to functions of type
// DRIVER_CANCEL. The preferred way to avoid Warning 28101 is to declare the
// function type explicitly. In the following example, the DriverEntry function
// is declared to be of type DRIVER_INITIALIZE.
//
DRIVER_INITIALIZE DriverEntry;

EVT_WDF_DRIVER_DEVICE_ADD HidFx2EvtDeviceAdd;

EVT_WDF_IO_QUEUE_IO_INTERNAL_DEVICE_CONTROL HidFx2EvtInternalDeviceControl;

NTSTATUS
HidFx2GetHidDescriptor(
    IN WDFDEVICE Device,
    IN WDFREQUEST Request
    );

NTSTATUS
HidFx2GetReportDescriptor(
    IN WDFDEVICE Device,
    IN WDFREQUEST Request
    );


NTSTATUS
HidFx2GetDeviceAttributes(
    IN WDFREQUEST Request
    );

EVT_WDF_DEVICE_PREPARE_HARDWARE HidFx2EvtDevicePrepareHardware;

EVT_WDF_DEVICE_D0_ENTRY HidFx2EvtDeviceD0Entry;

EVT_WDF_DEVICE_D0_EXIT HidFx2EvtDeviceD0Exit;

PCHAR
DbgDevicePowerString(
    IN WDF_POWER_DEVICE_STATE Type
    );

NTSTATUS
HidFx2ConfigContReaderForInterruptEndPoint(
    PDEVICE_EXTENSION DeviceContext
    );

EVT_WDF_USB_READER_COMPLETION_ROUTINE HidFx2EvtUsbInterruptPipeReadComplete;

VOID
HidFx2CompleteReadReport(
    WDFDEVICE Device
    );

EVT_WDF_OBJECT_CONTEXT_CLEANUP HidFx2EvtDriverContextCleanup;

PCHAR
DbgHidInternalIoctlString(
    IN ULONG        IoControlCode
    );

NTSTATUS
HidFx2SendIdleNotification(
    IN WDFREQUEST Request
    );

NTSTATUS
HidFx2SetFeature(
    IN WDFREQUEST Request
    );

NTSTATUS
HidFx2GetFeature(
    IN WDFREQUEST Request,
    OUT PULONG BytesReturned
    );

EVT_WDF_IO_QUEUE_IO_CANCELED_ON_QUEUE HidFx2EvtIoCanceledOnQueue;

NTSTATUS
HidFx2GetSwitchState(
    IN WDFDEVICE Device,
    OUT PUCHAR SwitchState
    );

NTSTATUS
SendVendorCommand(
    IN WDFDEVICE Device,
    IN UCHAR VendorCommand,
    IN PUCHAR CommandData
    );

NTSTATUS
GetVendorData(
    IN WDFDEVICE Device,
    IN UCHAR VendorCommand,
    IN PUCHAR CommandData
    );


USBD_STATUS
HidFx2ValidateConfigurationDescriptor(  
    IN PUSB_CONFIGURATION_DESCRIPTOR ConfigDesc,
    IN ULONG BufferLength,
    _Inout_  PUCHAR *Offset
    );

EVT_WDF_TIMER HidFx2EvtTimerFunction;

#endif   //_HIDUSBFX2_H_

