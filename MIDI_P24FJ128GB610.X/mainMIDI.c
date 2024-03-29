/*
 * File:   mainMIDI.c
 * Author: adrengineer
 *
 * Created on 04 November 2022, 14:31
 */

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include <p24FJ128GB610.h>

#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "config_bits.h"
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\UART_P24FJ128GB610.X\uart.h"

#include "MIDI.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#define ACK_RUN_TRIS    TRISGbits.TRISG14
#define ACK_RUN_LAT     LATGbits.LATG14
#define ACK_RUN_PORT    PORTGbits.RG14

#define BTN_ON_TRIS     TRISGbits.TRISG12   //P93_SWT2 
#define BTN_ON_LAT      LATGbits.LATG12     //P93_SWT2 
#define BTN_ON_PORT     PORTGbits.RG12      //P93_SWT2 

#define RAMPVOL         1   //RAMP THE VOLUMEN UP
/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/


int main(void) {
/******************************************************************************/   
/*****************************  LOCAL VARIABLES  ******************************/
/******************************************************************************/ 
unsigned int volumen = 0;   
/******************************************************************************/   
/*****************************  REMAPPABLE PINS   *****************************/
/******************************************************************************/ 
    
/******************************************************************************/   
/*****************************  PORT CONFIGURATION  ***************************/                             
/******************************************************************************/
    ACK_RUN_TRIS    = 0;
    BTN_ON_TRIS     = 1;
    
   
/******************************************************************************/   
/********************************  INITIALISING  ******************************/
/******************************************************************************/ 
    ACK_RUN_LAT     = 1;
    __delay_ms(1000);
    ACK_RUN_LAT     = 0;
    
    UART_Init();
    UART_Open();
    
/******************************************************************************/   
/*********************************  MAIN LOOP  ********************************/     
/******************************************************************************/ 
    while(1){
        #ifndef RAMPVOL
        if(BTN_ON_PORT){
            MIDI_NRPNcommand(MIDI_CHANNEL0, 0x0100);
            MIDI_Value_14bits(MIDI_CHANNEL0, 14000);  
            while(BTN_ON_PORT);
            MIDI_NRPNcommand(MIDI_CHANNEL0, 0x0100);
            MIDI_Value_14bits(MIDI_CHANNEL0, 0);             
        }    
        #endif
        #ifdef RAMPVOL
        MIDI_NRPNcommand(MIDI_CHANNEL0, 0x0100);
        MIDI_Value_14bits(MIDI_CHANNEL0, volumen);
        
        if(volumen == 14000){ 
            volumen =9000;
            ACK_RUN_LAT ^= 1;
        __delay_ms(5000);
            MIDI_NRPNcommand(MIDI_CHANNEL0, 0x0100);
            MIDI_Value_14bits(MIDI_CHANNEL0, 000);
        }
        volumen=(volumen+10);
        #endif
    }
        
    return (0);
}
/******************************************************************************/       
/********************************  INTERRUPTS  ********************************/
/******************************************************************************/