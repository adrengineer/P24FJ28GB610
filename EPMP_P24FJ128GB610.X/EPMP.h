/*
 * File:   EPMP.h
 * Author: adrengineer
 *
 * Created on 13 October 2022, 15:16
 */
/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 13/10/22     1.0         Initial project. EPMP_P24FJ128GB610 project.
 ******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef EPMP_H
#define	EPMP_H

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/

#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"

/* -------------------------------------------------------------------------- */
/* Defines                                                                    */
/* -------------------------------------------------------------------------- */


#ifdef _P24FJ128GB610

    // As defined in the following structure the pin connection is as follows:
        #define DATA_TRIS       TRISE
        #define DATA_LAT        LATE
        #define DATA_PORT       LATE
        #define DATA_ANS        ANSE
        /*USE TRIS AS TRICK TO CHEAT MPU WHEN NO ANS IS AVAILABLE*/
        #define CS_TRIS         TRISDbits.TRISD10   //P70_CS/_2
        #define CS_LAT          LATDbits.LATD10
        #define CS_PORT         PORTDbits.RD10

        #define RD_TRIS         TRISDbits.TRISD5    //P82_PMDR
        #define RD_LAT          LATDbits.LATD5
        #define RD_PORT         PORTDbits.RD5

        #define WR_TRIS         TRISDbits.TRISD4    //P81_PMWR
        #define WR_LAT          LATDbits.LATD4
        #define WR_PORT         PORTDbits.RD4

        #define A0_ANS          ANSBbits.ANSB15     //P44_PMA0 or  P67_PMBE
        #define A0_TRIS         TRISBbits.TRISB15   
        #define A0_LAT          LATBbits.LATB15
        #define A0_PORT         PORTBbits.RB15

        #define IRQ_TRIS        TRISAbits.TRISA5    //P61_IRQ
        #define IRQ_PORT        PORTAbits.RA5

        #define DB0_ANS         TRISEbits.TRISE0    //P93_D0
        #define DB1_ANS         TRISEbits.TRISE1    //P94_D1
        #define DB2_ANS         TRISEbits.TRISE2    //P98_D2
        #define DB3_ANS         TRISEbits.TRISE3    //P99_D3
        #define DB4_ANS         ANSEbits.ANSE4      //P100_D4
        #define DB5_ANS         TRISEbits.TRISE5    //P03_D5
        #define DB6_ANS         TRISEbits.TRISE6    //P04_D6
        #define DB7_ANS         TRISEbits.TRISE7    //P05_D7

        #define MASK_WRITE_TRIS 0b1111111100000000
        #define MASK_READ_TRIS  0b0000000011111111
        #define DB0_TRIS        TRISEbits.TRISE0    //P93_D0
        #define DB1_TRIS        TRISEbits.TRISE1    //P94_D1
        #define DB2_TRIS        TRISEbits.TRISE2    //P98_D2
        #define DB3_TRIS        TRISEbits.TRISE3    //P99_D3
        #define DB4_TRIS        TRISEbits.TRISE4    //P100_D4
        #define DB5_TRIS        TRISEbits.TRISE5    //P03_D5
        #define DB6_TRIS        TRISEbits.TRISE6    //P04_D6
        #define DB7_TRIS        TRISEbits.TRISE7    //P05_D7
        
        #define MASK_WRITE      0b1111111100000000
        #define DB0_LAT         LATEbits.LATE0      //P93_D0
        #define DB1_LAT         LATEbits.LATE1      //P94_D1
        #define DB2_LAT         LATEbits.LATE2      //P98_D2
        #define DB3_LAT         LATEbits.LATE3      //P99_D3
        #define DB4_LAT         LATEbits.LATE4      //P100_D4
        #define DB5_LAT         LATEbits.LATE5      //P03_D5
        #define DB6_LAT         LATEbits.LATE6      //P04_D6
        #define DB7_LAT         LATEbits.LATE7      //P05_D7

        #define DB0_PORT        PORTEbits.RE0       //P93_D0
        #define DB1_PORT        PORTEbits.RE1       //P94_D1
        #define DB2_PORT        PORTEbits.RE2       //P98_D2
        #define DB3_PORT        PORTEbits.RE3       //P99_D3
        #define DB4_PORT        PORTEbits.RE4       //P100_D4
        #define DB5_PORT        PORTEbits.RE5       //P03_D5
        #define DB6_PORT        PORTEbits.RE6       //P04_D6
        #define DB7_PORT        PORTEbits.RE7       //P05_D7
#endif
/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/

//extern char LCDLINE; //Needs to be added in main too.

/*----------------------------------------------------------------------------*/
/* Function prototypes                                                        */
/*----------------------------------------------------------------------------*/
void EPMP_Init(void);
void PMP_Init();

unsigned char _rdpmpbyte(void);
void _wrpmpbyte (unsigned char data);
unsigned char _rdpmpstat(void);
char _wrpmpstat (unsigned char data);

/*----------------------------------------------------------------------------*/
/* Printf messages                                                            */
/*----------------------------------------------------------------------------*/
//static const unsigned char NoParityMSG[]   = {" with No parity bit"};





#endif	/* EPMP_H */
