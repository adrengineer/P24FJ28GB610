/*
 * File:   ADCmain.c
 * Author: adrengineer
 *
 * Created on 08 June 2022, 19:25
 * This file will flash the Acknowledge port at a frequency determine by the 
 * ADC read.
 */


/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "C:\Users\adren\Documents\Project-[G01]_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "config_bits.h"
#include "ADC.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#define ACK_RUN_TRIS    TRISGbits.TRISG14
#define ACK_RUN_LAT     LATGbits.LATG14
#define ACK_RUN_PORT    PORTGbits.RG14

#define POTL_CHANNEL    12
#define POTL_ANS        ANSBbits.ANSB12
#define POTL_TRIS       TRISBbits.TRISB12
#define POTL_LAT        LATBbits.LATB12
#define POTL_PORT       PORTBbits.RB12

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
unsigned int ADC_VALUE=1000;


int main(void) {
    int i,adc_value;
 
/******************************************************************************/   
/*****************************  PORT CONFIGURATION  ***************************/                             
/******************************************************************************/
    POTL_ANS        = 1;
    ACK_RUN_TRIS    = 0;
    POTL_TRIS       = 1;
    
#ifdef _INTERRUPTS
    INTCON2bits.GIE = 1;
#endif   
    
/******************************************************************************/   
/********************************  INITIALISING  ******************************/
/******************************************************************************/ 
    ACK_RUN_LAT     = 1;
    
    ADC_Init();
    ADC_ChannelSel(POTL_CHANNEL);
    ADC_On();
    ADC_Sample();

    
/******************************************************************************/   
/*********************************  MAIN LOOP  ********************************/     
/******************************************************************************/ 
    while(1){
        //ACK_RUN_LAT    ^= 1;
        for (unsigned int i = 0;i<ADC_VALUE;i++)__delay_us(100);
        
        #ifndef _INTERRUPT_ADC
        ADC_Sample();
        ADC_VALUE = ADC_Read();
        #endif
    }
}
/******************************************************************************/       
/********************************  INTERRUPTS  ********************************/
/******************************************************************************/
#ifdef INTERRUPT_ADC
void __attribute__ ((__interrupt__)) _ADC1Interrupt(void){
    ADC_VALUE = ADC1BUF0;
    
    IFS0bits.AD1IF = 0;  
}
#endif
