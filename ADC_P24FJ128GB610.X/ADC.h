/*
 * File:   ADC.h
 * Author: Adrian Moreno
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
 * 08/06/22     1.0         Created log.
 * 31/10/22     2.0         Modified at UnionAudio for DreamHat v3.0
 ***************************************************************************** */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H


/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "C:\Users\adren\Documents\Project-[G01]_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#ifdef _INTERRUPTS
    #define INTERRUPT_ADC 1
#endif

#define YES                 1
#define NO                  0

#define AD1CON1_ADON            0b1000000000000000 //(bit 15) A/D module is operating
#define AD1CON1_ADSIDL          0b0010000000000000 //(bit 13) stop in idle mode.
#define AD1CON1_MODE12          0b0000010000000000 //(bit 10) 12 bit mode.

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Function prototypes                                                        */
/*----------------------------------------------------------------------------*/
void ADC_Init(void);
void ADC_On(void);
void ADC_ChannelSel(unsigned char sel);
void ADC_Sample(void);
unsigned int ADC_Read(void);

/*----------------------------------------------------------------------------*/
/* Printf messages                                                            */
/*----------------------------------------------------------------------------*/



#endif	/* ADC_H */
