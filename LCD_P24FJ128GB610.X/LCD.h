/* 
 * File:   LCD.h  - P24FJ128GB610 REPOSITORY
 * Author: 
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
 * 5/10/22      1.0         Initial project. P24FJ128GB610.
 * 26/10/22     1.2         Added to project I2C_P24FJ128GB610
 ******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/

#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#ifdef _I2C
    #define _LCD_I2C 1
#endif  
#ifdef _LCD_I2C
    #include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\I2C_P24FJ128GB610.X\I2C.h"
#endif



/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#ifdef _P24FJ128GB202
// As defined in the following structure the pin connection is as follows:
    #define LCD_DATA_TRIS       TRISB
    #define LCD_DATA_LAT        LATB
    #define LCD_DATA_PORT       LATB
    #define LCD_DATA_ANS        ANSB

    #define LCD_EN_TRIS         TRISBbits.TRISB11  
    #define LCD_RW_TRIS         TRISBbits.TRISB10    
    #define LCD_RS_TRIS         TRISBbits.TRISB9  

    #define LCD_EN_LAT          LATBbits.LATB11  
    #define LCD_RW_LAT          LATBbits.LATB10     
    #define LCD_RS_LAT          LATBbits.LATB9  

    #define LCD_EN_PORT         PORTBbits.RB11      
    #define LCD_RW_PORT         PORTBbits.RB10      
    #define LCD_RS_PORT         PORTBbits.RB9  

    #define LCD_DB0_TRIS        TRISBbits.TRISB0   
    #define LCD_DB1_TRIS        TRISBbits.TRISB1    
    #define LCD_DB2_TRIS        TRISBbits.TRISB2    
    #define LCD_DB3_TRIS        TRISBbits.TRISB3    
    #define LCD_DB4_TRIS        TRISBbits.TRISB13   
    #define LCD_DB5_TRIS        TRISBbits.TRISB6   
    #define LCD_DB6_TRIS        TRISBbits.TRISB7   
    #define LCD_DB7_TRIS        TRISBbits.TRISB8 

    #define LCD_DB0_LAT         LATBbits.LATB0      
    #define LCD_DB1_LAT         LATBbits.LATB1     
    #define LCD_DB2_LAT         LATBbits.LATB2    
    #define LCD_DB3_LAT         LATBbits.LATB3     
    #define LCD_DB4_LAT         LATBbits.LATB13      
    #define LCD_DB5_LAT         LATBbits.LATB6      
    #define LCD_DB6_LAT         LATBbits.LATB7    
    #define LCD_DB7_LAT         LATBbits.LATB8     

    #define LCD_DB0_PORT        PORTBbits.RB0      
    #define LCD_DB1_PORT        PORTBbits.RB1       
    #define LCD_DB2_PORT        PORTBbits.RB2      
    #define LCD_DB3_PORT        PORTBbits.RB3     
    #define LCD_DB4_PORT        PORTBbits.RB13      
    #define LCD_DB5_PORT        PORTBbits.RB6      
    #define LCD_DB6_PORT        PORTBbits.RB7      
    #define LCD_DB7_PORT        PORTBbits.RB8   
#endif

#ifdef _P24FJ128GB610

    #ifdef _LCD_I2C
       #define SCL_TRIS TRISAbits.TRISA2
       #define SDA_TRIS TRISAbits.TRISA3 
    #else
    // As defined in the following structure the pin connection is as follows:
        #define LCD_DATA_TRIS       TRISE
        #define LCD_DATA_LAT        LATE
        #define LCD_DATA_PORT       LATE
        #define LCD_DATA_ANS        ANSE
        /*USE TRIS AS TRICK TO CHEAT MPU WHEN NO ANS IS AVAILABLE*/
        #define LCD_EN_ANS          ANSBbits.ANSB15     //P44_PMA0
        #define LCD_RW_ANS          TRISDbits.TRISD4    //P81_PMWR
        #define LCD_RS_ANS          TRISDbits.TRISD5    //P82_PMDR

        #define LCD_EN_TRIS         TRISBbits.TRISB15   //P44_PMA0
        #define LCD_RW_TRIS         TRISDbits.TRISD4    //P81_PMWR
        #define LCD_RS_TRIS         TRISDbits.TRISD5    //P82_PMDR

        #define LCD_EN_LAT          LATBbits.LATB15     //P44_PMA0
        #define LCD_RW_LAT          LATDbits.LATD4      //P81_PMWR
        #define LCD_RS_LAT          LATDbits.LATD5      //P82_PMDR

        #define LCD_EN_PORT         PORTBbits.RB15      //P44_PMA0
        #define LCD_RW_PORT         PORTDbits.RD4       //P81_PMWR
        #define LCD_RS_PORT         PORTDbits.RD5       //P82_PMDR

        #define LCD_DB0_ANS         TRISEbits.TRISE0    //P93_LCD_D0
        #define LCD_DB1_ANS         TRISEbits.TRISE1    //P94_LCD_D1
        #define LCD_DB2_ANS         TRISEbits.TRISE2    //P98_LCD_D2
        #define LCD_DB3_ANS         TRISEbits.TRISE3    //P99_LCD_D3
        #define LCD_DB4_ANS         ANSEbits.ANSE4      //P100_LCD_D4
        #define LCD_DB5_ANS         TRISEbits.TRISE5    //P03_LCD_D5
        #define LCD_DB6_ANS         TRISEbits.TRISE6    //P04_LCD_D6
        #define LCD_DB7_ANS         TRISEbits.TRISE7    //P05_LCD_D7

        #define LCD_DB0_TRIS        TRISEbits.TRISE0    //P93_LCD_D0
        #define LCD_DB1_TRIS        TRISEbits.TRISE1    //P94_LCD_D1
        #define LCD_DB2_TRIS        TRISEbits.TRISE2    //P98_LCD_D2
        #define LCD_DB3_TRIS        TRISEbits.TRISE3    //P99_LCD_D3
        #define LCD_DB4_TRIS        TRISEbits.TRISE4    //P100_LCD_D4
        #define LCD_DB5_TRIS        TRISEbits.TRISE5    //P03_LCD_D5
        #define LCD_DB6_TRIS        TRISEbits.TRISE6    //P04_LCD_D6
        #define LCD_DB7_TRIS        TRISEbits.TRISE7    //P05_LCD_D7

        #define LCD_DB0_LAT         LATEbits.LATE0      //P93_LCD_D0
        #define LCD_DB1_LAT         LATEbits.LATE1      //P94_LCD_D1
        #define LCD_DB2_LAT         LATEbits.LATE2      //P98_LCD_D2
        #define LCD_DB3_LAT         LATEbits.LATE3      //P99_LCD_D3
        #define LCD_DB4_LAT         LATEbits.LATE4      //P100_LCD_D4
        #define LCD_DB5_LAT         LATEbits.LATE5      //P03_LCD_D5
        #define LCD_DB6_LAT         LATEbits.LATE6      //P04_LCD_D6
        #define LCD_DB7_LAT         LATEbits.LATE7      //P05_LCD_D7

        #define LCD_DB0_PORT        PORTEbits.RE0       //P93_LCD_D0
        #define LCD_DB1_PORT        PORTEbits.RE1       //P94_LCD_D1
        #define LCD_DB2_PORT        PORTEbits.RE2       //P98_LCD_D2
        #define LCD_DB3_PORT        PORTEbits.RE3       //P99_LCD_D3
        #define LCD_DB4_PORT        PORTEbits.RE4       //P100_LCD_D4
        #define LCD_DB5_PORT        PORTEbits.RE5       //P03_LCD_D5
        #define LCD_DB6_PORT        PORTEbits.RE6       //P04_LCD_D6
        #define LCD_DB7_PORT        PORTEbits.RE7       //P05_LCD_D7
    #endif
#endif
    

/* The following are used for setting the I/O port direction register.*/

#define LCD_WRITE 0b00000001//struct lcd_pin_map const LCD_WRITE = {0,0,0,0,0}; // For write mode all pins are out
#define LCD_READ 0b00001111 //struct lcd_pin_map const LCD_READ = {0,0,0,0,15}; // For read mode data pins are in


#define     LCD_FIRST_ROW           128
#define     LCD_SECOND_ROW          192
#define     LCD_THIRD_ROW           148
#define     LCD_FOURTH_ROW          212
#define     LCD_CLEAR               0b00000001
#define     LCD_RETURN_HOME         0b00000010
#define     LCD_CURSOR_OFF          0x0c //12
#define     LCD_UNDERLINE_ON        0x0e //14
#define     LCD_BLINK_CURSOR_ON     0x0f //15
#define     LCD_MOVE_CURSOR_LEFT    0x10 //16
#define     LCD_MOVE_CURSOR_RIGHT   20
#define     LCD_TURN_OFF            0b00001000
#define     LCD_TURN_ON             0b00001100
#define     LCD_INC_ADDR            0b00000110
#define     LCD_DEC_ADDR            0b00000100
#define     LCD_LSHIFT_CURSOR       0b00010000   
#define     LCD_RSHIFT_CURSOR       0b00010100
#define     LCD_LSHIFT_DISPLAY      0b00011000   
#define     LCD_RSHIFT_DISPLAY      0b00011100
    
#ifdef _LCD_I2C
    #define LCD_BL              0x08
    #define LCD_EN              0x04
    #define LCD_RW              0x02
    #define LCD_RS              0x01
    #define devAddr             0x27 ////0b0100A2A1A0x --> A2A1A0=111
    /* ONLY 4 BITS MODE FUNCTIONS OPERATIVE*/
#endif

//#define     LCD_8BITS_MODE          1
#define     LCD_N_LINES             2


/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
//static char Custom_Char5x8[] = {
//  0b00011111,0b00010101,0b00011111,0b00010101,0b00011111,0b00010101,0b00011111,0b00000000, // Icon for solar panel - Code for CGRAM memory space 0
//};

extern char LCDLINE; //Needs to be added in main too.

extern __eds__ int* pointer;
/*----------------------------------------------------------------------------*/
/* Function prototypes                                                        */
/*----------------------------------------------------------------------------*/
void LCD_Init(unsigned int speed);
void LCD_Bus(unsigned char dato);
void LCD_Parameter(unsigned char data);
void LCD_Command(unsigned char cmd);
void LCD_GoToXY(char row, char col);
void putch(char p);
void LCD_WriteByte(char c);
void LCD_WriteString(char *dato);
//char LCD_GetXY(char row, char col);
//char LCD_ReadByte();
void InitCustomChars();

/*----------------------------------------------------------------------------*/
/* Printf messages                                                            */
/*----------------------------------------------------------------------------*/
static const unsigned char NoParityMSG[]   = {" with No parity bit"};
static const unsigned char OddParityMSG[]  = {" with Odd parity bit"};
static const unsigned char EvenParityMSG[] = {" with Even parity bit"};
static const unsigned char MarkParityMSG[] = {" with Mark bit"};
static const unsigned char SpaceParityMSG[] = {" with Space bit"};

#endif	/* LCD_H */