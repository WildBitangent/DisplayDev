#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"
#include <stddef.h>

//uint32_t ProtocolValue;

static uint8_t * s_pbyControlRequestData = NULL;
static uint16_t s_wControlRequestDataSize = 0;

DEVICE Device_Table =
{
	EP_NUM,
	1
};

DEVICE_PROP Device_Property =
{
	Display_init,
	Display_Reset,
	Display_Status_In,
	Display_Status_Out,
	Display_Data_Setup,
	Display_NoData_Setup,
	Display_Get_Interface_Setting,
	Display_GetDeviceDescriptor,
	Display_GetConfigDescriptor,
	Display_GetStringDescriptor,
	0,
	0x40								/*MAX PACKET SIZE*/
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
	Display_GetConfiguration,
	Display_SetConfiguration,
	Display_GetInterface,
	Display_SetInterface,
	Display_GetStatus,
	Display_ClearFeature,
	Display_SetEndPointFeature,
	Display_SetDeviceFeature,
	Display_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
	(uint8_t*)Display_DeviceDescriptor,
	SIZ_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
	(uint8_t*)Display_ConfigDescriptor,
	SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
	{(uint8_t*)Display_StringLangID, SIZ_STRING_LANGID},
	{(uint8_t*)Display_StringVendor, SIZ_STRING_VENDOR},
	{(uint8_t*)Display_StringProduct, SIZ_STRING_PRODUCT},
	{(uint8_t*)Display_StringSerial, SIZ_STRING_SERIAL}
};

void Display_init()
{
	pInformation->Current_Configuration = 0;

	/* Connect the device */
	PowerOn();

	/* Perform basic device initialization operations */
	USB_SIL_Init();

	bDeviceState = UNCONNECTED;
}


void Display_Reset()
{
	/* Set Display_DEVICE as not configured */
	pInformation->Current_Configuration = 0;
	pInformation->Current_Interface = 0;/*the default Interface*/

	/* Current Feature initialization */
	pInformation->Current_Feature = Display_ConfigDescriptor[7];

	SetBTABLE(BTABLE_ADDRESS);

	/* Initialize Endpoint 0 */
	SetEPType(ENDP0, EP_CONTROL);
	SetEPTxStatus(ENDP0, EP_TX_NAK);
	SetEPRxAddr(ENDP0, ENDP0_RXADDR);
	SetEPTxAddr(ENDP0, ENDP0_TXADDR);
	Clear_Status_Out(ENDP0);
	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
	SetEPRxValid(ENDP0);

	/* Initialize Endpoint 1 */
	SetEPType(ENDP1, EP_BULK);
	SetEPTxAddr(ENDP1, ENDP1_TXADDR);
	SetEPRxStatus(ENDP1, EP_RX_DIS);
	SetEPTxStatus(ENDP1, EP_TX_NAK);

	/* Initialize Endpoint 2 */
	SetEPType(ENDP2, EP_BULK);
	SetEPRxAddr(ENDP2, ENDP2_RXADDR);
	SetEPRxCount(ENDP2, Device_Property.MaxPacketSize);
	SetEPRxStatus(ENDP2, EP_RX_VALID);
	SetEPTxStatus(ENDP2, EP_TX_DIS);

	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
	SetEPRxValid(ENDP0);

	/* Set this device to response on default address */
	SetDeviceAddress(0);

	bDeviceState = ATTACHED;
}

void Display_SetConfiguration(void)
{
	DEVICE_INFO *pInfo = &Device_Info;

	if (pInfo->Current_Configuration != 0)
	{
		/* Device configured */
		bDeviceState = CONFIGURED;
	}
}

void Display_SetDeviceAddress ()
{
	bDeviceState = ADDRESSED;
}

void Display_Status_In()
{}

void Display_Status_Out ()
{}

uint8_t *usb_ControlCopyData(uint16_t Length)
{
	if (Length == 0)
	{
		pInformation->Ctrl_Info.Usb_wLength = s_wControlRequestDataSize;
		return NULL;
	}
	else
	{
		return s_pbyControlRequestData;
	}
}

RESULT Display_Data_Setup(uint8_t RequestNo)
{
//	if ( ( VENDOR_REQUEST == (pInformation->USBbmRequestType & REQUEST_TYPE) ) &&
//	     ( INTERFACE_RECIPIENT == (pInformation->USBbmRequestType & RECIPIENT) ) &&
//	     ( pInformation->USBwIndexs.bw.bb1 == 0 ) )
//	{
//	    pInformation->Ctrl_Info.CopyData = usb_ControlCopyData;
//	    s_wControlRequestDataSize = WinUSBComm_Control(RequestNo, &s_pbyControlRequestData, pInformation->USBwLengths.w);
//	    pInformation->Ctrl_Info.Usb_wLength = s_wControlRequestDataSize;
//	}
//
//	return USB_SUCCESS; // USB_UNSUPPORT

//	uint8_t *(*CopyRoutine)(uint16_t);
//
//	CopyRoutine = NULL;
//
//	pInformation->Ctrl_Info.CopyData = CopyRoutine;
//	pInformation->Ctrl_Info.Usb_wOffset = 0;
//	(*CopyRoutine)(0);
//	return USB_SUCCESS;
}

RESULT Display_NoData_Setup(uint8_t RequestNo)
{
//	if ( ( VENDOR_REQUEST == (pInformation->USBbmRequestType & REQUEST_TYPE) ) &&
//	     ( INTERFACE_RECIPIENT == (pInformation->USBbmRequestType & RECIPIENT) ) &&
//	     ( pInformation->USBwIndexs.bw.bb1 == 0 ) )
//	{
//	    WinUSBComm_Control(RequestNo, NULL, 0);
//	}
//
//    return USB_SUCCESS;
}

RESULT Display_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
	if (AlternateSetting > 0)
	{
		return USB_UNSUPPORT;
	}
	else if (Interface > 0)
	{
		return USB_UNSUPPORT;
	}
	return USB_SUCCESS;
}

uint8_t *Display_GetDeviceDescriptor(uint16_t Length)
{
	return Standard_GetDescriptorData(Length, &Device_Descriptor );
}

uint8_t *Display_GetConfigDescriptor(uint16_t Length)
{
	return Standard_GetDescriptorData(Length, &Config_Descriptor );
}

uint8_t *Display_GetStringDescriptor(uint16_t Length)
{
	uint8_t wValue0 = pInformation->USBwValue0;

	if (wValue0 > 4)
	{
		return NULL;
	}
	else
	{
		return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
	}
}
