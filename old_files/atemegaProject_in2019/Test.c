
#include <mega128.h>
#include <delay.h>

#define FND_Null  17
#define FND_Star  18
#define FND_Sharp 19

#define READ_COL PINC >>4;
#define WRITE_ROW PORTC
#define FND_DIG PORTE
#define FND_DATA PORTB
                                                      // timer 0 -> for debounce time 2 -> to count time


// Fnd 문자표 및 fnd포트 핀 설정
unsigned int FND_char[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90};          //0x88, 0x83, 0xc4, 0xa1, 0x84, 0x8e};
unsigned int FND_dig[] ={0x1f,0x2f,0x4f,0x8f,0x0f};    // FND0 ON, FND1 ON, FND2 ON, FND3 ON, ALL FND OFF
unsigned char sec,min;
char count;


void Init_port(void)                      // initial condition of regs
{
    DDRE =0xf0;    // 1111 0000 -> what resister is this ?, DDRE ?? Port E , left nibble is output, right nibble is input.
    DDRB = 0xff;   // 1111 1111 all ports belonged in B are output
    DDRC = 0x0f;
    PORTC = 0x0f;   // all bits in port c are output, this means output of port c is 1111 0000
    PORTE = FND_dig[4]; // sent selecting
}

void Init_Timer(void)                    // count_time0 is used for chattering prohibition funcution .
{
TIMSK = (1<< TOIE0)|(1<<TOIE2);
TCCR0 &=~((1<<CS02)|(1<<CS01)|(1<<CS00)); // normal mode and 1024 prescailing
TCNT0 = - 70;
TCCR2 = (1<<CS22)|(1<<CS21)|(1<<CS20);
TCNT2 = -5;
SREG |= 0x80;
}

interrupt [TIM0_OVF] void timer_ovf0(void)
{
 count ++;
 TCNT0 = - 70;
}

 interrupt [TIM2_OVF] void timer2_overflow(void)
{
    TCNT2 = -5;
    count++;
    if(count == 2881)
    {
        sec++;
        count = 0;
    }
    if(sec == 60)
    {
        sec = 0;
        min++;
    }
    if(min == 60)
    {
        min = 0;
    }
}

unsigned char Debounce(unsigned char row)
{
 TCCR0 = ((1<<CS02)|(1<<CS01)|(1<<CS00));
 count = 0;
 while(count >1);
 TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));
 WRITE_ROW = row;
 return READ_COL;
}

void FND_Display(unsigned int* seg_value)
{

    FND_DIG = FND_dig[0];
    FND_DATA = FND_char[seg_value[0]];
    delay_ms(1);

    FND_DIG = FND_dig[1];
    FND_DATA = FND_char[seg_value[1]];
    delay_ms(1);

    FND_DIG = FND_dig[2];
    FND_DATA = FND_char[seg_value[2]];
    delay_ms(1);

    FND_DIG = FND_dig[3];
    FND_DATA = FND_char[seg_value[3]];
    delay_ms(1);

}

unsigned char KeyScan(void)
{

    unsigned int KeyScan_Line_Sel = 0xf7;
    unsigned char KeyScan_Sel=0, Key_num=0;
    unsigned char Get_Key_Data = 0;

    for(KeyScan_Sel = 0; KeyScan_Sel <4; KeyScan_Sel ++)
    {

    WRITE_ROW = KeyScan_Line_Sel;
    delay_us(10);
    Get_Key_Data = READ_COL;

    if(Get_Key_Data != 0x00)

                {
     Get_Key_Data = Debounce(KeyScan_Line_Sel);
     switch(Get_Key_Data)
                    {
     case 0x01:

     Key_num = KeyScan_Sel*4 + 1;
     break;

     case 0x02:

     Key_num = KeyScan_Sel*4 +2;
     break;

     case 0x04:
     Key_num = KeyScan_Sel*4 +3;
     break;

     case 0x08:
     Key_num = KeyScan_Sel*4 +4;
     break;

     default :
     Key_num = FND_Null;


                     }

                     return Key_num;

            }

            KeyScan_Line_Sel = (KeyScan_Line_Sel>>1);

    }

        return Key_num;

}




void FND_ClockDisplay(unsigned char Min, unsigned char Sec)
{
    FND_DIG = FND_dig[0];
    FND_DATA = FND_char[Sec%10];
    delay_ms(1);

    FND_DIG = FND_dig[1];
    FND_DATA = FND_char[Sec/10];
    delay_ms(1);

    if(Sec % 2)
    {
        FND_DIG = FND_dig[2];
        FND_DATA = FND_char[Min%10]&0x7f;
        delay_ms(1);
    }

    FND_DIG = FND_dig[3];
    FND_DATA = FND_char[Min/10];
    delay_ms(1);

}



void main(void)


{

    bit Key_off_flag = 0;
    unsigned char New_key_data = 0, key_Num = 0,  octave_value =4;
    unsigned int buf_seg[4] = {FND_Null, FND_Null, FND_Null, FND_Null};

    PORTG = 0x10;

    Init_port();
    Init_Timer();

    while(1)


{

    if((buf_seg[0] & buf_seg[1] & buf_seg[2] & buf_seg[3]) != 0)


    {


         New_key_data = KeyScan();

             if(New_key_data)
        {
               if(New_key_data%4 != 0)
            {
                key_Num = (New_key_data/4)*3+(New_key_data%4);

                  if(key_Num >= 10)
               {
                   switch(key_Num)
                  {

                    case 10 :
                    key_Num = FND_Null;
                    break;

                    case 11 :
                    key_Num = FND_Null;
                    break;

                    case 12 :
                    key_Num = FND_Null;

                    default :
                    break;
                  }

               }

            else;

            }

        }

         else

         key_Num = (New_key_data/4)+9;

      if(Key_off_flag)
      {
       buf_seg[3] = buf_seg[2];
       buf_seg[2] = buf_seg[1];
       buf_seg[1] = buf_seg[0];
       Key_off_flag = ~Key_off_flag;
       }
       buf_seg[0] = key_Num;
     }


      else

      Key_off_flag = 1;

      FND_Display(buf_seg);


      }



      else;               // if 1~4 all of buffers are filled with char  then ...

 sec = (10*buf_seg[1]) + buf_seg[0] ;
 min = (10*buf_seg[3]) + buf_seg[2] ;
 FND_ClockDisplay(min,sec);






}






}




