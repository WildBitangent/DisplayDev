#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
#define Display_GetConfiguration          NOP_Process
//#define Display_SetConfiguration          NOP_Process
#define Display_GetInterface              NOP_Process
#define Display_SetInterface              NOP_Process
#define Display_GetStatus                 NOP_Process
#define Display_ClearFeature              NOP_Process
#define Display_SetEndPointFeature        NOP_Process
#define Display_SetDeviceFeature          NOP_Process
//#define Display_SetDeviceAddress          NOP_Process

void Display_init();
void Display_Reset();
void Display_SetConfiguration();
void Display_SetDeviceAddress ();
void Display_Status_In ();
void Display_Status_Out ();
uint8_t *usb_ControlCopyData(uint16_t Length);
RESULT Display_Data_Setup(uint8_t);
RESULT Display_NoData_Setup(uint8_t);
RESULT Display_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Display_GetDeviceDescriptor(uint16_t );
uint8_t *Display_GetConfigDescriptor(uint16_t);
uint8_t *Display_GetStringDescriptor(uint16_t);
#ifdef __cplusplus
}
#endif
