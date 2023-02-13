/*
 * File:   EPMP.c
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


/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "EPMP.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function                                                                   */
/*----------------------------------------------------------------------------*/
/* ************************************************************************** */
/* @Brief: This function initialises EPMP                                     */
/*          It configures the ports automatically                             */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void EPMP_Init(){
    //PMCON1
    PMCON1bits.PMPEN = 0;
    PMCON1bits.PSIDL = 0;
    PMCON1bits.ADRMUX = 0b00;
    PMCON1bits.MODE = 0b11;
    PMCON1bits.CSF = 0b00;
    PMCON1bits.ALP = 1;
    PMCON1bits.ALMODE = 0;
    PMCON1bits.BUSKEEP = 0;
    PMCON1bits.IRQM = 0b00;
    //PMCON2
    PMCON2bits.BUSY = 0;
    PMCON2bits.ERROR = 0;
    PMCON2bits.TIMEOUT = 0;
    PMCON2bits.RADDR = 0b00000000;
    //PMCON3
    PMCON3bits.PTWREN = 1;
    PMCON3bits.PTRDEN = 1;
    PMCON3bits.PTBE1EN = 0;
    PMCON3bits.PTBE0EN = 0;
    PMCON3bits.AWAITM = 0b11;
    PMCON3bits.AWAITE = 1;
    //PMCON4
    PMCON4bits.PTEN15 = 0;
    PMCON4bits.PTEN14 = 0;
    PMCON4bits.PTEN0  = 1;
    //PMCS1CF
    PMCS1CFbits.CSDIS = 0;
    PMCS1CFbits.CSP = 0;
    PMCS1CFbits.CSPTEN = 1;
    PMCS1CFbits.WRSP = 1;
    PMCS1CFbits.RDSP = 1;
    PMCS1CFbits.SM = 1;
    PMCS1CFbits.PTSZ = 0b00;
    //PMCS1MD
    PMCS1MDbits.DWAITM = 0b1111;
    //PMCON1
    PMCON1bits.PMPEN = 1;
           
}
/* ************************************************************************** */
/* @Brief: This function initialises port to use PMP with dream               */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void PMP_Init(){

    CS_TRIS     = 0;     
    RD_TRIS     = 0;       
    WR_TRIS     = 0;        
    A0_ANS      = 0;         
    A0_TRIS     = 0;           
    IRQ_TRIS    = 0;      

    DB0_ANS     = 0;   
    DB1_ANS     = 0;    
    DB2_ANS     = 0;      
    DB3_ANS     = 0;        
    DB4_ANS     = 0;     
    DB5_ANS     = 0;      
    DB6_ANS     = 0;    
    DB7_ANS     = 0;    

    DATA_TRIS &= MASK_WRITE_TRIS;
    DB0_TRIS    = 0;       
    DB1_TRIS    = 0;      
    DB2_TRIS    = 0;       
    DB3_TRIS    = 0;     
    DB4_TRIS    = 0;      
    DB5_TRIS    = 0;      
    DB6_TRIS    = 0;       
    DB7_TRIS    = 0; 
    
}
/* ****************************************************************************
 * @Brief: It reads a data byte from the Parallel Master Port.
 * @Param: 
 * @Return: Data read. 
 * ************************************************************************** */
unsigned char _rdpmpbyte(void){
    unsigned int pmp = 0;
    
    TRISB |=   0b0000001111000000;
    TRISC |=   0b0000110000110000;
    
    CS_LAT = 0;
    //__delay_us(1);
    RD_LAT = 0;
    //__delay_us(1);
    A0_LAT = 0;
    //__delay_us(1);
    
    pmp |= (PORTB & 0b0000001111000000);
    pmp >>= 6;
    pmp |= (PORTC & 0b0000000000110000);
    pmp |= ((PORTC & 0b0000110000000000)>>4);
    
    RD_LAT = 1;
    //__delay_us(1);
    CS_LAT = 1;
   // __delay_us(100);
    
    return (unsigned char) pmp;
    
}
/* ****************************************************************************
 * @Brief: It reads the status register.
 * @Param: 
 * @Return: Status register. 
 * ************************************************************************** */
unsigned char _rdpmpstat(void){
    unsigned int pmp = 0;
    
    TRISB |=   0b0000001111000000;
    TRISC |=   0b0000110000110000;
    
    CS_LAT = 0;
    //__delay_us(1);
    RD_LAT = 0;
    //__delay_us(1);
    A0_LAT = 1;
    //__delay_us(1);
    
    pmp |= (PORTB & 0b0000001111000000);
    pmp >>= 6;
    pmp |= (PORTC & 0b0000000000110000);
    pmp |= ((PORTC & 0b0000110000000000)>>4);
    
    RD_LAT = 1;
    //__delay_us(1);
    CS_LAT = 1;
   // __delay_us(100);
    
    return (unsigned char) pmp;
    
}
/* ****************************************************************************
 * @Brief: It send a byte to the Parallel Master Port.
 * @Param: Byte to write.
 * @Return: 
 * ************************************************************************** */
void _wrpmpbyte (unsigned char data){
    DATA_TRIS &= MASK_WRITE_TRIS;

    CS_LAT = 0;
    __delay_us(1);
    WR_LAT = 0;
    __delay_us(1);
    A0_LAT = 0;
    __delay_us(1);

    DATA_LAT = ((DATA_PORT & MASK_WRITE) | data);

    WR_LAT = 1;
    __delay_us(1);
    CS_LAT = 1;
    __delay_us(1);

}
/* ****************************************************************************
 * @Brief: It send a byte to the Parallel Master Port check RF status.
 * @Param: Byte to write.
 * @Return: 
 * ************************************************************************** */
char _wrpmpstat (unsigned char data){
    unsigned int value = 0;
    /*unsigned int i=65500;
    while((_rdpmpstat()&0b01000000)&&(--i)){};
    if(i==0)
        return 0;
    else{*/


    CS_LAT = 0;
    __delay_us(10);
    WR_LAT = 0;
    __delay_us(10);
    A0_LAT = 0;
    __delay_us(10);

    //DATA_LAT = data;
    //DATA_LAT = ((DATA_PORT & MASK_WRITE) | data);
    
    DB0_LAT    = 0;       
    DB1_LAT    = 0;      
    DB2_LAT    = 0;       
    DB3_LAT    = 0;     
    DB4_LAT    = 1;      
    DB5_LAT    = 1;      
    DB6_LAT    = 1;       
    DB7_LAT    = 1; 
    
    WR_LAT = 1;
    __delay_us(10);
    CS_LAT = 1;
    __delay_us(10);
    return 1;
//}
}