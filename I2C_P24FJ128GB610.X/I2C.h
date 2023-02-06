/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
/******************************************************************************
 * Change log                                                                 
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 15/06/22     1.0         Created log. Added to LCD_P24FJ128GB610
 * 16/06/22                 Added to MIDI_P24FJ128GB610
 * 27/10/22     1.1         Added to a new version at work.
 * 
 **************************************************************************** */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_H
#define	I2C_H

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
//#define LCD_DATA_TRIS       TRISB
//#define LCD_DATA_LAT        LATB
//#define LCD_DATA_PORT       LATB
//#define LCD_DATA_ANS        ANSB

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Function prototype                                                         */
/*----------------------------------------------------------------------------*/


extern void I2C_Init(unsigned int BRG);
extern void I2C_SendByte(unsigned char i2cAddr, unsigned char reg, unsigned char data);
extern void I2C_SendBurst(unsigned char i2cAddr, unsigned char reg, unsigned char* pcdata, unsigned char ndata);
extern unsigned char I2C_ReadByte(unsigned char i2cAddr, unsigned char reg);
extern void I2C_ReadBurst(unsigned char i2cAddr, unsigned char reg, unsigned char* pcdata, unsigned char ndata);
extern void I2C_WriteByte(unsigned char byte);
extern void I2C_Start(void);
extern void I2C_Stop(void);

/*----------------------------------------------------------------------------*/
/* Printf messages                                                            */
/*----------------------------------------------------------------------------*/
//static const unsigned char NoParityMSG[]   = {" with No parity bit"};

#endif	/* I2C_H */

