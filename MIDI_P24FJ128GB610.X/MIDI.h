/* 
 * File:  MIDI.h
 * Author: Adrengineer
 * Comments:
 * Revision history: 
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

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MIDI_H
#define	MIDI_H

/* -------------------------------------------------------------------------- */
/* Files to Include                                                           */
/* -------------------------------------------------------------------------- */
#include "C:\Users\adren\Documents\P_G01_P24FJ128GB610\INI_P24FJ128GB610.X\system.h"


/* -------------------------------------------------------------------------- */
/* Defines                                                                    */
/* -------------------------------------------------------------------------- */

typedef union
{
    uint32_t Val;
    uint8_t v[4];
    union
    {
        struct
        {
            uint8_t CIN :4;
            uint8_t CN  :4;
            uint8_t CH  :4;
            uint8_t CC  :4;
            uint8_t MIDI_1;
            uint8_t MIDI_2;
        };
        struct
        {
            uint8_t CodeIndexNumber :4;
            uint8_t CableNumber     :4;
            uint8_t Channel         :4;
            uint8_t ControlChange   :4;
            uint8_t DATA_1;
            uint8_t DATA_2;
        };
        struct
        {
            uint8_t codeIndexNumber :4;
            uint8_t cableNumber     :4;
            uint8_t data_0;
            uint8_t data_1;
            uint8_t data_2;
        };
    };
} MIDI_EVENT_PACKET, *P_MIDI_EVENT_PACKET;



#define MIDI_BUFFER 256

/* Code Index Number (CIN) values */
/*   Table 4-1 of midi10.pdf      */
#define MIDI_CIN_MISC_FUNCTION_RESERVED         0x0
#define MIDI_CIN_CABLE_EVENTS_RESERVED          0x1
#define MIDI_CIN_2_uint8_t_MESSAGE              0x2
#define MIDI_CIN_MTC                            0x2
#define MIDI_CIN_SONG_SELECT                    0x2
#define MIDI_CIN_3_uint8_t_MESSAGE              0x3
#define MIDI_CIN_SSP                            0x3
#define MIDI_CIN_SYSEX_START                    0x4
#define MIDI_CIN_SYSEX_CONTINUE                 0x4
#define MIDI_CIN_1_uint8_t_MESSAGE              0x5
#define MIDI_CIN_SYSEX_ENDS_1                   0x5
#define MIDI_CIN_SYSEX_ENDS_2                   0x6
#define MIDI_CIN_SYSEX_ENDS_3                   0x7
#define MIDI_CIN_NOTE_OFF                       0x8
#define MIDI_CIN_NOTE_ON                        0x9
#define MIDI_CIN_POLY_KEY_PRESS                 0xA
#define MIDI_CIN_CONTROL_CHANGE                 0xB
#define MIDI_CIN_PROGRAM_CHANGE                 0xC
#define MIDI_CIN_CHANNEL_PREASURE               0xD
#define MIDI_CIN_PITCH_BEND_CHANGE              0xE
#define MIDI_CIN_SINGLE_uint8_t                 0xF

/* MIDI message for DREAM */
/* Table 1 of "5716PIA-FW high range piano sound module" */

#define MIDI_CTRL_99_NRPN_HIGH                  0x63
#define MIDI_CTRL_98_NRPN_LOW                   0x62
#define MIDI_CTRL_06_MSB_DATA                   0x06
#define MIDI_CTRL_38_LSB_DATA                   0x26

#define MIDI_SYSEX_START                        0xF0
#define MIDI_MANUF_ID                           0x002000
#define MIDI_COMMAND_ID                         0x3D
#define MIDI_SYSEX_END                          0xF7

/* MIDI control change */
/* Table 1 of "5716PIA-FW high range piano sound module" */

#define MIDI_CC_NRPN                            0xB
#define MIDI_CC_NOTE_ON                         0x9
#define MIDI_CC_NOTE_OFF                        0x8

/* MIDI channel */
/* DREAM: 2 ports of 16 channels. F5 nn is use to change ports*/
#define MIDI_CHANNEL0                           0x0
#define MIDI_CHANNEL1                           0x1
#define MIDI_CHANNEL2                           0x2
#define MIDI_CHANNEL3                           0x3
#define MIDI_CHANNEL4                           0x4

/* Specific command for the DSP algorithm in use*/
#define DREAM_NRPN_ON_OFF                               0x0100
#define DREAM_NRPN_LEVEL1                               0x010A
#define DREAM_NRPN_BIQ_L_HF_ON_OFF                      0x0100
#define DREAM_NRPN_BIQ_L_HF_GAIN                        0x0102
#define DREAM_NRPN_BIQ_L_MF_ON_OFF                      0x0200
#define DREAM_NRPN_BIQ_L_MF_GAIN                        0x0202
#define DREAM_NRPN_BIQ_L_LF_ON_OFF                      0x0300
#define DREAM_NRPN_BIQ_L_LF_GAIN                        0x0302
#define DREAM_NRPN_BIQ_R_HF_ON_OFF                      0x0400
#define DREAM_NRPN_BIQ_R_HF_GAIN                        0x0402
#define DREAM_NRPN_BIQ_R_MF_ON_OFF                      0x0500
#define DREAM_NRPN_BIQ_R_MF_GAIN                        0x0502
#define DREAM_NRPN_BIQ_R_LF_ON_OFF                      0x0600
#define DREAM_NRPN_BIQ_R_LF_GAIN                        0x0602
#define DREAM_NRPN_MIX_L0_GAIN                          0x071F
#define DREAM_NRPN_MIX_L1_GAIN                          0x0720
#define DREAM_NRPN_MIX_L2_GAIN                          0x0721
#define DREAM_NRPN_MIX_R0_GAIN                          0x081F
#define DREAM_NRPN_MIX_R1_GAIN                          0x0820
#define DREAM_NRPN_MIX_R2_GAIN                          0x0821
#define DREAM_NRPN_MIX_L_GAIN                           0x0300
#define DREAM_NRPN_MIX_R_GAIN                           0x0400
#define DREAM_NRPN_DLY_FBCK                             0x0105
#define DREAM_NRPN_DLY_TIME                             0x0104
#define DREAM_NRPN_DLY_L_HF_ON_OFF                      0x0100
#define DREAM_NRPN_DLY_L_MF_ON_OFF                      0x0200
#define DREAM_NRPN_DLY_L_LF_ON_OFF                      0x0300
#define DREAM_NRPN_DLY_R_HF_ON_OFF                      0x0400
#define DREAM_NRPN_DLY_R_MF_ON_OFF                      0x0500
#define DREAM_NRPN_DLY_R_LF_ON_OFF                      0x0600
#define DREAM_NRPN_BIQ_L_LF_FRQ                         0x0341
#define DREAM_NRPN_BIQ_L_MFL_FRQ                        0x0241
#define DREAM_NRPN_BIQ_L_MFR_FRQ                        0x0242
#define DREAM_NRPN_BIQ_L_HF_FRQ                         0x0141
#define DREAM_NRPN_BIQ_R_LF_FRQ                         0x0641
#define DREAM_NRPN_BIQ_R_MFL_FRQ                        0x0541
#define DREAM_NRPN_BIQ_R_MFR_FRQ                        0x0542
#define DREAM_NRPN_BIQ_R_HF_FRQ                         0x0441

/* -------------------------------------------------------------------------- */
/* Global Variables                                                           */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Function prototypes                                                        */
/* -------------------------------------------------------------------------- */

void MIDI_NRPNcommand(unsigned char channel, unsigned int nrpn);
void MIDI_Message_28bits(unsigned char channel, unsigned int nrpn, unsigned long int value);
void MIDI_Value_14bits(unsigned char channel, unsigned int value);
void MIDI_Value_7bits(unsigned char channel, unsigned int value);
unsigned char MIDI_SendPackage (unsigned char* package);

/* -------------------------------------------------------------------------- */
/* Printf messages                                                            */
/* -------------------------------------------------------------------------- */

#endif	/* MIDI_H */

