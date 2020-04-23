#include <delay.h>
#include <mega128.h>
#include "lcd.h"

#define LCD_WDATA PORTA
#define LCD_WINST PORTA

#define LCD_CTRL PORTG
#define LCD_EN 0
#define LCD_RW 1
#define LCD_RS 2

void LCD_PORT_Init(void)

{

DDRA = 0xff;
DDRG = 0x0f;

}


void LCD_Data(unsigned char ch)
{

LCD_CTRL |= (1<< LCD_RS);
LCD_CTRL &= ~(1<<LCD_RW);
LCD_CTRL |= (1 << LCD_EN);
delay_us(50);
LCD_WDATA = ch;
delay_us(50);
LCD_CTRL &= ~(1<< LCD_EN);
}


void LCD_Comm(unsigned char ch)
{

LCD_CTRL &= ~(1<<LCD_RS);
LCD_CTRL &= ~(1<<LCD_RW);
LCD_CTRL |= (1<<LCD_EN);
delay_us(50);
LCD_WINST = ch;
delay_us(50);
LCD_CTRL &= ~ (1 << LCD_EN);
}


void LCD_Delay(unsigned char ms)
{

delay_ms(ms);
}

void LCD_Char (unsigned char c)
{

LCD_Data(c);
delay_ms(1);
}


void LCD_Str(unsigned char *str)
{

while ( *str != 0) {
            LCD_Char(*str);
            str++;
            }
       }



void LCD_Pos(unsigned char x, unsigned char y)
{

LCD_Comm(0x80|(x*0x40+y));
}

void LCD_Clear (void)
{
LCD_Comm(0x01);
LCD_Delay(2);
}

void LCD_Init(void)
{

LCD_PORT_Init();

LCD_Comm(0x38);
LCD_Delay(4);
LCD_Comm(0x38);
LCD_Delay(4);
LCD_Comm(0x38);
LCD_Delay(4);
LCD_Comm(0x0e);
LCD_Delay(2);
LCD_Comm(0x06);
LCD_Delay(2);
LCD_Clear();
}


void LCD_Display_Shift(unsigned char p)
{
if(p == RIGHT) {
    LCD_Comm(0x1c);
    LCD_Delay(1);
  }
  
else if (p == LEFT){
    LCD_Comm(0x18);
    LCD_Delay(1);
    }
    
}


void LCD_Cursor_Shift(unsigned char p)
{
if(p == RIGHT) {
    LCD_Comm(0x14);
    LCD_Delay(1);
  }
  
else if (p == LEFT){
    LCD_Comm(0x10);
    LCD_Delay(1);
    }
    
}
            

void LCD_Cursor_Home(void)
{
LCD_Comm(0x02);
LCD_Delay(2);
}

