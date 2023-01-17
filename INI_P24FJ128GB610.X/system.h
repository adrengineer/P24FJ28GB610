/* 
 * File: system.h  
 * Author: Adrian Moreno
 * Comments: 
 * Revision history: 
 */

/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 24/05/22     1.0         Initial project.
 * 25/05/22                 Added to MIDI_P24FJ128GB610.
 * 07/06/22                 Added to UART_P24FJ128GB610
 * 17/06/22                 Added to LCD_P24FJ128GB610
 ******************************************************************************/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef SYSTEM_H
#define	SYSTEM_H

#define __XC

/* ************************************************************************** */
/* Files to Include                                                           */
/* ************************************************************************** */
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif


/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
/******************************************************************************/
/* System frequency
 *
 * This is the CPU clock frequency.
 *
 * For this system (PIC18F25Q10) the maximum internal clock is 64MHz.
 *
 ******************************************************************************/
#define FCY 4000000UL
//#define FOSC        8000000L    //L, is a way of casting 
//#define _XTAL_FREQ  8000000     //In order to be able to use delay MACROS
#define _USE_FRC_CLOCK  0
#define _USE_PRI_CLOCK  1

#include <libpic30.h>

#define FP 40000000UL
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16)-1
#define DELAY_105uS asm volatile ("REPEAT, #4201"); Nop(); // 105uS delay
/******************************************************************************/
/* Reset reason                                                               */
/******************************************************************************/
#define RESET_HVDR    0x01
#define RESET_CMR     0x02
#define RESET_VREGS   0x04
#define RESET_EXTR    0x08
#define RESET_SWR     0x10
#define RESET_WDTO    0x20
#define RESET_BOR     0x40
#define RESET_POR     0x80

/******************************************************************************/
/* Wake-up scenario                                                           */
/******************************************************************************/
#define WAKE_ACTIVE 0
#define WAKE_SLEEP  1
#define WAKE_IDLE   2

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#define SYSCLK      FOSC
#define PBCLK       SYSCLK/2
#define MAX_USHORT  65535L

/******************************************************************************/
/* (ADC2)Analog-to-Digital converter with computation module                                                               */
/******************************************************************************/
#define ADC_VREF_VDD       0b00
#define ADC_CLK_128        0b111111
#define ADC_CH_ANA5        0b000101
#define ADC_CH_ANB5        0b001101
#define ADC_CH_ANB4        0b001100
#define ADC_R_JUST         0b1


#define _INTERRUPTS 1



/******************************************************************************/
/* Macro Functions                                                            */
/******************************************************************************/

/******************************************************************************/
/* Function prototypes                                                        */
/******************************************************************************/

/******************************************************************************/
/* Global Variables                                                           */
/******************************************************************************/


/******************************************************************************/
/* Printf messages                                                            */
/******************************************************************************/


#endif	/* SYSTEM_H */