/*
 * File:   ADC.c  - P24FJ128GB610 REPOSITORY
 * Author: adrengineer
 *
 * Created on 08 June 2022, 21:59
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
 * 
 ***************************************************************************** */

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "ADC.h"  

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* User Global Variable Declaration                                           */
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/* Functions                                                                  */
/*----------------------------------------------------------------------------*/

/* ************************************************************************** */
/* @Brief: Initialise the ADC module                                          */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void ADC_Init(void){

    /* Initialise ADC module */
    AD1CON2bits.PVCFG = 0x00 ;      //positive ref voltage in built
    AD1CON2bits.NVCFG0 = 0x0 ;      //neg ref voltage in built
    AD1CON3bits.ADCS = 0b00111111;  //conversion clock source period
    AD1CON1bits.SSRC = 0b0000;      //manual conversion trigger
                                    //manual start of sampling (ASAM=0) 
 // AD1CON3bits.SAMC = 0b10000;     //auto sample time select bit
    AD1CON1bits.FORM = 0b00;        //integer form,unsigned 
    AD1CON2bits.SMPI = 0x0;         //
    AD1CON1bits.MODE12 = 1;         //12/10 bit 
    AD1CON3bits.ADRC = 0;           //A/D conversion clock source bit
    
#if INTERRUPT_ADC 
    IPC3bits.AD1IP  = 4;
    IFS0bits.AD1IF = 0;             // interrupt flag 
    IEC0bits.AD1IE = 1;             //interrupt enable
#endif
            
}

/* ************************************************************************** */
/* @Brief:                                                                    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void ADC_On(void){
    AD1CON1bits.ADON = 1;           // on A/D module
}

/* ************************************************************************** */
/* @Brief:                                                                    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void ADC_ChannelSel(unsigned char sel){
    AD1CHS = sel;                   //input channel 
}
/* ************************************************************************** */
/* @Brief:                                                                    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void ADC_Sample(void){
    AD1CON1bits.SAMP = 1;           //Start sampling
    for(char i=0;i<100;i++){             // some delay for sampling min 2Tad
        Nop();
    }

   AD1CON1bits.SAMP = 0;           //End sampling and Start conversion
   for(char i=0;i<100;i++){              // some delay for sampling min 2Tad
         Nop();
    } 
}
/* ************************************************************************** */
/* @Brief:                                                                    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
unsigned int ADC_Read(void){


    while(!AD1CON1bits.DONE);       //Wait for conversion to complete

    return ADC1BUF0;
}