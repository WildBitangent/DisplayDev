#pragma once
extern "C"
{
/* defines how many endpoints are used by the device */
#define EP_NUM     (4)

/*-------------------------------------------------------------*/
/* --------------   Buffer Description Table  -----------------*/
/*-------------------------------------------------------------*/
/* buffer table base address */
#define BTABLE_ADDRESS      (0x00)

#define ENDP0_BUFFSIZE 64
#define ENDP1_TXBUFFSIZE 64
#define ENDP2_RXBUFFSIZE 64

/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (8 * EP_NUM)
#define ENDP0_TXADDR        (ENDP0_RXADDR + ENDP0_BUFFSIZE)

/* EP1  */
/* tx buffer base address */
#define ENDP1_TXADDR        (ENDP0_TXADDR + ENDP0_BUFFSIZE)

/* EP2  */
/* Rx buffer base address */
#define ENDP2_RXADDR        (ENDP1_TXADDR + ENDP1_TXBUFFSIZE)


/*-------------------------------------------------------------*/
/* -------------------   ISTR events  -------------------------*/
/*-------------------------------------------------------------*/
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_RESETM )

/* CTR service routines */
/* associated to defined endpoints */
/* #define  EP1_IN_Callback   NOP_Process*/
#define  EP2_IN_Callback   NOP_Process
#define  EP3_IN_Callback   NOP_Process
#define  EP4_IN_Callback   NOP_Process
#define  EP5_IN_Callback   NOP_Process
#define  EP6_IN_Callback   NOP_Process
#define  EP7_IN_Callback   NOP_Process

#define  EP1_OUT_Callback   NOP_Process
//#define  EP2_OUT_Callback   NOP_Process
#define  EP3_OUT_Callback   NOP_Process
#define  EP4_OUT_Callback   NOP_Process
#define  EP5_OUT_Callback   NOP_Process
#define  EP6_OUT_Callback   NOP_Process
#define  EP7_OUT_Callback   NOP_Process
}
