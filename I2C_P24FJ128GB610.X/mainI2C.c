/*
 * File:   mainI2C.c
 * Author: adrengineer
 *
 * Created on 4 de febrero de 2023, 11:13
 */


/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
//#include "xc.h"
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "config_bits.h"
#include "I2C.h"
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\LCD_P24FJ128GB610.X\lcd.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#define FALL_EDGE       1
#define RISE_EDGE       0

#define ACK_RUN_TRIS    TRISGbits.TRISG14
#define ACK_RUN_LAT     LATGbits.LATG14
#define ACK_RUN_PORT    PORTGbits.RG14

#define BRG             18
/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
unsigned char lcdline =0;
char LCDLINE;

int main(void) {
    char buf[20];

/******************************************************************************/   
/*****************************  REMAPPABLE PINS   *****************************/
/******************************************************************************/ 

    
/******************************************************************************/   
/*****************************  PORT CONFIGURATION  ***************************/                             
/******************************************************************************/ 
    ANSG = 0;
    ACK_RUN_TRIS = 0;
    
    
/******************************************************************************/   
/********************************  INITIALISING  ******************************/
/******************************************************************************/ 
    ACK_RUN_LAT     = 1;

    LCD_Init(18);
/******************************************************************************/   
/*********************************  MAIN LOOP  ********************************/     
/******************************************************************************/   
    
    
    while(1)
    {
        ACK_RUN_LAT = 1;
        __delay_ms(300);
        ACK_RUN_LAT = 0;
        __delay_ms(300);

        sprintf(buf,"hello world");
        LCD_WriteString(buf);
        __delay_ms(500);
    }
    return (0);
}
/******************************************************************************/       
/********************************  INTERRUPTS  ********************************/
/******************************************************************************/ 