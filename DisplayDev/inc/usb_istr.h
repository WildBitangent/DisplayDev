#pragma once
extern "C"
{
#include "usb_conf.h"

void USB_Istr();

/* function prototypes Automatically built defining related macros */

void EP1_IN_Callback();
void EP2_IN_Callback();
void EP3_IN_Callback(void);
void EP4_IN_Callback(void);
void EP5_IN_Callback(void);
void EP6_IN_Callback(void);
void EP7_IN_Callback(void);

void EP1_OUT_Callback(void);
void EP2_OUT_Callback();
void EP3_OUT_Callback(void);
void EP4_OUT_Callback(void);
void EP5_OUT_Callback(void);
void EP6_OUT_Callback(void);
void EP7_OUT_Callback(void);
}
