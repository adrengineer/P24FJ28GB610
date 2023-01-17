/*
 * File:   main.c
 * Author: adrengineer
 *
 * Created on 23 May 2022, 19:26
 */


#include "system.h"
#include "config_bits.h"
#include <libpic30.h>

/****************************************************************************/
/* Useful Macros */
#define BITS2WORD(sfrBitfield) ( *((unsigned int*) &sfrBitfield) )
// Convert a bitfield to a word (unsigned int).
#define BITS2BYTEL(sfrBitfield) ( ((unsigned char*) &sfrBitfield)[0] )
// Return the low byte (as a unsigned char) of a bitfield.
#define BITS2BYTEH(sfrBitfield) ( ((unsigned char*) &sfrBitfield)[1] )
// Return the high byte (as a unsigned char) of a bitfield.

/****************************************************************************/
/* User Configurable Definitions */

// If the following line is uncommented the uC will use the internal oscillator,
// comment the line out to use the external oscillator
//#define USE_FRC_CLOCK

// Processor clock frequency selection
#define CLOCK_FREQ 32000000ULL // Use 32MHz clock ? default for demo board
//#define CLOCK_FREQ 16000000ULL // Use 16MHz clock
//#define CLOCK_FREQ 8000000ULL // Use 8MHz clock
//#define CLOCK_FREQ 4000000ULL // Use 4MHz clock

/*
*
*/
int main(void) {

unsigned int pllCounter;
OSCCONBITS OSCCONbitsCopy;

// Copy the current Clock Setup
OSCCONbitsCopy = OSCCONbits;
// Enable the PLL ? Note: Fuse bits don?t do this
CLKDIVbits.PLLEN = 1;
// Wait for the PLL to stabalise
for (pllCounter = 0; pllCounter < 600; pllCounter++);

// Check to see what clock setup is defined ? either internal or external
#if _USE_FRC_CLOCK
// Setup the uC to use the internal FRCPLL mode
OSCCONbitsCopy.NOSC = 0b001;
OSCCONbitsCopy.OSWEN = 1;
#elif _USE_PRI_CLOCK
// Setup the uC to use the external crystal with the PLL
OSCCONbitsCopy.NOSC = 0b010;
OSCCONbitsCopy.OSWEN = 1;
#endif

// Switch over to the new clock setup
__builtin_write_OSCCONH( BITS2BYTEH( OSCCONbitsCopy ) );
__builtin_write_OSCCONL( BITS2BYTEL( OSCCONbitsCopy ) );
// Wait for this transfer to take place
while (OSCCONbits.COSC != OSCCONbits.NOSC);
// Wait for Clock switch to occur
    while (OSCCONbits.OSWEN!= 0);
    // Wait for PLL to lock ONLY if it is use in config bits
    #ifndef __MPLAB_SIM
    while (OSCCONbits.LOCK!= 1);
    #endif
// Setup the DIV bits for the FRC, this values means the config word needs to be: PLLDIV_DIV2
//LKDIVbits.RCDIV0 = 0;
// Note ? don?t want to do this check if we are running in the MPLAB X simulator as it won?t work

//CLKDIVbits.CPDIV = 0b01;

// At this point the PIC24FJ64GB004 clock setup will be complete with the PLL
// enabled and ready for operation with USB2.0
    
    TRISGbits.TRISG15 = 0;
    
    while(1){
        LATGbits.LATG15 ^= 1;
        __delay_ms(500);
    }
    return 0;
}
