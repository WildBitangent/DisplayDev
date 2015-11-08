#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "usb_istr.h"

volatile uint16_t wIstr;				/* ISTR register last read value */
volatile uint8_t bIntPackSOF = 0;		/* SOFs received between 2 consecutive packets */

void (*pEpInt_IN[7])() =
{
    EP1_IN_Callback,
    EP2_IN_Callback,
    EP3_IN_Callback,
    EP4_IN_Callback,
    EP5_IN_Callback,
    EP6_IN_Callback,
    EP7_IN_Callback,
};

void (*pEpInt_OUT[7])() =
{
    EP1_OUT_Callback,
    EP2_OUT_Callback,
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
};

void USB_Istr()
{
	wIstr = _GetISTR();

	if (wIstr & ISTR_CTR & wInterrupt_Mask)
	{
		/* servicing of the endpoint correct transfer interrupt */
		/* clear of the CTR flag into the sub */
		CTR_LP();
	}

	if (wIstr & ISTR_RESET & wInterrupt_Mask)
	{
		_SetISTR((uint16_t)CLR_RESET);
		Device_Property.Reset();
	}
}
