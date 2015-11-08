#include "stm32f30x.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_pwr.h"
#include "hw_config.h"
//#include "usb_type.h"

__IO uint32_t bDeviceState = UNCONNECTED; 			/* USB device status */
__IO bool fSuspendEnabled = true;					/* true when suspend is possible */

struct
{
	__IO RESUME_STATE eState;
	__IO uint8_t bESOFcnt;
} ResumeS;

RESULT PowerOn()
{
	uint16_t wRegVal;

	/*** cable plugged-in ? ***/
	USB_Cable_Config(ENABLE);

	/*** CNTR_PWDN = 0 ***/
	wRegVal = CNTR_FRES;
	_SetCNTR(wRegVal);

	/*** CNTR_FRES = 0 ***/
	wInterrupt_Mask = 0;
	_SetCNTR(wInterrupt_Mask);
	/*** Clear pending interrupts ***/
	_SetISTR(0);
	/*** Set interrupt mask ***/
	wInterrupt_Mask = CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM;
	_SetCNTR(wInterrupt_Mask);

	return USB_SUCCESS;
}

RESULT PowerOff()
{
	/* disable all interrupts and force USB reset */
	_SetCNTR(CNTR_FRES);
	/* clear interrupt status register */
	_SetISTR(0);
	/* Disable the Pull-Up*/
	USB_Cable_Config(DISABLE);
	/* switch-off device */
	_SetCNTR(CNTR_FRES + CNTR_PDWN);
	/* sw variables reset */
	/* ... */

	return USB_SUCCESS;
}

void Suspend()
{
	uint16_t wCNTR;
	/* suspend preparation */
	/* ... */

	/* macrocell enters suspend mode */
	wCNTR = _GetCNTR();
	wCNTR |= CNTR_FSUSP;
	_SetCNTR(wCNTR);

	/* ------------------ ONLY WITH BUS-POWERED DEVICES ---------------------- */
	/* power reduction */
	/* ... on connected devices */


	/* force low-power mode in the macrocell */
	wCNTR = _GetCNTR();
	wCNTR |= CNTR_LPMODE;
	_SetCNTR(wCNTR);

	/* switch-off the clocks */
	/* ... */
	Enter_LowPowerMode();
}

void Resume_Init(void)
{
	uint16_t wCNTR;

	/* ------------------ ONLY WITH BUS-POWERED DEVICES ---------------------- */
	/* restart the clocks */
	/* ...  */

	/* CNTR_LPMODE = 0 */
	wCNTR = _GetCNTR();
	wCNTR &= (~CNTR_LPMODE);
	_SetCNTR(wCNTR);


	/* restore full power */
	/* ... on connected devices */
	Leave_LowPowerMode();

	/* reset FSUSP bit */
	_SetCNTR(IMR_MSK);

	/* reverse suspend preparation */
	/* ... */
}

void Resume(RESUME_STATE eResumeSetVal)
{
	uint16_t wCNTR;

	if (eResumeSetVal != RESUME_ESOF)
		ResumeS.eState = eResumeSetVal;

	switch (ResumeS.eState)
	{
	case RESUME_EXTERNAL:
		Resume_Init();
		ResumeS.eState = RESUME_OFF;
		break;
	case RESUME_INTERNAL:
		Resume_Init();
		ResumeS.eState = RESUME_START;
		break;
	case RESUME_LATER:
		ResumeS.bESOFcnt = 2;
		ResumeS.eState = RESUME_WAIT;
		break;
	case RESUME_WAIT:
		ResumeS.bESOFcnt--;
		if (ResumeS.bESOFcnt == 0)
			ResumeS.eState = RESUME_START;
		break;
	case RESUME_START:
		wCNTR = _GetCNTR();
		wCNTR |= CNTR_RESUME;
		_SetCNTR(wCNTR);
		ResumeS.eState = RESUME_ON;
		ResumeS.bESOFcnt = 10;
		break;
	case RESUME_ON:
		ResumeS.bESOFcnt--;
		if (ResumeS.bESOFcnt == 0)
		{
			wCNTR = _GetCNTR();
			wCNTR &= (~CNTR_RESUME);
			_SetCNTR(wCNTR);
			ResumeS.eState = RESUME_OFF;
		}
		break;
	case RESUME_OFF:
	case RESUME_ESOF:
	default:
    	ResumeS.eState = RESUME_OFF;
    	break;
	}
}
