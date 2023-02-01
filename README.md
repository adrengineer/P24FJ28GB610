# P24FJ28GB610
Individual blocks of the microcontroller PIC 24FJ128GB610 are developed in this repository.

_HARDWARE_

To establish communication with the microcontroller a minimum set up with decoupling capacitor is required. 
External oscillators are optional, and not necessary for running the microcontroller.


![Alt text](Pictures/GeneralPIC.jpg)

### INI_P24FJ128GB610.X
This folder contains the initialization project. This project will initialize the microcontroller and toggle a pin to acknowledge *running status*.

## ADC_P24FJ128GB610.X
This project contains necessary files to initialize ADC module. It will toggle a port at a rate determine by the ADC read.

## TMR_P24FJ128GB610
This project allows you to use any timer of the microcontroller to toggle a port at frequency that you wish.