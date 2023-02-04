/*
 * File:   LCD.c  - P24FJ128GB610 REPOSITORY
 * Author: adrengineer
 *
 * Created on 14 June 2022, 19:50
 */
/******************************************************************************/
/* Change log                                                                 *
 *
 *
 *
 * Date         Revision    Comments
 * MM/DD/YY
 * --------     ---------   ----------------------------------------------------
 * 5/10/22      1.0         Initial project. P24FJ128GB610.
 * 26/10/22     1.2         Integrated with I2C LCD. 
 ******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Files to Include                                                           */
/*----------------------------------------------------------------------------*/
#include "LCD.h"


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
/* @Brief: This function initialises ports and LCD in mode 4/8 bits.          */
/*          It configures the ports automatically                             */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void LCD_Init(unsigned int speed){
    #ifdef _PMP
    #elif _LCD_I2C
        SDA_TRIS = 0;
        SCL_TRIS = 0;

        I2C_Init(speed);             //Configuration of MSSP as I2C communication
        I2C_Start();
        I2C_WriteByte((devAddr << 1) + 0);

        /*Start setup sequence*/
        LCD_Bus(0x00);     //lcd_rs = 0; lcd_rw = 0; lcd_enable = 0;        
        I2C_Stop();


    #else
    /*Initialise ports*/
    LCD_EN_ANS = 0;        
    LCD_RW_ANS = 0;         
    LCD_RS_ANS = 0;         

    LCD_DB0_ANS = 0;
    LCD_DB1_ANS = 0;   
    LCD_DB2_ANS = 0;     
    LCD_DB3_ANS = 0;      
    LCD_DB4_ANS = 0;        
    LCD_DB5_ANS = 0;       
    LCD_DB6_ANS = 0;        
    LCD_DB7_ANS = 0; 
        
    LCD_EN_TRIS = 0;        
    LCD_RW_TRIS = 0;         
    LCD_RS_TRIS = 0;         

    LCD_DB0_TRIS = 0;
    LCD_DB1_TRIS = 0;   
    LCD_DB2_TRIS = 0;     
    LCD_DB3_TRIS = 0;      
    LCD_DB4_TRIS = 0;        
    LCD_DB5_TRIS = 0;       
    LCD_DB6_TRIS = 0;        
    LCD_DB7_TRIS = 0; 
    
    #if LCD_8BITS_MODE  
    #else
        LCD_DB0_LAT = 0;
        LCD_DB1_LAT = 0;   
        LCD_DB2_LAT = 0;     
        LCD_DB3_LAT = 0;                 
    #endif
    /*Start setup sequence*/
    LCD_RS_LAT = 0;        
    LCD_RW_LAT = 0;
    LCD_EN_LAT = 0;          
    #endif


        
    __delay_ms(15);       
    
    LCD_Command(0x30);    
    __delay_ms(5);         
    LCD_Command(0x30);
    __delay_us(110);
    LCD_Command(0x30);
    __delay_us(40);
    
    #ifdef LCD_8BITS_MODE    
    #else
        LCD_Command(0x02);      
    #endif

    //__delay_us(40);
    #ifdef LCD_8BITS_MODE   
        LCD_Command(0x38);      //function set 
    #else
        LCD_Command(0x28);      //function set, 4 Bits, 2 Lines and font 5*8;   
    #endif
    __delay_us(40);
    LCD_Command(LCD_TURN_OFF);
    __delay_us(40);
    LCD_Command(LCD_CLEAR);      
    __delay_ms(2);
    LCD_Command(LCD_INC_ADDR);      //Entry Mode 
    __delay_us(40);
    /*End setup sequence*/
    
    LCD_Command(LCD_TURN_ON);     
    __delay_us(40);
    

}




/* ************************************************************************** */
/* @Brief: This function writes data in the bus. Address is fixed!! in 4 bits */
/*          mode.                                                             */ 
/* @Param:   n: data to write                                                */
/* @Return:                                                                   */
/* ************************************************************************** */
void LCD_Bus(unsigned char dato){
#ifdef _LCD_I2C
    I2C_WriteByte(dato);
#else
    #ifdef LCD_8BITS_MODE
        LCD_DATA_LAT = dato ;
    #else
        LCD_DB4_LAT = dato ;
        LCD_DB5_LAT = dato >>1;
        LCD_DB6_LAT = dato >>2;
        LCD_DB7_LAT = dato >>3;
    #endif
     
    LCD_EN_LAT = 1;
    LCD_EN_LAT = 0;
    __delay_us(100);
#endif
}

/* ************************************************************************** */
/* @Brief: This function writes a command in the bus                          */ 
/* @Param:  n: data to write                                                  */
/* @Return:                                                                   */
/* ************************************************************************** */
void LCD_Command(unsigned char cmd){
#ifdef _PMP
    *pointer = cmd;
#elif _LCD_I2C
    unsigned char lcddata; 
    I2C_Start();
    I2C_WriteByte((devAddr << 1) + 0);
    
    // Write high nibble
     lcddata = (cmd & 0xF0) |LCD_BL;

        //1.- RS=0; W/R=0
         LCD_Bus (lcddata);
        //2.-After Tas=40ns (Address Set-up time) activated enable
         //__delay_us (10);
         LCD_Bus (lcddata | LCD_EN);
        //3.- Minimum enable pulse with (230ns)
         //__delay_us(100);
        //4.-Desactivated enable and wait Tah=10ns(Address hold time)
         LCD_Bus (lcddata & ~LCD_EN); // Reset LCD bus
         //__delay_us(100);
         
    // Write low nibble
     lcddata = (cmd <<4) |LCD_BL;

        //1.- RS=0; W/R=0
         LCD_Bus (lcddata);
        //2.-After Tas=40ns (Address Set-up time) activated enable
         //__delay_us (10);
         LCD_Bus (lcddata | LCD_EN);
        //3.- Minimum enable pulse with (230ns)
         //__delay_us(100);
        //4.-Desactivated enable and wait Tah=10ns(Address hold time)
         LCD_Bus (lcddata & ~LCD_EN); // Reset LCD bus
         //__delay_us(100);
         
    I2C_Stop();
#else
    LCD_RS_LAT = 0;
    __delay_us(100); //Delay needed to avoid send a data whilst controller is busy

    __delay_us(100);
    LCD_RW_LAT = 0;
    __delay_us(100);
    
//notsure 100 about this two lines   
    LCD_EN_LAT = 1;
    __delay_us(100);
    
    #ifdef LCD_8BITS_MODE
        LCD_Bus(cmd);
    #else
        LCD_Bus(cmd >>4);
        LCD_Bus(cmd);
    #endif 
#endif
}

/* ************************************************************************** */
/* @Brief: This function writes a parameter in the bus                        */ 
/* @Param: n: data to write                                                   */
/* @Return:                                                                   */
/* ************************************************************************** */
void LCD_Parameter(unsigned char data){
#ifdef _PMP
    *pointer = data;
#elif _LCD_I2C
         unsigned char lcddata;
    I2C_Start();
    I2C_WriteByte((devAddr << 1) + 0);
    
    // Write high nibble
     lcddata = (data & 0xF0)  |LCD_BL|LCD_RS; // Get high nibble; and 0xF0 for
                                              // deleted low nibble
        //1.- RS=1; W/R=0
         LCD_Bus (lcddata);
        //2.-After Tas=40ns (Address Set-up time) activated enable
        // __delay_us (10);
         LCD_Bus (lcddata | LCD_EN);
        //3.- Minimum enable pulse with (230ns)
         //__delay_us(100);
        //4.-Desactivated enable and wait Tah=10ns(Address hold time)
         LCD_Bus (lcddata & ~LCD_EN); // Reset LCD bus
         //__delay_us(100);
 
    // Write low nibble
     lcddata = (data <<4) |LCD_BL|LCD_RS; // Get low nibble

        //1.- RS=1; W/R=0
         LCD_Bus (lcddata);
        //2.-After Tas=40ns (Address Set-up time) activated enable
         //__delay_us (10);
         LCD_Bus (lcddata | LCD_EN);
        //3.- Minimum enable pulse with (230ns)
         //__delay_us(100);
        //4.-Desactivated enable and wait Tah=10ns(Address hold time)
         LCD_Bus (lcddata & ~LCD_EN); // Reset LCD bus
         //__delay_us(100);
         
    I2C_Stop();
    
#else
    LCD_RS_LAT = 1;
    __delay_us(100); //Delay needed to avoid send a data whilst controller is busy

    __delay_us(100);
    LCD_RW_LAT = 0;
    __delay_us(100);

    #if LCD_8BITS_MODE
        LCD_Bus(data);
    #else
        LCD_Bus(data >>4);
        LCD_Bus(data);
    #endif
#endif
}
/* ************************************************************************** */
/* @Brief: This function sets the pointer a specific location                 */ 
/* @Param: x: x location                                                      */
/*         y: y location                                                      */
/* @Return:                                                                   */
/* ************************************************************************** */
void LCD_GoToXY(char row, char col) {
   char address ;
   if (row > LCD_N_LINES )row = LCD_N_LINES ;
   
   switch(row) {
     case 1 : address=0x80; LCDLINE = 1; break;
     case 2 : address=0xc0; LCDLINE = 2; break;
     case 3 : address=0x94; LCDLINE = 3; break;
     case 4 : address=0xd4; LCDLINE = 4; break;
   }
   address+=(col-1);
   LCD_Command(address);
   
}
/* ************************************************************************** */
/* @Brief:                                                                    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
/*WITH THIS FUNCTION IT'S POSIBLE USE PRINTF*/
void putch(char p)
{
    LCD_Parameter(p);
}

/* ************************************************************************** */
/* @Brief: This function sends a character to LCD. will display c on the next */
/*  position of the LCD. The following have special meaning:                  */
/*  \f  Clear display                                                         */
/*  \n  Go to start of second line                                            */
/*  \b  Move back one position                                                */
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void LCD_WriteByte(char c)
{
    switch (c) {
        case '\f'   : LCD_Command(LCD_CLEAR);
                     LCDLINE = 1;
                     __delay_ms(2);            break;
        case '\n'   : LCD_GoToXY(++LCDLINE, 1); break;
        case '\b'   : LCD_Command(0x10);       break;
        case '\r'   : LCD_GoToXY(LCDLINE, 1);  break;
        default     : LCD_Parameter(c);        break;
   }
}

/* ************************************************************************** */
/* @Brief:                                                                    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */
void LCD_WriteString(char *dato)
{
    while (*dato) 
    {
        LCD_Parameter(*dato); 
        dato++; 
    }
}




//next functions are not checked
/*char LCD_GetXY(char row, char col){
   char value;

    LCD_gotoxy(x,y);
    lcd_rs=1;
    value = lcd_read_byte();
    lcd_rs=0;
    return(value);
}*/

char LCD_ReadByte(){
#ifdef _PMP
   
#elif _LCD_I2C
#else
    char low,high;
    
    
    LCD_DB0_TRIS = 1;
    LCD_DB1_TRIS = 1;   
    LCD_DB2_TRIS = 1;     
    LCD_DB3_TRIS = 1;      
    LCD_DB4_TRIS = 1;        
    LCD_DB5_TRIS = 1;       
    LCD_DB6_TRIS = 1;        
    LCD_DB7_TRIS = 1;   
    
    #if LCD_8BITS_MODE
        LCD_RW_LAT = 1;
        __delay_us(1000);

        LCD_EN_LAT = 1;
        __delay_us(1000);

        high = LCD_DATA_PORT;

        LCD_EN_LAT = 0;

        LCD_DB0_TRIS = 0;
        LCD_DB1_TRIS = 0;   
        LCD_DB2_TRIS = 0;     
        LCD_DB3_TRIS = 0;      
        LCD_DB4_TRIS = 0;        
        LCD_DB5_TRIS = 0;       
        LCD_DB6_TRIS = 0;        
        LCD_DB7_TRIS = 0;  
        
        LCD_RS_LAT = 0;        
        LCD_RW_LAT = 0;
        LCD_EN_LAT = 0;          

        __delay_ms(15); 

        __delay_us(40);
    LCD_Command(0x28);      //function set, 0x28
    __delay_us(40);
    LCD_Command(LCD_CLEAR);      
    __delay_ms(2);
    LCD_Command(0x0C);      //Diplay on/off Control, 0x0c
    __delay_us(40);
    LCD_Command(0x06);      //Entry Mode Set, 0x06
    __delay_us(40);
        return (high);
    #else
        LCD_RW_LAT = 1;
        __delay_us(1);

        LCD_EN_LAT = 1;
        __delay_us(1);

        high = LCD_DATA_PORT;

        LCD_EN_LAT = 0;
        __delay_us(1);
        LCD_EN_LAT = 1;
        __delay_us(1);

        low = LCD_DATA_PORT;

        LCD_EN_LAT = 0;


        LCD_DB0_TRIS = 0;
        LCD_DB1_TRIS = 0;   
        LCD_DB2_TRIS = 0;     
        LCD_DB3_TRIS = 0;      
        LCD_DB4_TRIS = 0;        
        LCD_DB5_TRIS = 0;       
        LCD_DB6_TRIS = 0;        
        LCD_DB7_TRIS = 0;   

        return( (high<<4) | low);
    #endif 
        
#endif
    return 0;
}


/* ************************************************************************** */
/* @Brief:                                                                    */ 
/* @Param:                                                                    */
/* @Return:                                                                   */
/* ************************************************************************** */

void InitCustomChars(){
    int i;
    LCD_Command(0x40);   // Set CGRAM Address
    for (i = 0; i <= 63 ; i++)
//        LCD_putc(Custom_Char5x8[i]);

    LCD_Command(0X02);      // .. return to Home
};