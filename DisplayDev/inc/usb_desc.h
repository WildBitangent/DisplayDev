#pragma once
extern "C"
{
#include <stdint.h>

#define SIZ_DEVICE_DESC             0x12
#define SIZ_CONFIG_DESC             0x20

#define SIZ_STRING_LANGID           0x04
#define SIZ_STRING_VENDOR			28
#define SIZ_STRING_PRODUCT			24
#define SIZ_STRING_SERIAL			26

extern const uint8_t Display_DeviceDescriptor[];
extern const uint8_t Display_ConfigDescriptor[];
extern const uint8_t Display_StringLangID[];
extern const uint8_t Display_StringVendor[];
extern const uint8_t Display_StringProduct[];
extern uint8_t Display_StringSerial[];
}
