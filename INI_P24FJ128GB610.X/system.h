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
 *                          The purpose is to have a single SYSTEM configuration 
 *                          file develop codes from different blocks.
 ******************************************************************************/

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

/******************************************************************************/
/* System frequency
 *
 * This is the CPU clock frequency.
 *
 * For this system (PIC18F25Q10) the maximum internal clock is 64MHz.
 *
 ******************************************************************************/
#define FCY         100000000UL     //must be define before including the library
#define FOSC        64000000L       //L, is a way of casting 
#define _XTAL_FREQ  64000000        //In order to be able to use delay MACROS

#include <libpic30.h>


#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <stdio.h>
#include <string.h>         /* For memset,strcpy...*/
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/* Defines                                                                    */
/* -------------------------------------------------------------------------- */

#define FP 100000000UL
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
#define _USE_SERIAL_MIDI    0
#define _USE_MPU_MIDI       1
#define _USE_USB_MIDI       0 

/* ************************************************************************** */
/* Debugging options                                                          */
/* ************************************************************************** */
#define _DEBUGGING          0
#define _LCD_MODE           1




/* -------------------------------------------------------------------------- */
/* Macro Functions                                                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Function prototypes                                                        */
/* -------------------------------------------------------------------------- */



#endif	/* SYSTEM_H */