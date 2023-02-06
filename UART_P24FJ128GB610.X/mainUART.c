/*
 * File:   mainUART.c
 * Author: Adrengineer
 *
 * Created on 04 November 2022, 09:02
 */

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/


#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "config_bits.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#define ACK_RUN_TRIS    TRISGbits.TRISG14
#define ACK_RUN_LAT     LATGbits.LATG14
#define ACK_RUN_PORT    PORTGbits.RG14

#define BTN_ON_TRIS     TRISGbits.TRISG12   //P93_SWT2 
#define BTN_ON_LAT      LATGbits.LATG12     //P93_SWT2 
#define BTN_ON_PORT     PORTGbits.RG12      //P93_SWT2 

//#define SEND_MIDI   1
/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/


int main(void) {
/******************************************************************************/   
/*****************************  LOCAL VARIABLES  ******************************/
/******************************************************************************/ 
    
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
        #ifndef SEND_MIDI
        UART_WriteByte('a');
        __delay_ms(3);
        UART_WriteByte('b');
        __delay_ms(3);
        UART_WriteByte('c'); 
        __delay_ms(3);
        ACK_RUN_LAT ^= 1;
        __delay_ms(1000);
        #endif
        #ifdef SEND_MIDI        
        
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x63); __delay_ms(3); 
        UART_WriteByte(0x01);__delay_ms(3);  
         
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x62);__delay_ms(3);  
        UART_WriteByte(0x00);__delay_ms(3); 
        
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x06);__delay_ms(3);  
        UART_WriteByte(0x7F);__delay_ms(3); 
        
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x26);__delay_ms(3);  
        UART_WriteByte(0x7F);__delay_ms(3);
        
 
        
        ACK_RUN_LAT ^= 1;
        __delay_ms(5000);
        
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x63);__delay_ms(3);  
        UART_WriteByte(0x01); __delay_ms(3); 
         
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x62); __delay_ms(3); 
        UART_WriteByte(0x00); __delay_ms(3);
        
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x06);__delay_ms(3);  
        UART_WriteByte(0x00); __delay_ms(3);
        
        UART_WriteByte(0xB0);__delay_ms(3);
        UART_WriteByte(0x26);__delay_ms(3);  
        UART_WriteByte(0x7F);__delay_ms(3);
        
 
        
        ACK_RUN_LAT ^= 1;
        __delay_ms(5000);

        #endif

    }
    return (0);
}
/******************************************************************************/       
/********************************  INTERRUPTS  ********************************/
/******************************************************************************/