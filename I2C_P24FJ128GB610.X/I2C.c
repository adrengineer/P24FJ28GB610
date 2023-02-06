/*
 * File:   I2C.c
 * Author: adrengineer
 *
 * Created on 15 June 2022, 19:54
 */

/******************************************************************************
 * Change log                                                                 
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 15/06/22     1.0         Created log. Added to LCD_P24FJ128GB610
 * 16/06/22                 Added to MIDI_P24FJ128GB610
 * 27/10/22     1.1         Added to a new version at work.
 * 
  **************************************************************************** */

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "I2C.h"

/*----------------------------------------------------------------------------*/
/* Defines                                                                    */
/*----------------------------------------------------------------------------*/


#define I2C_SCL_TRIS        TRISAbits.TRISA2
#define I2C_SCL_PULLUP      LATAbits.LATA2
#define I2C_SDA_TRIS        TRISAbits.TRISA3
#define I2C_SDA_PULLUP      LATAbits.LATA3

//#define BRG 78

/*----------------------------------------------------------------------------*/
/* Global Variables                                                           */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function prototype                                                         */
/*----------------------------------------------------------------------------*/

/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void I2C_Init(unsigned int BRG){
	I2C_SCL_PULLUP = 1;
	I2C_SDA_PULLUP = 1;
	ODCAbits.ODCA2 = 1;
    ODCAbits.ODCA3 = 1;
	I2C_SCL_TRIS = 0;//output
	I2C_SDA_TRIS = 0;//output
	//I2C_SCL_TRIS = 1;//disable output
	//I2C_SDA_TRIS = 1;//disable output
    	I2C2CONL = 0x1000;//Set all bits to known state.
    	I2C2CONLbits.I2CEN = 0;//Disable until everything set up. Pins will be I/0
	I2C2BRG = BRG;
    	I2C2CONLbits.DISSLW = 0;//Enable slew rate control for 400kHz operation.
    	//IFS1bits.MI2C1IF = 0;//Clear I2C master int flag.
    	I2C2CONLbits.I2CEN = 1;
}

/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void I2C_Start(void) {
	I2C2CONLbits.SEN = 1;
	while(I2C2CONLbits.SEN);
}

/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void i2c_restart(void) {
	I2C2CONLbits.RSEN = 1;
	while(I2C2CONLbits.RSEN);
}
/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void I2C_Stop(void) {
	I2C2CONLbits.PEN = 1;
	while(I2C2CONLbits.PEN);
}
/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void I2C_WriteByte(unsigned char byte) {
	I2C2TRN = byte;
	while(I2C2STATbits.TRSTAT);
}
/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
char i2c_read(char bLastRx) {
	I2C2CONLbits.RCEN = 1;
	while(I2C2CONLbits.RCEN);
	//ack sequence
	if (bLastRx) I2C2CONLbits.ACKDT = 1; else I2C2CONLbits.ACKDT = 0;
	I2C2CONLbits.ACKEN = 1; while (I2C2CONLbits.ACKEN);
	return I2C2RCV;
}

void I2C_SendByte(unsigned char i2cAddr, unsigned char reg, unsigned char data) {
	I2C_Start();
	I2C_WriteByte(i2cAddr);
	I2C_WriteByte(reg);
	I2C_WriteByte(data);
	I2C_Stop();
}
/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void I2C_SendBurst(unsigned char i2cAddr, unsigned char reg, unsigned char* pcdata, unsigned char ndata){
	I2C_Start();

	I2C_WriteByte(i2cAddr);
	I2C_WriteByte(reg);
	unsigned char i;
	for (i=0; i<ndata; i++) {I2C_WriteByte(pcdata[i]);}

	I2C_Stop();
}
/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
unsigned char I2C_ReadByte(unsigned char i2cAddr, unsigned char reg) {
	unsigned char ucRtn;
	I2C_Start();
	I2C_WriteByte(i2cAddr);// I2C slave address
	I2C_WriteByte(reg);// Send register address
	i2c_restart();
	I2C_WriteByte(i2cAddr | 0x01);// I2C slave address + read flag
	ucRtn = i2c_read(1);// receive data
	I2C_Stop();
	return ucRtn;
}
/* ************************************************************************** */
/* @Brief:                                                                    */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void I2C_ReadBurst(unsigned char i2cAddr, unsigned char reg, unsigned char* pcdata, unsigned char ndata){
	I2C_Start();
	I2C_WriteByte(i2cAddr);//address, write
	I2C_WriteByte(reg);
	i2c_restart();

	I2C_WriteByte(i2cAddr | 0x01);// I2C slave address + read flag
	unsigned char i;
	for (i=0; i<ndata; i++) {pcdata[i] = i2c_read(i == ndata-1);}
	I2C_Stop();
}