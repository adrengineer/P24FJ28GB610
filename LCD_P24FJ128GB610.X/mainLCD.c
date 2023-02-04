/*
 * File:   mainLCD.c
 * Author: adrengineer
 *
 * Created on 14 June 2022, 19:50
 */

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "C:\Users\adren\Documents\Project-[G01]_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "config_bits.h"
#include "LCD.h"


/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#define FALL_EDGE       1
#define RISE_EDGE       0

#define ACK_RUN_TRIS    TRISGbits.TRISG14
#define ACK_RUN_LAT     LATGbits.LATG14
#define ACK_RUN_PORT    PORTGbits.RG14


//MENU SETTINGS OBJECTS
#define MARK_BLINK_SELECTION    0   //1st charaction marked (0) OR blink(1) for selection


/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
char B1_Msg0[]     = {" HELLO"};
char B1_Msg1[]     = {"  world "};


char LCDLINE;


int main(void) {

    
/******************************************************************************/   
/********************* PORT CONFIGURATION *************************************/
/******************************************************************************/ 
    ACK_RUN_TRIS    = 0;

/******************************************************************************/   
/********************* INITIALISING    ****************************************/
/******************************************************************************/ 
    ACK_RUN_LAT     = 1;

    LCD_Init(18);
#if MARK_BLINK_SELECTION
    LCD_Command(LCD_BLINK_CURSOR_ON);
    __delay_ms(10);
#endif


/******************************************************************************/   
/*********************  MAIN LOOP  ********************************************/
/******************************************************************************/    
    while(1)
    {

        LCD_Command(LCD_CLEAR);
        __delay_ms(10);
        LCD_WriteString(B1_Msg0);
        __delay_ms(10);
        LCD_GoToXY(2,1);
        __delay_ms(10);
        LCD_WriteString(B1_Msg1);
        __delay_ms(20);

        ACK_RUN_LAT ^= 1;
        __delay_ms(2000);

    }
    return (0);
}

