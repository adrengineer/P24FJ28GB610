/*
 * File:   mainTMR.c
 * Author: adrengineer
 *
 * Created on 01 November 2022, 10:06
 * This project will toggle the acknowledge port at a frequency determine by 
 * timer in use.
 */

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include <p24FJ128GB610.h>

#include "C:\Users\adren\Documents\Project-[G01]_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "config_bits.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
//Choose one
//#define ACTIVE_TIMER1   1
//#define ACTIVE_TIMER2   1
#define ACTIVE_TIMER3   1
//#define ACTIVE_TIMER4   1
//#define ACTIVE_TIMER5   1
//#define ACTIVE_TIMER23  1
//#define ACTIVE_TIMER45  1

#if defined (__PIC24FJ128GB610__)
    //#define PRESCALER_1_1       
    //#define PRESCALER_1_8       
    //#define PRESCALER_1_64      
    #define PRESCALER_1_256     

    #ifdef PRESCALER_1_1
    #define PRESCALER   1
    #define T_PS        0b00
    #endif
    #ifdef PRESCALER_1_8
    #define PRESCALER   8
    #define T_PS        0b01
    #endif
    #ifdef PRESCALER_1_64
    #define PRESCALER   64
    #define T_PS        0b10
    #endif
    #ifdef PRESCALER_1_256
    #define PRESCALER   256
    #define T_PS        0b11
    #endif


#endif

//Don't use zeros in front, it will be consider octal
#define T1_TIME         1600       //Max = 65535   
#define T1_TIME_S(a)    ((unsigned int)((float)(a)*FCY))     
#define T1_TIME_mS(a)   ((unsigned int)(((float)((float)a/(float)1000))*(float)(FCY/PRESCALER))) 
#define T1_TIME_uS(a)   ((unsigned int)((((float)a/(float)1000000))*(FCY/PRESCALER))) 

#define T2_TIME         35530      //Max = 65535 
#define T2_TIME_S(a)    ((unsigned int)((float)(a)*FCY))     
#define T2_TIME_mS(a)   ((unsigned int)(((float)((float)a/(float)1000))*(float)(FCY/PRESCALER))) 
#define T2_TIME_uS(a)   ((unsigned int)((((float)a/(float)1000000))*(FCY/PRESCALER))) 

#define T3_TIME         5       //Max = 65535  
#define T3_TIME_S(a)    ((unsigned int)((float)(a)*FCY))     
#define T3_TIME_mS(a)   ((unsigned int)(((float)((float)a/(float)1000))*(float)(FCY/PRESCALER))) 
#define T3_TIME_uS(a)   ((unsigned int)((((float)a/(float)1000000))*(FCY/PRESCALER))) 

#define T4_TIME         2000       //Max = 65535 
#define T4_TIME_S(a)    ((unsigned int)((float)(a)*FCY))     
#define T4_TIME_mS(a)   ((unsigned int)(((float)((float)a/(float)1000))*(float)(FCY/PRESCALER))) 
#define T4_TIME_uS(a)   ((unsigned int)((((float)a/(float)1000000))*(FCY/PRESCALER))) 

#define T5_TIME         35530       //Max = 65535 
#define T5_TIME_S(a)    ((unsigned int)((float)(a)*FCY))     
#define T5_TIME_mS(a)   ((unsigned int)(((float)((float)a/(float)1000))*(float)(FCY/PRESCALER))) 
#define T5_TIME_uS(a)   ((unsigned int)((((float)a/(float)1000000))*(FCY/PRESCALER))) 

#define T23_TIME        4294967296  //Max = 4.294.967.296 
#define T23_TIME_S(a)   ((unsigned long int)((float)(a)*FCY))     
#define T23_TIME_mS(a)  ((unsigned long int)(((float)((float)a/(float)1000))*(float)(FCY/PRESCALER))) 
#define T23_TIME_uS(a)  ((unsigned long int)((((float)a/(float)1000000))*(FCY/PRESCALER))) 

#define T45_TIME        967296  //Max = 4.294.967.296
#define T45_TIME_S(a)   ((unsigned long int)((float)(a)*FCY))     
#define T45_TIME_mS(a)  ((unsigned long int)(((float)((float)a/(float)1000))*(float)(FCY/PRESCALER))) 
#define T45_TIME_uS(a)  ((unsigned long int)((((float)a/(float)1000000))*(FCY/PRESCALER))) 

#define ACK_RUN_TRIS    TRISGbits.TRISG14
#define ACK_RUN_LAT     LATGbits.LATG14
#define ACK_RUN_PORT    PORTGbits.RG14

#define BTN_ON_TRIS     TRISGbits.TRISG12   //P93_SWT2 
#define BTN_ON_LAT      LATGbits.LATG12     //P93_SWT2 
#define BTN_ON_PORT     PORTGbits.RG12      //P93_SWT2 

//#define PAUSE_MODE      1 //CAN PAUSE THE TIMER AND RESTART WHEN PRESS THE BUTTON
                            //IT WILL TRIGGER TIMMER INMEDIATELY, SO YOU HAVE TO IGNORE THE FIRST TIME INTERRUPT AFTER RESTART.
#define RESTART_MODE    1

#if defined (__PIC24FJ128GB610__)
    #define uno 1
#else
    #define two 2
#endif
/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
char count;

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
    
    #ifdef ACTIVE_TIMER1
    T1CONbits.TON   = 0;
    T1CONbits.TECS  = 0b00;     // SOSC
    T1CONbits.TCKPS = T_PS;     // 1:1
    T1CONbits.TCS   = 0;        // FOSC/2
    PR1             = T1_TIME_mS(500);
    IPC0bits.T1IP   = 2;
    IFS0bits.T1IF   = 0;
    IEC0bits.T1IE   = 1;
    
    T1CONbits.TON   = 1;
    #endif

    #ifdef ACTIVE_TIMER2
    T2CONbits.TON   = 0;
    T2CONbits.TECS  = 0b00;     // SOSC
    T2CONbits.TCKPS = T_PS;     // 1:1
    T2CONbits.T32   = 0;        // 16bits
    T2CONbits.TCS   = 0;        // FOSC/2
    PR2             = T2_TIME_mS(300);
    IPC1bits.T2IP   = 2;
    IFS0bits.T2IF   = 0;
    IEC0bits.T2IE   = 1;
    
    T2CONbits.TON   = 1;
    #endif
    #ifdef ACTIVE_TIMER3
    T3CONbits.TON   = 0;
    T3CONbits.TECS  = 0b00;     // SOSC
    T3CONbits.TCKPS = T_PS;     // 1:1
    T3CONbits.TCS   = 0;        // FOSC/2
    PR3             = T3_TIME_mS(1000);
    IPC2bits.T3IP   = 2;
    IFS0bits.T3IF   = 0;
    IEC0bits.T3IE   = 1;
    
    T3CONbits.TON   = 1;
    #endif
    #ifdef ACTIVE_TIMER4
    T4CONbits.TON   = 0;
    T4CONbits.TECS  = 0b00;     // SOSC
    T4CONbits.TCKPS = T_PS;     // 1:1
    T4CONbits.T32   = 0;        // 16bits
    T4CONbits.TCS   = 0;        // FOSC/2
    PR4             = T4_TIME_mS(150);
    IPC6bits.T4IP   = 2;
    IFS1bits.T4IF   = 0;
    IEC1bits.T4IE   = 1;
    
    T4CONbits.TON   = 1;
    #endif

    #ifdef ACTIVE_TIMER5
    T5CONbits.TON   = 0;
    T5CONbits.TECS  = 0b00;     // SOSC
    T5CONbits.TCKPS = T_PS;     // 1:1
    T5CONbits.TCS   = 0;        // FOSC/2
    PR5             = T5_TIME_mS(75);
    IPC7bits.T5IP   = 2;
    IFS1bits.T5IF   = 0;
    IEC1bits.T5IE   = 1;
    
    T5CONbits.TON   = 1;
    #endif
    #ifdef ACTIVE_TIMER23
    T2CONbits.TON   = 0;
    T2CONbits.TECS  = 0b00;     // SOSC
    T2CONbits.TCKPS = T_PS;     // 1:1
    T2CONbits.T32   = 1;        // 32bits
    T2CONbits.TCS   = 0;        // FOSC/2
    PR3             = (T23_TIME_mS(300)>>16);
    PR2             = T23_TIME_mS(300);
    IPC2bits.T3IP   = 2;
    IFS0bits.T3IF   = 0;
    IEC0bits.T3IE   = 1;
    
    T2CONbits.TON   = 1;
    #endif
    #ifdef ACTIVE_TIMER45
    T4CONbits.TON   = 0;
    T4CONbits.TECS  = 0b00;     // SOSC
    T4CONbits.TCKPS = T_PS;     // 1:1
    T4CONbits.T32   = 1;        // 32bits
    T4CONbits.TCS   = 0;        // FOSC/2
    PR5             = (T23_TIME_mS(500)>>16);
    PR4             = T23_TIME_mS(500);
    IPC7bits.T5IP   = 2;
    IFS1bits.T5IF   = 0;
    IEC1bits.T5IE   = 1;
    
    T4CONbits.TON   = 1;
    #endif
/******************************************************************************/   
/********************************  INITIALISING  ******************************/
/******************************************************************************/ 
    ACK_RUN_LAT     = 1;
    __delay_ms(1000);
    ACK_RUN_LAT     = 0;
    
    #ifdef _INTERRUPTS
    INTCON2bits.GIE     = 1;
    #endif
    
/******************************************************************************/   
/*********************************  MAIN LOOP  ********************************/     
/******************************************************************************/ 
    while(1){
//Right sequence to restart a time:
//  a) Turn off time follow by disable time interrupt in the INTERRUPT ROUTING
//  b) When restarting timer, clear the interrupt flag because otherwise automatically will generate an interrupt due to TMR = PR.
//      This will allow a gap of time some timer restart its value. 
// c) enable interrupts. 
        #ifdef PAUSE_MODE        
        if(BTN_ON_PORT){
            ACK_RUN_LAT   ^= 1;
            T3CONbits.TON   = 1;
            Nop();
            IFS0bits.T3IF   = 0;
            IEC0bits.T3IE   = 1;
            while(BTN_ON_PORT);
        }
        #endif
        #ifdef RESTART_MODE
        if(BTN_ON_PORT){
            if(T3CONbits.TON){
                T3CONbits.TON   = 0;
                TMR3=0;
                PR3 = T3_TIME_mS(1000);
                T3CONbits.TON   = 1;          
            }
            else{
                ACK_RUN_LAT   ^= 1;
                T3CONbits.TON   = 1;
                Nop();
                IFS0bits.T3IF   = 0;
                IEC0bits.T3IE   = 1;    
            }
            
            while(BTN_ON_PORT);            
        }
        #endif
    }
    return (0);
}
/******************************************************************************/       
/********************************  INTERRUPTS  ********************************/
/******************************************************************************/
#ifdef ACTIVE_TIMER1
void __attribute__((interrupt,no_auto_psv)) _T1Interrupt(void){
 
    ACK_RUN_LAT ^= 1;
    
    IFS0bits.T1IF = 0;
        
}
#endif
#ifdef ACTIVE_TIMER2
void __attribute__((interrupt,no_auto_psv)) _T2Interrupt(void){
 
    ACK_RUN_LAT ^= 1;
    
    IFS0bits.T2IF = 0;
        
}
#endif
#ifdef ACTIVE_TIMER3
void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void){
 
    ACK_RUN_LAT ^= 1;
    
    #ifdef PAUSE_MODE
    T3CONbits.TON   = 0;
    IEC0bits.T3IE   = 0;
    #endif
    #ifdef RESTART_MODE
    T3CONbits.TON   = 0;
    IEC0bits.T3IE   = 0;
    #endif
    IFS0bits.T3IF   = 0;
    
}
#endif
#ifdef ACTIVE_TIMER4
void __attribute__((interrupt,no_auto_psv)) _T4Interrupt(void){
 
    ACK_RUN_LAT ^= 1;
    
    IFS1bits.T4IF = 0;
        
}
#endif
#ifdef ACTIVE_TIMER5
void __attribute__((interrupt,no_auto_psv)) _T5Interrupt(void){
 
    ACK_RUN_LAT ^= 1;
    
    IFS1bits.T5IF = 0;
        
}
#endif
#ifdef ACTIVE_TIMER23
void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void){
 
    ACK_RUN_LAT ^= 1;
    
    IFS0bits.T3IF = 0;
        
}
#endif
#ifdef ACTIVE_TIMER45
void __attribute__((interrupt,no_auto_psv)) _T5Interrupt(void){
 
    ACK_RUN_LAT ^= 1;
    
    IFS1bits.T5IF = 0;
        
}
#endif
