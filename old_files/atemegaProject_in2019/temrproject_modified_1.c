#include <mega128.h>
#include <delay.h>
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FND_Null 16
#define FND_Star 14
#define FND_Sharp 15
unsigned int buf_seg[8] = {0,0,0,0,0,0,0,0};     // 편의를 위한 전역 변수(버퍼) 생성
unsigned int second;
unsigned int count;
unsigned int forseed;
  unsigned char easy_number_lcd[]="          ";
    unsigned char normal_number_lcd[]= "         ";
      unsigned char hard_number_lcd[]= "          ";
        unsigned int easy_number;
  unsigned int normal_number;
  unsigned int hard_number;
  unsigned char pad_to_lcd[] = "        ";
  unsigned int cnt_mode_1;
  unsigned int cnt_mode_2;
  unsigned int mode_flag;
  unsigned int game_flag;

void init_reg(void)



{

    DDRE=0xf0;
    DDRB=0xff;
    DDRC=0xf0;
    PORTC=0xff;
    TIMSK = (1 << TOIE0); //오버플로우(TOV0) 인터럽트 선택
    TCCR0 = (1 << CS02); //일반모드, 64분주비
    TCNT0 = -250; //카운터값 설정, 0.001초
    SREG |= 0x80; //전체 인터럽트 허가

}


interrupt [TIM0_OVF] void timer0_ovf(void)

{

    count++;

    forseed++; // for rand(seed);
    if(count == 1000) //0.001 * 1000 = 1초 마다 동작
    {
       count = 0; //count값 재설
       second++;    // (variable named second will add 1 per 1second.
    }

}

unsigned char Keyscan(void)



{



    unsigned char key_scan_line = 0xef;
    unsigned char key_scan_loop = 0, getPinData = 0;
    unsigned char key_num = 0;

    for(key_scan_loop=0; key_scan_loop<4; key_scan_loop++)



    {

        PORTC = key_scan_line;



        delay_us(1);







        getPinData = PINC&0x0f;







        if(getPinData != 0x00)



        {



            switch(getPinData)



            {



                case 0x01:



                key_num=key_scan_loop*4+1;



                break;







                case 0x02:



                key_num=key_scan_loop*4+2;



                break;







                case 0x04:



                key_num=key_scan_loop*4+3;



                break;







                case 0x08:



                key_num=key_scan_loop*4+4;



                break;



            }



            return key_num;



                                         }



        else;

        key_scan_line=(key_scan_line<<1);



        delay_us(1);



        }



}

unsigned char Key_data_trans(unsigned char New_key_data)



{



unsigned char key_num=0;

if(New_key_data%4 !=0)



{



key_num = (New_key_data/4)*3+(New_key_data%4);



switch(key_num)



{



 case 10:



 key_num = FND_Star;

 break;

 case 11:

 key_num = FND_Null;

 break;

 case 12:



 key_num = FND_Sharp;



 break;



  }



 }



 else



  key_num = (New_key_data/4)+9;



  return key_num;



  }


void Key_pad_in(unsigned char* New_key_data, unsigned char* Key_off_flag)



{

 if(*New_key_data)



 {



  if(*Key_off_flag)  // buffer has 8 slots



  {


   buf_seg[7] = buf_seg[6];
   buf_seg[6] = buf_seg[5];
   buf_seg[5] = buf_seg[4];
   buf_seg[4] = buf_seg[3];
   buf_seg[3] = buf_seg[2];
   buf_seg[2] = buf_seg[1];
   buf_seg[1] = buf_seg[0];
   *Key_off_flag = ~*Key_off_flag;



   }



   else;



        buf_seg[0] = Key_data_trans(*New_key_data);



        }



        else



    *Key_off_flag=0xff;


 }



void pad_to_lcd_function()

{

pad_to_lcd[0] = '0' + buf_seg[0];

pad_to_lcd[1] = '0' + buf_seg[1];

pad_to_lcd[2] = '0' + buf_seg[2] ;

pad_to_lcd[3] = '0' + buf_seg[3] ;

pad_to_lcd[4] = '0' + buf_seg[4] ;

pad_to_lcd[5] = '0' + buf_seg[5] ;

pad_to_lcd[6] = '0' + buf_seg[6]  ;

pad_to_lcd[7] = '0' + buf_seg[7]  ;







}


unsigned int normal_random_number()   //5자리

{

 unsigned int stNum = 10000, endNum = 99999;
    unsigned int randNum = 0;

    randNum = (rand() % (endNum - stNum + 1))   + stNum;        // 7자리로 맞추기

    return randNum;




}

void easy_number_string_function()   // Transforming integer into String function



{                                                  //test int change



  unsigned char test_string_0;
    unsigned char test_string_10;
    unsigned char test_string_100;
    test_string_100 = easy_number/100;
    test_string_10 =  (easy_number - 100*(test_string_100))/10;
    test_string_0 =  easy_number - (easy_number/10)*10;
   easy_number_lcd[0]  = '0' + test_string_100;
   easy_number_lcd[1] = '0' + test_string_10;
   easy_number_lcd[2] = '0' + test_string_0;
}



void normal_number_string_function()



{                                                  //test int change



  unsigned char test_string_0;

    unsigned char test_string_10;

    unsigned char test_string_100;

    unsigned char test_string_1000;

    unsigned char test_string_10000;

    test_string_10000 = normal_number/10000;                               // 51234     10000 -> 5
    test_string_1000 =  (normal_number - 10000*(test_string_10000))/1000;          //   (51234 - 50000 ) / 1000
    test_string_100 =  (normal_number - 10000*(test_string_10000) - 1000*(test_string_1000))/100;
    test_string_10 =   (normal_number - 10000*(test_string_10000) - 1000*(test_string_1000) - 100*(test_string_100))/10;
    test_string_0 =  (normal_number - 10000*(test_string_10000) - 1000*(test_string_1000) - 100*(test_string_100) - 10*(test_string_10));
   normal_number_lcd[0]  = '0' + test_string_10000;
   normal_number_lcd[1] = '0' + test_string_1000;
   normal_number_lcd[2] = '0' + test_string_100;
   normal_number_lcd[3] = '0' + test_string_10;
   normal_number_lcd[4] = '0' + test_string_0;

}


    void correct_function(void)

{
 unsigned char correct[] = " CONGRATURATION ! ";

                          cnt_mode_1 = 0;

                          cnt_mode_2 = 0;
                          mode_flag = 0;

                          LCD_Clear();
                           LCD_Clear();
                            LCD_Clear();

                          LCD_Pos(1,0);

                          LCD_Str(correct);

                          delay_ms(1000);

                          game_flag = game_flag + 1;

}

void fail_function(void)

{

unsigned char fail[] = " FAIL TT ";
                          cnt_mode_1 = 0;
                          cnt_mode_2 = 0;
		    mode_flag = 0;
			LCD_Clear();
                           LCD_Clear();
                            LCD_Clear();
                          LCD_Pos(1,0);
                          LCD_Str(fail);
                          delay_ms(1000);
                          game_flag = game_flag + 1;
}



void main(void)

{
  unsigned char Key_off_flag=0;
unsigned char New_key_data=0;
  unsigned char game_mode[] = " GAME MODE ";
 unsigned char easy[] = " EASY ";
  unsigned char normal[] = " NORMAL ";
  unsigned char hard[] = " HARD ";
  unsigned int level = 0; // variable for level. (0~2)
  unsigned char mode_select[] = " MODE SELECT ";
 unsigned char game_start[]= " GAME START!! ";
unsigned char question[] = " QUESTION " ;
 LCD_Init();
LCD_Init();
 LCD_Init();
  init_reg();
  while(1)

  {

 init_reg();
  game_flag = 0;
 LCD_Clear();
 LCD_Clear();
LCD_Init();

 LCD_Init();
switch(mode_flag)
{
case 0:
  while( cnt_mode_1 == 0 ) // initial mode.
  {

    New_key_data=Keyscan();

    Key_pad_in(&New_key_data,&Key_off_flag);

    LCD_Pos(0,0);

    LCD_Str(game_mode);

    switch(level)

    {

     case  0:

     LCD_Pos(1,0);

     LCD_Str(easy);

     break;


     case  1:

     LCD_Pos(1,0);

     LCD_Str(normal);

     break;

     case  2:

     LCD_Pos(1,0);
     LCD_Str(hard);

     break;



     default:

    }

    if( buf_seg[0] == 10)

    {


     cnt_mode_1 = cnt_mode_1 + 1;
     mode_flag = 1;

     buf_seg[0] = 0;
     cnt_mode_2 = 0;

    }


    else if (buf_seg[0] == 14)

    {

     mode_flag = 2;            // game start.
     cnt_mode_1 = cnt_mode_1 + 1;
     buf_seg[0] = 0;
     cnt_mode_2 = 0;
    }

   }

  break;
  case 1:
while ( cnt_mode_2 == 0)
{


    New_key_data=Keyscan();

LCD_Pos(0,0);
LCD_Str(mode_select);
if(buf_seg[0] == 11)
{
  level = 0;
      buf_seg[0] = 0;
 LCD_Pos(1,0);
  LCD_Str(easy);

}

else if (buf_seg[0] == 12)

{
  level = 1;

    buf_seg[0] = 0;
      LCD_Pos(1,0);
  LCD_Str(normal);

}

else if ( buf_seg [0] == 13)

{
 level = 2;
   buf_seg[0] = 0;
     LCD_Pos(1,0);
 LCD_Str(hard);

}

else if ( buf_seg [0] == 10)
{



  cnt_mode_2 = cnt_mode_2 + 1;
  mode_flag = 0;
  cnt_mode_1 = 0;
    buf_seg[0] = 0;

}

}
break ;
case 2 : // game mode ..

second = 0;
if(second <= 1)
{

LCD_Pos(0,0);


 LCD_Str("             ") ;

 LCD_Pos(0,0);

 LCD_Str(game_start);


}


LCD_Clear();


if(level == 0)
    {

        LCD_Clear();

         LCD_Pos(0,0);

         LCD_Str(question);

        srand(forseed);

        easy_number = 100 + (rand() % 899); // rand number 100 ~ 999

        easy_number_string_function();

            second = 0;



                    while(second <3)
                             {


                                                        LCD_Pos(0,1);
                                                        LCD_Str(easy_number_lcd);


                            }

                                LCD_Clear();

                   buf_seg[0]=0;
                   second = 0;
                   while(game_flag == 0)
                   {



                         New_key_data=Keyscan();
                         Key_pad_in(&New_key_data,&Key_off_flag);
                         pad_to_lcd_function() ;
                         LCD_Pos(0,0);
                         LCD_Str(pad_to_lcd);
                         if(second >5)
                         {

                         if( ((buf_seg[2]*100)+ (buf_seg[1]*10) + buf_seg[0]) == easy_number )



                         {
                          correct_function();

                         }

                         else if(((buf_seg[2]*100)+ (buf_seg[1]*10) + buf_seg[0]) != easy_number)

                         {
                         fail_function();
                         }

                         }

                         else if(buf_seg[0] == 14)



                         {

                           if( ((buf_seg[3]*100)+ (buf_seg[2]*10) + buf_seg[1]) == easy_number )



                         {
                           correct_function();

                         }

                         else if(((buf_seg[3]*100)+ (buf_seg[2]*10) + buf_seg[1]) != easy_number)



                         {
                             fail_function();
                         }


                         }


                   }


}


else if (level == 1)

{
    LCD_Clear();
         LCD_Clear();
          LCD_Clear();
         LCD_Pos(0,0);
         LCD_Str(question);
         srand(forseed);
        normal_number = normal_random_number();
         normal_number_string_function();
               second = 0;
         while(second <3)

                             {
                                                        LCD_Pos(0,1);
                                                        LCD_Str(normal_number_lcd);

                            }
                    LCD_Clear();
                   buf_seg[0]=0;
                   second = 0;
                   while(game_flag == 0)
                   {

                         New_key_data=Keyscan();
                         Key_pad_in(&New_key_data,&Key_off_flag);
                           pad_to_lcd_function() ;
                         LCD_Pos(0,0);
                         LCD_Str(pad_to_lcd);
                         if(second >5)

                         {


                         if( ((buf_seg[4]*10000 + buf_seg[3] * 1000) + (buf_seg[2]*100)+ (buf_seg[1]*10) + buf_seg[0]) == normal_number )



                         {
                          correct_function();
                         }

                         else if(((buf_seg[4]*10000 + buf_seg[3] * 1000) + (buf_seg[2]*100)+ (buf_seg[1]*10) + buf_seg[0]) != normal_number)


                         {

                          fail_function();
                         }
                         }

                         else if (buf_seg[0] == 14)

                         {

                          if( (buf_seg[5]*10000 + buf_seg[4]*1000 + buf_seg[3]*100 + buf_seg[2]*10 + buf_seg[1]) == normal_number)

                          {

                            correct_function();
                          }

                          else

                          {

                            fail_function();
                          }

                         }


                   }

}
else if(level == 2)
{

  LCD_Clear();

         LCD_Pos(0,0);
        LCD_Str(question);
         srand(forseed);

          normal_number = normal_random_number();
         normal_number_string_function();
               second = 0;
         while(second <3)

                             {


                                                        LCD_Pos(0,1);
                                                        LCD_Str(normal_number_lcd);

                            }

                    LCD_Clear();
                   buf_seg[0]=0;
                   second = 0;
                   while(game_flag == 0)
         {

                         New_key_data=Keyscan();
                         Key_pad_in(&New_key_data,&Key_off_flag);
                           pad_to_lcd_function() ;
                         LCD_Pos(0,0);
                         LCD_Str(pad_to_lcd);
                         if(second >5)

                         {


                         if( ((buf_seg[4]*10000 + buf_seg[3] * 1000) + (buf_seg[2]*100)+ (buf_seg[1]*10) + buf_seg[0]) == normal_number )



                         {
                          correct_function();
                         }

                         else if(((buf_seg[4]*10000 + buf_seg[3] * 1000) + (buf_seg[2]*100)+ (buf_seg[1]*10) + buf_seg[0]) != normal_number)


                         {

                          fail_function();
                         }
                         }

                         else if (buf_seg[0] == 14)

                         {

                          if( (buf_seg[5]*10000 + buf_seg[4]*1000 + buf_seg[3]*100 + buf_seg[2]*10 + buf_seg[1]) == normal_number)

                          {

                            correct_function();
                          }

                          else

                          {

                            fail_function();
                          }

                         }


                   }

}

break;


}


}


         }