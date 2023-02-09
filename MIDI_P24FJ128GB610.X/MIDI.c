/*
 * File:   MIDI.c
 * Author: adrengineer
 *
 * Created on 23 February 2022, 12:56
 */
/******************************************************************************
 * Change log                                                                 
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 23/02/22     1.0         Created log. Midi controller project
 * 04/11/22     1.1         MIDI_P24FJ128GB610 project
 * 
 ***************************************************************************** */
/* -------------------------------------------------------------------------- */
/* Files to Include                                                           */
/* -------------------------------------------------------------------------- */
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\UART_P24FJ128GB610.X\uart.h"
#include "midi.h"


/* -------------------------------------------------------------------------- */
/* Global Variables                                                           */
/* -------------------------------------------------------------------------- */

/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata DEVICE_AUDIO_MIDI_RX_DATA_BUFFER=DEVCE_AUDIO_MIDI_RX_DATA_BUFFER_ADDRESS
            static uint8_t ReceivedDataBuffer[64];
        #pragma udata DEVICE_AUDIO_MIDI_EVENT_DATA_BUFFER=DEVCE_AUDIO_MIDI_EVENT_DATA_BUFFER_ADDRESS
            static USB_AUDIO_MIDI_EVENT_PACKET midiData;
        #pragma udata
    #elif defined(__XC8)
        static uint8_t ReceivedDataBuffer[64] DEVCE_AUDIO_MIDI_RX_DATA_BUFFER_ADDRESS;
        static USB_AUDIO_MIDI_EVENT_PACKET midiData DEVCE_AUDIO_MIDI_EVENT_DATA_BUFFER_ADDRESS;
    #endif
#else
    //static uint8_t ReceivedDataBuffer[64];
    static MIDI_EVENT_PACKET midiData;
 
    
#endif
    

/* -------------------------------------------------------------------------- */
/* Function                                                                   */
/* -------------------------------------------------------------------------- */

/* ************************************************************************** */
/* @Brief:  Send a NRPN MIDI command                                                                  */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void MIDI_NRPNcommand(unsigned char channel,unsigned int nrpn)
{
    /* Upper byte*/
    midiData.Val = 0;   //must set all unused values to 0 so go ahead
    #if _USE_USB_MIDI
    midiData.CableNumber = 0;
    midiData.CodeIndexNumber = MIDI_CIN_CONTROL_CHANGE;
    #endif
  
    midiData.Channel = channel; 
    midiData.ControlChange = MIDI_CC_NRPN;    
    midiData.DATA_1 = MIDI_CTRL_99_NRPN_HIGH;
    midiData.DATA_2 = nrpn>>8;                     
    
    MIDI_SendPackage (midiData.v);
    
    /* Lower byte */
    midiData.Val = 0;   
    #if _USE_USB_MIDI
    midiData.CableNumber = 0;
    midiData.CodeIndexNumber = MIDI_CIN_CONTROL_CHANGE;
    #endif

    midiData.Channel = channel; 
    midiData.ControlChange = MIDI_CC_NRPN;                     
    midiData.DATA_1 = MIDI_CTRL_98_NRPN_LOW;
    midiData.DATA_2 = nrpn;                     
    
    MIDI_SendPackage (midiData.v);
}

/* ************************************************************************** */
/* @Brief: Transmit a 7 bits length MIDI command.                             */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void MIDI_Value_7bits(unsigned char channel, unsigned int value)
{
    midiData.Val = 0; 
    #if _USE_USB_MIDI
    midiData.CableNumber = 0;
    midiData.CodeIndexNumber = MIDI_CIN_CONTROL_CHANGE;
    #endif
    
    midiData.Channel = channel; 
    midiData.ControlChange = MIDI_CC_NRPN;  
    midiData.DATA_1 = MIDI_CTRL_06_MSB_DATA;
    midiData.DATA_2 = (value & 0x07F);                     
    
    MIDI_SendPackage (midiData.v);
}
/* ************************************************************************** */
/* @Brief: Transmit a 14bits length MIDI command.                             */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void MIDI_Value_14bits(unsigned char channel, unsigned int value)
{
    
    /* LSB Least Significant Byte */
    midiData.Val = 0;
    #if _USE_USB_MIDI
    midiData.CableNumber = 0;
    midiData.CodeIndexNumber = MIDI_CIN_CONTROL_CHANGE;
    #endif

    midiData.Channel = channel; 
    midiData.ControlChange = MIDI_CC_NRPN;   
    midiData.DATA_1 = MIDI_CTRL_38_LSB_DATA; 
    midiData.DATA_2 = (value & 0x07F);                     
    
    MIDI_SendPackage (midiData.v);
    
     /* MSB Most Significant Byte */
    
    midiData.Val = 0;   //must set all unused values to 0 so go ahead
    #if _USE_USB_MIDI
    midiData.CableNumber = 0;
    midiData.CodeIndexNumber = MIDI_CIN_CONTROL_CHANGE;
    #endif
     
    midiData.Channel = channel; 
    midiData.ControlChange = MIDI_CC_NRPN;    
    midiData.DATA_1 =  MIDI_CTRL_06_MSB_DATA;
    midiData.DATA_2 = (((value<<1)>>8) & 0x07F);                     
    
    MIDI_SendPackage (midiData.v);
}

/* ************************************************************************** */
/* @Brief: Send the MIDI command through the selected protocol in system.h    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
unsigned char MIDI_SendPackage (unsigned char* data)
{
    unsigned char rtn;
    rtn = 0;
    
    #if _USE_USB_MIDI
        if(_wrpmpstat(midiData.v[0]))
            rtn |= 0b00000001;
        #if _USE_SERIAL_MIDI
            UART_WriteByte(midiData.v[0]);
            __delay_ms(1);
        #endif
    #endif
    
            
    #if _USE_SERIAL_MIDI
        UART_WriteByte(midiData.v[1]);
        __delay_ms(1);
    #endif
    #if _USE_MPU_MIDI 
        if(_wrpmpstat(midiData.v[1]))
        rtn |= 0b00000100;
    #endif
    
            
    #if _USE_SERIAL_MIDI
        UART_WriteByte(midiData.v[2]);
        __delay_ms(1);
    #endif
    #if _USE_MPU_MIDI 
        if(_wrpmpstat(midiData.v[2]))
        rtn |= 0b00000100;
    #endif
    
            
    #if _USE_SERIAL_MIDI
        UART_WriteByte(midiData.v[3]);
        __delay_ms(1);
    #endif
    #if _USE_MPU_MIDI 
        if(_wrpmpstat(midiData.v[3]))
        rtn |= 0b00000100;
    #endif

    return rtn;
}

/* ************************************************************************** */
/* @Brief: Transmit a 28bits length MIDI command.                             */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void MIDI_Message_28bits(unsigned char channel, unsigned int nrpn, unsigned long int value)
{  
    midiData.Val = 0;   
    #if _USE_USB_MIDI
    midiData.cableNumber = 0;
    midiData.codeIndexNumber = MIDI_CIN_SYSEX_START;
    #endif
    midiData.data_0 = 0xF0; 
    midiData.data_1 = 0x00;
    midiData.data_2 = 0x20;      
    MIDI_SendPackage (midiData.v);
    
    midiData.Val = 0;
    #if _USE_USB_MIDI
    midiData.cableNumber = 0;
    midiData.codeIndexNumber = MIDI_CIN_SYSEX_START;   
    #endif
    midiData.data_0 = 0x00;     
    midiData.data_1 = 0x3D;    
    midiData.data_2 = channel;                    
    MIDI_SendPackage (midiData.v);
    
    midiData.Val = 0;
    #if _USE_USB_MIDI
    midiData.cableNumber = 0;
    midiData.codeIndexNumber = MIDI_CIN_SYSEX_START;    
    #endif
    midiData.data_0 = nrpn >> 8;     
    midiData.data_1 = nrpn;    
    midiData.data_2 = 0x04;                     
    MIDI_SendPackage (midiData.v);
    
    midiData.Val = 0;   
    #if _USE_USB_MIDI
    midiData.cableNumber = 0;
    midiData.codeIndexNumber = MIDI_CIN_SYSEX_START;
    #endif
    midiData.data_0 = ((value>>21) & 0x07F);    
    midiData.data_1 = ((value>>14) & 0x07F);   
    midiData.data_2 = ((value>>7) & 0x07F);                        
    MIDI_SendPackage (midiData.v);
    
    midiData.Val = 0;   
    #if _USE_USB_MIDI
    midiData.cableNumber = 0;
    midiData.codeIndexNumber = MIDI_CIN_SYSEX_ENDS_2;
    #endif
    midiData.data_0 = ((value) & 0x07F);    
    midiData.data_1 = 0xf7;   
    midiData.data_2 = 0x9F;                        
    MIDI_SendPackage (midiData.v);
 
}