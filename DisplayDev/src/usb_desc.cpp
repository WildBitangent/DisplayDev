#include "usb_desc.h"
#include "usb_lib.h"

/* USB Standard Device Descriptor */
const uint8_t Display_DeviceDescriptor[] =
{
	SIZ_DEVICE_DESC,			/*bLength */
	0x01,						/*bDescriptorType*/
	0x00,						/*bcdUSB */
	0x02,
	0x00,						/*bDeviceClass*/
	0x00,						/*bDeviceSubClass*/
	0x00,						/*bDeviceProtocol*/
	0x40,						/*bMaxPacketSize 64*/
	0x50,						/*idVendor (0x1d50)*/
	0x1d,
	0xac,						/*idProduct = 0x60ac*/
	0x60,
	0x00,						/*bcdDevice rel. 2.00*/
	0x02,
	1,							/*Index of string descriptor describing manufacturer */
	2,							/*Index of string descriptor describing product*/
	3,							/*Index of string descriptor describing the device serial number */
	0x01						/*bNumConfigurations*/
};

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Display_ConfigDescriptor[] =
{
	0x09, 						/* bLength: Configuration Descriptor size */
	0x02,						/* bDescriptorType: Configuration */
	SIZ_CONFIG_DESC,			/* wTotalLength: Bytes returned 32*/
	0x00,
	0x01,						/*bNumInterfaces: 1 interface*/
	0x01,						/*bConfigurationValue: Configuration value*/
	0x00,						/*iConfiguration: Index of string descriptor describing the configuration*/
	0xE0,						/*bmAttributes: bus powered */
	0x32,						/*MaxPower 100 mA: this current is used for detecting Vbus*/

	/************** Descriptor of Display interface ****************/
	/* 09 */
	0x09,						/*bLength: Interface Descriptor size*/
	0x04,						/*bDescriptorType: Interface descriptor type*/
	0x00,						/*bInterfaceNumber: Number of Interface*/
	0x00,						/*bAlternateSetting: Alternate setting*/
	0x02,						/*bNumEndpoints*/
	0xFF,						/*bInterfaceClass: Vendor Specific*/
	0x00,						/*bInterfaceSubClass : none*/
	0x00,						/*nInterfaceProtocol : none*/
	0,							/*iInterface: Index of string descriptor*/			//PROBLEEEEEEEEEEEEEEEEEEEEEM 0x04 - update: nem!
	/******************** Descriptor of Display endpoint 1 ********************/
	/* 18 */
	0x07,						/*bLength: Endpoint Descriptor size*/
	0x05,						/*bDescriptorType:*/
	0x81,						/*bEndpointAddress: Endpoint Address (IN)*/
	0x02,						/*bmAttributes: Bulk endpoint*/
	0x40,						/*wMaxPacketSize: 64 Byte max */  					//CHANGE TO 320Bytes!
	0x00,
	0x00,						/*bInterval: Polling Interval */
	/******************** Descriptor of Display endpoint 2 ********************/
	/* 25 */
	0x07,						/*bLength: Endpoint Descriptor size*/
	0x05,						/*bDescriptorType:*/
	0x02,						/*bEndpointAddress: Endpoint Address (OUT)*/
	0x02,						/*bmAttributes: Bulk endpoint*/
	0x40,						/*wMaxPacketSize: 64 Byte max */  					//CHANGE TO 320Bytes! update: NEEEEEEIN!!!! :'(
	0x00,
	0x00,						/*bInterval: Polling Interval */
	/* 32 */
};

/* USB String Descriptors */
const uint8_t Display_StringLangID[] =
{
	SIZ_STRING_LANGID,
	0x03,
	0x09,
	0x04
}; /* LangID = 0x0409: U.S. English */

const uint8_t Display_StringVendor[] =
{
	SIZ_STRING_VENDOR,			/* Size of Vendor string */
    0x03,						/* bDescriptorType: String*/
	/* Manufacturer: "Macko S.R.OoO" -26bytes */
    'M', 0, 'a', 0, 'c', 0, 'k', 0, 'o', 0, ' ', 0, 'S', 0, '.', 0,
    'R', 0, '.', 0, 'O', 0, 'o', 0, 'O', 0
};

const uint8_t Display_StringProduct[] =
{
	SIZ_STRING_PRODUCT,			/* bLength */
	0x03,						/* bDescriptorType */
	// "Gay Machina" - 22bytes
	'G', 0, 'a', 0, 'y', 0, ' ', 0, 'M', 0, 'a', 0, 'c', 0, 'h', 0,
	'i', 0, 'n', 0, 'a', 0
};

uint8_t Display_StringSerial[] =
{
	SIZ_STRING_SERIAL,          	/* bLength */
	0x03,        					/* bDescriptorType */
	'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, '1', 0, '0', 0
};

