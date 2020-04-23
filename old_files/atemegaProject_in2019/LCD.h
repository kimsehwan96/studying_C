#include <new_mega128.h>
#include <delay.h>

#define LCD_WDATA       PORTA    // LCD ������ ��Ʈ ����
#define LCD_WINST       PORTA

#define LCD_CTRL        PORTG    // LCD ������Ʈ ����
#define LCD_EN          0
#define LCD_RW          1
#define LCD_RS          2

#define Byte unsigned char

#define On              1    //�Ҹ��� ��� ����
#define Off             0

void Port_Init(void)
{
    DDRA = 0xFF;
    DDRG = 0x0F;
    DDRF = 0x00;
}

#define RIGHT           1
#define LEFT            0

void LCD_Data(Byte ch)
{
    LCD_CTRL |= (1 << LCD_RS);
    LCD_CTRL &= ~(1 << LCD_RW);
    LCD_CTRL |= (1 << LCD_EN);
    delay_us(50);
    LCD_WDATA = ch;
    delay_us(50);
    LCD_CTRL &= ~(1 << LCD_EN);
}


void LCD_Comm(Byte ch)
{
    LCD_CTRL &= ~(1 << LCD_RS);
    LCD_CTRL &= ~(1 << LCD_RW);
    LCD_CTRL |= (1 << LCD_EN);
    delay_us(50);
    LCD_WINST = ch;
    delay_us(50);
    LCD_CTRL &= ~(1 << LCD_EN);
}

void LCD_delay(Byte ms)
{
    delay_ms(ms);
}

void LCD_CHAR(Byte c)
{
   delay_ms(1); 
   LCD_Data(c);
}

void LCD_STR(unsigned char *str)
{
    while(*str != 0) {
        LCD_CHAR(*str);
        str++;
    }
}

//void Putc_LCD(Byte ch);          //LCD ǥ�� ���

void LCD_pos(unsigned char col, unsigned char row) // LCD ������ ����
{
    LCD_Comm(0x80|(row+col*0x40));
}

void LCD_Clear(void)        // ȭ�� Ŭ���� (1)
{
    LCD_Comm(0x01);
    LCD_delay(2);
}

void LCD_Init(void)
{
    LCD_Comm(0x38);
    LCD_delay(2);
    LCD_Comm(0x38);
    LCD_delay(2);
    LCD_Comm(0x38);
    LCD_delay(2);
    LCD_Comm(0x0e);
    LCD_delay(2);
    LCD_Comm(0x06);
    LCD_delay(2);
    

    LCD_Clear();
} 

void Cursor_Home(void)
{
    LCD_Comm(0x02);
    LCD_delay(2);
}


void LCD_Shift(char p)
{
    if(p==RIGHT){
        LCD_Comm(0x1c);
        LCD_delay(1); // �ð�����
    }
    
    //ǥ�� ȭ�� ��ü�� �������� �̵�
    else if(p == LEFT) {
        LCD_Comm(0x18);
        LCD_delay(1);
     }
}

              
