/*
 * File:   UART.h
 * Author: Adrengineer
 * Comments: 
 * 
 * Revision history
 */


/******************************************************************************
 * Change log                                                                 
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 25/01/21     1.0         Created log.
 * 04/11/22     1.1         Added to UART_P24FJ128GB610 project
 * 
 ***************************************************************************** */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART_H
#define	UART_H


/* -------------------------------------------------------------------------- */
/* Files to Include                                                           */
/* -------------------------------------------------------------------------- */
/* System funct/params, like osc/peripheral config */
#include "C:\Users\adren\Documents\Project-[G01]_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"      


/******************************************************************************
 * Uart character and word spacing
 *
 * This parameter modifies the amount of time waited between characters and
 *   words when printing over the UART.
 ***************************************************************************** */

#define CHARACTER_SPACING   5000

/*
 * A typical Character_Spacing value for fast printing is 5000. For slow
 *   printing 200,000 is common.
 */

#define WORD_SPACING        15000

/* -------------------------------------------------------------------------- */
/* Defines                                                                    */
/* -------------------------------------------------------------------------- */

#define YES                 1
#define NO                  0
#define UART_TX_INT_ON   		0b1000000000000000  // Transmit Shift Empty interrupt on
#define UART_TX_INT_OFF  		0b0000000000000000  // Transmit interrupt off
#define UART_TX_INT_MASK		(~UART_TX_INT_ON)	//Mask Trnasmit Interrupt select bit
#define USART_RX_INT_ON   		0b01000000  // Receive interrupt on
#define USART_RX_INT_OFF  		0b00000000  // Receive interrupt off
#define USART_RX_INT_MASK		(~USART_RX_INT_ON)	//Mask Receive Interrupt select bit
#define USART_ADDEN_ON    		0b00100000  // Enables address detection
#define USART_ADDEN_OFF   		0b00000000  // Disables address detection
#define USART_ADDEN_MASK		(~USART_ADDEN_ON)	//Mask address detection select bit
#define USART_BRGH_HIGH   		0b00010000  // High baud rate
#define USART_BRGH_LOW    		0b00000000  // Low baud rate
#define USART_BRGH_MASK			(~USART_BRGH_HIGH)	//Mask baud rate select bit
#define USART_CONT_RX     		0b00001000  // Continuous reception
#define USART_SINGLE_RX   		0b00000000  // Single reception
#define USART_CONT_RX_MASK		(~USART_CONT_RX) 	//Mask Continuous Reception select bit
#define USART_SYNC_MASTER 		0b00000100  // Synchrounous master mode
#define USART_SYNC_SLAVE  		0b00000000  // Synchrounous slave mode
#define USART_SYNC_MASK			(~USART_SYNC_MASTER)	//Mask usart mode select bit
#define USART_NINE_BIT    		0b00000010  // 9-bit data
#define USART_EIGHT_BIT   		0b00000000  // 8-bit data
#define USART_BIT_MASK 			(~USART_NINE_BIT)		//Mask 9 bit transmit  select bit
#define USART_SYNCH_MODE  		0b00000001  // Synchronous mode
#define USART_ASYNCH_MODE 		0b00000000  // Asynchronous mode
#define USART_MODE_MASK			(~USART_SYNCH_MODE) 	//Mask sync/async mode select bit
#define USART_BRG16             0b00001000  // Synchronous mode
#define SENDB                   0b00001000
#define BusyUSART( )            (!TX1STAbits.TRMT) //define with High CamelCase for library reference

    #if defined (__PIC24FJ128GB610__)
#define UART_UARTEN_EN          0b1000000000000000  //(bit 15)  UART EN
#define UART_UEN                0b0000000000000000  //(bit 9-8) UxTX, UxRX and UxRTS pins are enabled and used;
#define UART_ABAUD_LOW          0b0000000000000000  //(bit 5)   No auto-baud
#define UART_BRGH_LOW           0b0000000000000000  //(bit 3)   Standard speed mode /16
#define UART_PDSEL              0b0000000000000000  //(bit 2-1) 8-bit data, no parity
#define UART_STSEL_1STOP        0b0000000000000000  //(bit 0)   1 stop bit


#define UART_UTXISEL_8BIT_EMPTY 0b0000000000000000  //(bit 15,13) Interrupt when 8bits are empty
#define UART_URXISEL_8BIT_MORE  0b0000000000000000  //(bit 7-6) Interrupt when 1 word or more
#define UART_URXISEL_8BIT_RECV  0b0000000011000000  //(bit 7-6) Interrupt when 8 bits received
    #else
#define UART_MOD_ASY_8BIT       0b0000000000000000  //(bit 3-0) Asynchronous 8-bits
#define UART_ABAUD_LOW          0b0000000000000000  //(bit 6) No auto-baud
#define UART_BRGH_LOW           0b0000000000000000  //(bit 7) Standard speed mode /16
#define UART_UARTEN_EN          0b1000000000000000  //(bit 15)UART EN
#define UART_UTXEN_EN           0b0000000000100000  //(bit 5) Transmit enable
#define UART_URXEN_EN           0b0000000000010000  //(bit 4)Receive enable

#define UART_STSEL_1STOP        0b0000000000000000  //(bit 5-4) 1 stop bit

#define UART_UTXISEL_8BIT_EMPTY 0b0000000000000000  //(bit 14-12) Interrupt when 8bits are empty
#define UART_URXISEL_8BIT_MORE  0b0000000000000000  //(bit 10-8) Interrupt when 1 word or more
#define UART_URXISEL_8BIT_RECV  0b0000011100000000  //(bit 10-8) Interrupt when 8 bits received
    #endif


#define TX                      0b00000100 //RC2

/* -------------------------------------------------------------------------- */
/* Global Variables                                                           */
/* -------------------------------------------------------------------------- */
extern unsigned char RECEIVEDDATABUFFER[64];
extern unsigned char I;
extern unsigned char A;
extern unsigned char CTS;

/* -------------------------------------------------------------------------- */
/* Function prototypes                                                        */
/* -------------------------------------------------------------------------- */
void UART_Init(void);
void UART_Open(void);
void UART_Close(void );
unsigned char UART_ReadByte();
void UART_WriteByte(unsigned char caracter);
void UART_WriteString(char* cadena);
void UART_String(const unsigned char *data);
#ifdef _LCD_MODE
void putch(char p);
#endif


/* -------------------------------------------------------------------------- */
/* Printf messages                                                            */
/* -------------------------------------------------------------------------- */



#endif	/* UART_H */
