/*
 * File:   UART.c
 * Author: Adrengineer
 *
 * Created on 26 January 2022, 09:30
 */
/******************************************************************************
 * Change log                                                                 
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 25/01/21     1.0         Created log.
 * 04/11/22     1.1         Added to UART_P24FJ128GB610 project
 * 04/11/22     1.7         MIDI_P24FJ128GB610 project
 * 
 ***************************************************************************** */

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
/* System funct/params, like osc/peripheral config */
#include "C:\Users\adren\Documents\Project-[G01]_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"  
#include "UART.h"        


/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/
#define _U1INTERRUPTS 0

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/
//static uint8_t ReceivedDataBuffer[MIDI_BUFFER];

/*----------------------------------------------------------------------------*/
/* Function                                                                   */
/*----------------------------------------------------------------------------*/


/** ****************************************************************************
 * @Brief: The function initialises the UART. The Baud is set and the Parity 
 *      setting is also set.
 * @Param:
 * @Return:
 * ************************************************************************* **/
void UART_Init()
{
    unsigned int configMODE;
    unsigned int configMODEH;
    unsigned int configSTA;
    unsigned int configSTAH;
    /*
     * parity options
     * 0 is none
     * 1 is Odd
     * 2 is Even
     * 3 is mark
     * 4 is space
     */
    
    #if defined (__PIC24FJ128GB610__)
    #else
    __builtin_write_RPCON(0x0000);
    RPINR18bits.U1RXR= 77;                  //RX remapped to RP77
    RPOR14bits.RP61R = 1;                   //RX&TX are swap in Altium parent file.
    __builtin_write_RPCON(0x0800);
    #endif
    
    //UART_Close();                          //turn off usart if was previously on
    configMODE      = 0;
    configMODEH     = 0;
    configSTA       = 0;
    configSTAH      = 0;
            
    
    #if defined (__PIC24FJ128GB610__)
    //-----configure USART -----
    //configMODE |= UART_UARTEN_EN;           //(bit 15)  UART EN
    configMODE |= UART_UEN;                 //(bit 9-8) UxTX, UxRX and UxRTS pins are enabled and used;
    configMODE |= UART_ABAUD_LOW;           //(bit 5)   No auto-baud
    configMODE |= UART_BRGH_LOW;            //(bit 3)   Standard speed mode /16
    configMODE |= UART_PDSEL;               //(bit 2-1) 8-bit data, no parity
    configMODE |= UART_STSEL_1STOP;         //(bit 0)   1 stop bit

    configSTA |= UART_UTXISEL_8BIT_EMPTY;   //(bit 15,13) Interrupt when 8bits are empty
    configSTA |= UART_URXISEL_8BIT_MORE;    //(bit 7-6) Interrupt when 1 word or more
    configSTA |= UART_URXISEL_8BIT_RECV;    //(bit 7-6) Interrupt when 8 bits received

    U5MODE  = configMODE;
    U5STA   = configSTA;

    U5BRG   = BRGVAL;
    #else
    configMODE |= UART_MOD_ASY_8BIT;        //(bit 3-0) Asynchronous 8-bits
    configMODE |= UART_ABAUD_LOW;           //(bit 6) No auto-baud
    configMODE |= UART_BRGH_LOW;            //(bit 7) Standard speed mode /16
    configMODE |= UART_UARTEN_EN;           //(bit 15)UART EN
    configMODE |= UART_UTXEN_EN;            //(bit 5) Transmit enable
    configMODE |= UART_URXEN_EN;            //(bit 4) Receive enable
    U1MODE = configMODE;
    configMODEH |= UART_STSEL_1STOP;        //(bit 5-4) 1 stop bit
    U1MODEH = configMODEH;
    
    configSTAH |= UART_UTXISEL_8BIT_EMPTY;  //(bit 14-12) Interrupt when 8bits are empty
    configSTAH |= UART_URXISEL_8BIT_MORE;   //(bit 10-8) Interrupt when 1 word or more
    U1STAH = configSTAH;
    
    U1BRG = 53;//BRGVAL; // Baud Rate setting for 9600       
    
    #endif
    
    #if _U1INTERRUPTS
        #if defined (__PIC24FJ128GB610__)

        IFS0bits.U1TXIF = 0;
        IFS0bits.U1RXIF = 0;
        IEC0bits.U1RXIE = 1;                    // Enable UART RX interrupt
        IEC0bits.U1TXIE = 1;                    // Enable UART TX interrupt

        #else
        configSTA |= UART_TX_INT_ON;

        U1STA = configSTA;

        IFS0bits.U1TXIF = 0;
        IFS0bits.U1RXIF = 0;
        IEC0bits.U1RXIE = 1;                    // Enable UART RX interrupt
        IEC0bits.U1TXIE = 1;                    // Enable UART TX interrupt
        #endif

    #endif 
    
    /* Wait at least 105 microseconds (1/9600) before sending first char */
    DELAY_105uS    
   
}
/** ****************************************************************************
 * @Brief: The function sets up the UART transmitter and receiver.
 * @Param:
 * @Return:
 * ************************************************************************* **/
void UART_Open(){
    #if defined (__PIC24FJ128GB610__)
    U5MODEbits.UARTEN   = 1;
    U5STAbits.URXEN     = 1; 
    U5STAbits.UTXEN     = 1; 
    #else
    U1MODEbits.UARTEN   = 1;
    U1MODEbits.URXEN    = 1; 
    U1MODEbits.UTXEN    = 1; 
    #endif
    
}


/** ****************************************************************************
 * @Brief: The function disables the uart.
 * @Param:
 * @Return:
 * ************************************************************************* **/
void UART_Close(void){
    #if defined (__PIC24FJ128GB610__)
    U5MODEbits.UARTEN   = 0;
    U5STAbits.URXEN     = 0; 
    U5STAbits.UTXEN     = 0; 
    #else
    U1MODEbits.UARTEN   = 0;
    U1MODEbits.URXEN    = 0; 
    U1MODEbits.UTXEN    = 0; 
    #endif
}


/** ****************************************************************************
 * @Brief: Receiving data (mode asynchronous)
 * @Param:
 * @Return: data received
 * ************************************************************************* **/
unsigned char UART_ReadByte(){
    #if defined (__PIC24FJ128GB610__)
    if(U5STAbits.OERR){           
        U5STAbits.OERR = 0;
    }
    if(!U5STAbits.URXDA){ 
        return U5RXREG;
    }
    else
        return 0;
    #else
    if(U1STAbits.OERR){           
        U1STAbits.OERR = 0;
    }
    if(!U1STAHbits.URXBE){ 
        return U1RXREG;
    }
    else
        return 0;
    #endif

}


/** ****************************************************************************
 * @Brief: Transmitting byte data (mode asynchronous)
 * @Param: Character (8bits) to be send
 * @Return: 
 * ************************************************************************* **/
void UART_WriteByte(unsigned char caracter){
    #if defined (__PIC24FJ128GB610__)
    #if _U1INTERRUPTS 
    #else
        while(U5STAbits.TRMT==0);   
        U5TXREG = caracter;
    #endif
    #else
    #if _U1INTERRUPTS 
    if (I > MIDI_BUFFER);
        //return 0;
    else{
        if(U1STAbits.TRMT == 1){
            if(A >= I){
                U1TXREG = caracter;
            }
            else if(A < I){
                RECEIVEDDATABUFFER[I] = caracter;
                I++;
            }
        }
        else{ //U1STAbits.TRMT == 0
            RECEIVEDDATABUFFER[I] = caracter;
            I++;
   
            if(CTS == 1){
                U1TXREG = RECEIVEDDATABUFFER[A];
                A++;
                CTS = 0;  
            }

        }

        //return 1;
    }

    #else
        while(U1STAbits.TRMT==0);   
        U1TXREG = caracter;
    #endif
    #endif

       
}
/** ****************************************************************************
 * @Brief: Transmitting string data (mode asynchronous)
 * @Param: String to be send
 * @Return: 
 * ************************************************************************* **/ 
void UART_WriteString(char* cadena){
    while(*cadena != 0x00){
        UART_WriteByte(*cadena);
        cadena++;
    }
}
//void UART_String(const unsigned char *data){
//    while(*data != 0x00){
//        UART_WriteByte(*data);
//        *data++;
//    }
//    
//}
/** ****************************************************************************
 * @Brief:  WITH THIS FUNCTION AND STDIO LIBRARY IS POSIBLE USE PRINTF
 * @Param p: parameter to write
 * @Returm
 * ************************************************************************* **/
#ifdef _LCD_MODE
void putch(char p){
    #if defined (__PIC24FJ128GB610__)
    while(U5STAbits.TRMT==0);   
        U5TXREG = p;
    #else
   while(U1STAbits.TRMT==0);   
        U1TXREG = p;
    #endif   

}
#endif