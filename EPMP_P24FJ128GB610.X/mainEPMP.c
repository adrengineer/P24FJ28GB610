/*
 * File:   mainEPMP.c
 * Author: adrengineer
 *
 * Created on 13 October 2022, 15:02
 */


/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "config_bits.h"
#ifdef _PMP
    #include "EPMP.h"
#endif


/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#define ACK_RUN_TRIS    TRISGbits.TRISG14
#define ACK_RUN_LAT     LATGbits.LATG14
#define ACK_RUN_PORT    PORTGbits.RG14

#define EXTERNAL_RESOURCE_SIZE  0x200L    // 2x128 Kbytes
#define CS_START_ADDRESS        0x200000L   // the address programmed for the EPMP chip select in PMCS1BS register

//#define TEST_PMP_PERIPHERAL     1
#define TEST_DREAM_PMP          1

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
// define an array in EPMP EDS space to access the external resource
__eds__ int pmp_data[EXTERNAL_RESOURCE_SIZE]
__attribute__((eds, address(CS_START_ADDRESS), noload)); 
// temporary pointer
__eds__ int* pointer;

int main(void) {
    unsigned char counting = 0; 

/******************************************************************************/   
/*****************************  REMAPPABLE PINS   *****************************/
/******************************************************************************/ 

 
/******************************************************************************/   
/*****************************  PORT CONFIGURATION  ***************************/                             
/******************************************************************************/
    ACK_RUN_TRIS    = 0;
    
    ANSELB = 0;
    ANSELD = 0;
    ANSELE = 0;
    
    CS_TRIS = 0;
    RD_TRIS = 0;
    WR_TRIS = 0;
    A0_TRIS = 0;
    IRQ_TRIS = 1;  
/******************************************************************************/   
/********************************  INITIALISING  ******************************/
/******************************************************************************/ 
    CS_LAT = 1;
    RD_LAT = 1;
    WR_LAT = 1;
    
    ACK_RUN_LAT     = 1;
    #ifdef _PMP
    //EPMP_Init();
    //PMP_Init();
    #endif
/******************************************************************************/   
/*********************************  MAIN LOOP  ********************************/     
/******************************************************************************/     

    #ifdef TEST_PMP_PERIPHERAL
    // This code can be used if the EPMP access time is more than 1 Tcy.
    pointer = pmp_data; // assign pointer to the start address of the EPMP 
    // chip select region
    while(PMCON2bits.BUSY); // wait for the previous access is done
    *pointer++ = 1; // write '1' to external word address 0x000000
    while(PMCON2bits.BUSY); // wait for the previous access is done
    *pointer++ = 2; 
    #endif
    
    while(1){
    #ifdef TEST_PMP_PERIPHERAL
        while(PMCON2bits.BUSY); // wait for the previous access is done
        *pointer++ = counting; // write '1' to external word address 0x000000
        __delay_ms(30);
        counting++;
        while(PMCON2bits.BUSY); // wait for the previous access is done
        *pointer-- = counting; // write '1' to external word address 0x000000
        __delay_ms(30);
        counting++;
    #endif
    #ifdef TEST_DREAM_PMP 
        _wrpmpstat (0Xb0);
        __delay_ms(3);
        _wrpmpstat (0X06);
        __delay_ms(3);
        _wrpmpstat (0X07); 
        __delay_ms(3);

        __delay_ms(300);

        #ifdef _DEBUGGING
        ACK_RUN_LAT ^= 1;
        __delay_ms(1000);

        #endif
    #endif

    }
    return (0);
}
/******************************************************************************/       
/********************************  INTERRUPTS  ********************************/
/******************************************************************************/