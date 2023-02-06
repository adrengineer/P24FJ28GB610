/* 
 * File: system.h    - P24FJ128GB610 REPOSITORY
 * Author: Adrengineer
 * Comments: 
 * Revision history: Common version to all projects
 */

/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 24/05/22     1.0         Initial project  INI_P24JF128GB256.X
 *                          The purpose is to have a single SYSTEM configuration 
 *                          file develop codes from different blocks.
 * 06/10/22     1.1         Modified to use internal oscillator.
 * 08/06/22     1.1         Added to project ADC_P24FJ128GB256.X
 * 01/11/22     1.1         Added to project TMR_P24FJ128GB256.X
 * 04/11/22     1.1         Added to project UART_P24FJ128GB610.X
 * 05/10/22     1.0         Added to project LCD_P24FJ128GB610.X
 ******************************************************************************/



/* -------------------------------------------------------------------------- */
/* Pre-Defines                                                                */
/* -------------------------------------------------------------------------- */

#define FOSC            8000000L  //L, is a way of casting 
#define FCY             (FOSC/2)
//#define FCY             4000000UL   //must be define before including the library
//#define _XTAL_FREQ      8000000   //In order to be able to use delay MACROS
#define _USE_FRC_CLOCK  0
#define _USE_PRI_CLOCK  1

/* -------------------------------------------------------------------------- */
/* Files to Include                                                           */
/* -------------------------------------------------------------------------- */
#ifndef SYSTEM_H
#define	SYSTEM_H

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


/* -------------------------------------------------------------------------- */
/* Include                                                                    */
/* -------------------------------------------------------------------------- */
#include <libpic30.h>           //Include delay macros for 16bits MCU


#include <xc.h>                 // XC8 General Include File 

#include <stdint.h>             /* For uint8_t definition */
#include <stdbool.h>            /* For true/false definition */
#include <stdio.h>
#include <string.h>             /* For memset,strcpy...*/
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/* Defines                                                                    */
/* -------------------------------------------------------------------------- */

#define FP 4000000UL
#define BAUDRATE 9600
#define BRGVAL ((unsigned long int)FCY/((unsigned long int)BAUDRATE*(unsigned long int)16))-1;
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


/* ************************************************************************** */
/* MIDI commands options                                                      */
/* ************************************************************************** */
#define _USE_SERIAL_MIDI    1
#define _USE_MPU_MIDI       0
#define _USE_USB_MIDI       0 

/* ************************************************************************** */
/* Debugging options                                                          */
/* ************************************************************************** */
#define _DEBUGGING          0
//#define _LCD_MODE           1
#define _INTERRUPTS         1
//#define _PMP                1
#define _I2C                1


#if defined (__PIC24FJ128GB610__)
    #define uno 1
#else
    #define two 2
#endif

#define _P24FJ128GB610      1
//#define _P24FJ128GB202      1


/* -------------------------------------------------------------------------- */
/* Macro Functions                                                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Function prototypes                                                        */
/* -------------------------------------------------------------------------- */



#endif	/* SYSTEM_H */
