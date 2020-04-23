// CodeVisionAVR C Compiler
// (C) 1998-2004 Pavel Haiduc, HP InfoTech S.R.L.

// I/O registers definitions for the ATmega128

#ifndef _MEGA128_INCLUDED_
#define _MEGA128_INCLUDED_

#pragma used+
sfrb PINF=0;
sfrb PINE=1;
sfrb DDRE=2;
sfrb PORTE=3;
sfrb ADCL=4;
sfrb ADCH=5;
sfrw ADCW=4;      // 16 bit access
sfrb ADCSRA=6;
sfrb ADMUX=7;
sfrb ACSR=8;
sfrb UBRR0L=9;
sfrb UCSR0B=0xa;
sfrb UCSR0A=0xb;
sfrb UDR0=0xc;
sfrb SPCR=0xd;
sfrb SPSR=0xe;
sfrb SPDR=0xf;
sfrb PIND=0x10;
sfrb DDRD=0x11;
sfrb PORTD=0x12;
sfrb PINC=0x13;
sfrb DDRC=0x14;
sfrb PORTC=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb PINA=0x19;
sfrb DDRA=0x1a;
sfrb PORTA=0x1b;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEARL=0x1e;
sfrb EEARH=0x1f;
sfrw EEAR=0x1e;   // 16 bit access
sfrb SFIOR=0x20;
sfrb WDTCR=0x21;
sfrb OCDR=0x22;
sfrb OCR2=0x23;
sfrb TCNT2=0x24;
sfrb TCCR2=0x25;
sfrb ICR1L=0x26;
sfrb ICR1H=0x27;
sfrw ICR1=0x26;   // 16 bit access
sfrb OCR1BL=0x28;
sfrb OCR1BH=0x29;
sfrw OCR1B=0x28;  // 16 bit access
sfrb OCR1AL=0x2a;
sfrb OCR1AH=0x2b;
sfrw OCR1A=0x2a;  // 16 bit access
sfrb TCNT1L=0x2c;
sfrb TCNT1H=0x2d;
sfrw TCNT1=0x2c;  // 16 bit access
sfrb TCCR1B=0x2e;
sfrb TCCR1A=0x2f;
sfrb ASSR=0x30;
sfrb OCR0=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0=0x33;
sfrb MCUCSR=0x34;
sfrb MCUCR=0x35;
sfrb TIFR=0x36;
sfrb TIMSK=0x37;
sfrb EIFR=0x38;
sfrb EIMSK=0x39;
sfrb EICRB=0x3a;
sfrb RAMPZ=0x3b;
sfrb XDIV=0x3c;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#define DDRF (*(unsigned char *) 0x61)
#define PORTF (*(unsigned char *) 0x62)
#define PING (*(unsigned char *) 0x63)
#define DDRG (*(unsigned char *) 0x64)
#define PORTG (*(unsigned char *) 0x65)
#define SPMCSR (*(unsigned char *) 0x68)
#define EICRA (*(unsigned char *) 0x6a)
#define XMCRB (*(unsigned char *) 0x6c)
#define XMCRA (*(unsigned char *) 0x6d)
#define OSCCAL (*(unsigned char *) 0x6f)
#define TWBR (*(unsigned char *) 0x70)
#define TWSR (*(unsigned char *) 0x71)
#define TWAR (*(unsigned char *) 0x72)
#define TWDR (*(unsigned char *) 0x73)
#define TWCR (*(unsigned char *) 0x74)
#define OCR1CL (*(unsigned char *) 0x78)
#define OCR1CH (*(unsigned char *) 0x79)
#define TCCR1C (*(unsigned char *) 0x7a)
#define ETIFR (*(unsigned char *) 0x7c)
#define ETIMSK (*(unsigned char *) 0x7d)
#define ICR3L (*(unsigned char *) 0x80)
#define ICR3H (*(unsigned char *) 0x81)
#define OCR3CL (*(unsigned char *) 0x82)
#define OCR3CH (*(unsigned char *) 0x83)
#define OCR3BL (*(unsigned char *) 0x84)
#define OCR3BH (*(unsigned char *) 0x85)
#define OCR3AL (*(unsigned char *) 0x86)
#define OCR3AH (*(unsigned char *) 0x87)
#define TCNT3L (*(unsigned char *) 0x88)
#define TCNT3H (*(unsigned char *) 0x89)
#define TCCR3B (*(unsigned char *) 0x8a)
#define TCCR3A (*(unsigned char *) 0x8b)
#define TCCR3C (*(unsigned char *) 0x8c)
#define UBRR0H (*(unsigned char *) 0x90)
#define UCSR0C (*(unsigned char *) 0x95)
#define UBRR1H (*(unsigned char *) 0x98)
#define UBRR1L (*(unsigned char *) 0x99)
#define UCSR1B (*(unsigned char *) 0x9a)
#define UCSR1A (*(unsigned char *) 0x9b)
#define UDR1 (*(unsigned char *) 0x9c)
#define UCSR1C (*(unsigned char *) 0x9d)

// Interrupt vectors definitions

#define EXT_INT0 2
#define EXT_INT1 3
#define EXT_INT2 4
#define EXT_INT3 5
#define EXT_INT4 6
#define EXT_INT5 7
#define EXT_INT6 8
#define EXT_INT7 9
#define TIM2_COMP 10
#define TIM2_OVF 11
#define TIM1_CAPT 12
#define TIM1_COMPA 13
#define TIM1_COMPB 14
#define TIM1_OVF 15
#define TIM0_COMP 16
#define TIM0_OVF 17
#define SPI_STC 18
#define USART0_RXC 19
#define USART0_DRE 20
#define USART0_TXC 21
#define ADC_INT 22
#define EE_RDY 23
#define ANA_COMP 24
#define TIM1_COMPC 25
#define TIM3_CAPT 26
#define TIM3_COMPA 27
#define TIM3_COMPB 28
#define TIM3_COMPC 29
#define TIM3_OVF 30
#define USART1_RXC 31
#define USART1_DRE 32
#define USART1_TXC 33
#define TWI 34
#define SPM_RDY 35

//추가사항 new_mega128
//각 레지스터 번호 define
//typedefinition

typedef unsigned char   Byte;
typedef unsigned int    Word;

#define sei() #asm("sei")
#define cli() #asm("cli")

//PORTA 관련 레지스터 정의
//PINA
#define PINA7	7
#define PINA6	6
#define PINA5	5
#define PINA4	4
#define PINA3	3
#define PINA2	2
#define PINA1	1
#define PINA0	0

//DDRA
#define DDRA7	7
#define DDRA6	6
#define DDRA5	5
#define DDRA4	4
#define DDRA3	3
#define DDRA2	2
#define DDRA1	1
#define DDRA0	0

//PORTA
#define PORTA7	7
#define PORTA6	6
#define PORTA5	5
#define PORTA4	4
#define PORTA3	3
#define PORTA2	2
#define PORTA1	1
#define PORTA0	0

//PORTB의 레지스터 관련 정의
//PINB
#define PINB7	7
#define PINB6	6
#define PINB5	5
#define PINB4	4
#define PINB3	3
#define PINB2	2
#define PINB1	1
#define PINB0	0

//DDRB
#define DDRB7	7
#define DDRB6	6
#define DDRB5	5
#define DDRB4	4
#define DDRB3	3
#define DDRB2	2
#define DDRB1	1
#define DDRB0	0

//PORTB
#define PORTB7	7
#define PORTB6	6
#define PORTB5	5
#define PORTB4	4
#define PORTB3	3
#define PORTB2	2
#define PORTB1	1
#define PORTB0	0

//PORTC의 레지스터 관련 정의
//PINC
#define PINC7	7
#define PINC6	6
#define PINC5	5
#define PINC4	4
#define PINC3	3
#define PINC2	2
#define PINC1	1
#define PINC0	0

//DDRC
#define DDRC7	7
#define DDRC6	6
#define DDRC5	5
#define DDRC4	4
#define DDRC3	3
#define DDRC2	2
#define DDRC1	1
#define DDRC0	0

//PORTC
#define PORTC7	7
#define PORTC6	6
#define PORTC5	5
#define PORTC4	4
#define PORTC3	3
#define PORTC2	2
#define PORTC1	1
#define PORTC0	0

//PORTD의 레지스터 관련 정의
//PIND              
#define PIND7	7
#define PIND6	6
#define PIND5	5
#define PIND4	4
#define PIND3	3
#define PIND2	2
#define PIND1	1
#define PIND0	0
                    
//DDRD              
#define DDRD7	7
#define DDRD6	6
#define DDRD5	5
#define DDRD4	4
#define DDRD3	3
#define DDRD2	2
#define DDRD1	1
#define DDRD0	0
                    
//PORTD             
#define PORTD7	7
#define PORTD6	6
#define PORTD5	5
#define PORTD4	4
#define PORTD3	3
#define PORTD2	2
#define PORTD1	1
#define PORTD0	0

//PORTE의 레지스터 관련 정의
//PINE              
#define PINE7	7
#define PINE6	6
#define PINE5	5
#define PINE4	4
#define PINE3	3
#define PINE2	2
#define PINE1	1
#define PINE0	0
                    
//DDRE              
#define DDRE7	7
#define DDRE6	6
#define DDRE5	5
#define DDRE4	4
#define DDRE3	3
#define DDRE2	2
#define DDRE1	1
#define DDRE0	0
                    
//PORTE             
#define PORTE7	7
#define PORTE6	6
#define PORTE5	5
#define PORTE4	4
#define PORTE3	3
#define PORTE2	2
#define PORTE1	1
#define PORTE0	0

//PORTF의 레지스터 관련 정의
//PINF              
#define PINF7	7
#define PINF6	6
#define PINF5	5
#define PINF4	4
#define PINF3	3
#define PINF2	2
#define PINF1	1
#define PINF0	0
                    
//DDRF              
#define DDRF7	7
#define DDRF6	6
#define DDRF5	5
#define DDRF4	4
#define DDRF3	3
#define DDRF2	2
#define DDRF1	1
#define DDRF0	0
                    
//PORTF             
#define PORTF7	7
#define PORTF6	6
#define PORTF5	5
#define PORTF4	4
#define PORTF3	3
#define PORTF2	2
#define PORTF1	1
#define PORTF0	0

//PORTG의 레지스터 관련 정의
//PING              
#define PING4	4
#define PING3	3
#define PING2	2
#define PING1	1
#define PING0	0
                    
//DDRG              
#define DDRG4	4
#define DDRG3	3
#define DDRG2	2
#define DDRG1	1
#define DDRG0	0
                    
//PORTG             
#define PORTG4	4
#define PORTG3	3
#define PORTG2	2
#define PORTG1	1
#define PORTG0	0

//UCSR1A의 비트 정의
#define RXC1 	7
#define TXC1    6
#define UDRE1   5
#define FE1     4
#define DOR1    3
#define UPE1    2
#define U2X1    1
#define MPCM1   0

//OSCCAL의 비트 정의
#define CAL6	7
#define CAL5	6
#define CAL4	5
#define CAL3	4
#define CAL2	3
#define CAL1	2
#define CAL0	1

//ACSR의 비트 정의
#define ACD	7
#define ACBG	6
#define ACO	5
#define ACI	4
#define ACIE	3
#define ACIC 	2
#define ACIS1	1
#define ACIS0	0

//UCSR0A의 비트 정의
#define RXC0 	7
#define TXC0    6
#define UDRE0   5
#define FE0     4
#define DOR0    3
#define UPE0    2
#define U2X0    1
#define MPCM0   0

//UCSR0B의 비트 정의
#define RXCIE0	7
#define TXCIE0  6
#define UDRIE0  5
#define RXEN0   4
#define TXEN0   3
#define UCSZ02  2
#define RXB80   1
#define TXB80   0

//SPCR의 비트 정의
#define SPIE 	7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

//SPSR의 비트 정의
#define SPIF    7 
#define WCOL    6
#define SPI2X   0

//EECR의 비트 정의
#define EERIE	3
#define EEMWE 	2
#define EEWE    1
#define EERE    0

//EEARH의 비트 정의
#define EEAR8	0

//TCCR2의 비트 정의
#define FOC2 	7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

//SREG의 비트 정의
#define I 	7
#define T       6
#define H       5
#define S       4
#define V       3
#define N       2
#define Z       1
#define C       0

//UBRR1H의 비트 정의
//#define URSEL1	7//L476 redefined warning

//UCSR1C의 비트 정의
#define URSEL1 	7	
#define UMSEL1 	6
#define UPM11  	5
#define UPM10  	4
#define USBS1  	3
#define UCSZ11 	2
#define UCSZ10 	1
#define UCPOL1 	0

//GICR의 비트 정의
#define INT1 	7
#define INT0    6
#define INT2    5
#define PCIE1   4
#define PCIE0   3
#define IVSEL   1
#define IVCE    0

//GIFR의 비트 정의
#define INTF1 	7
#define INTF0   6
#define INTF2   5
#define PCIF1   4
#define PCIF0   3

//TIMSK의 비트 정의
#define TOIE1 	7
#define OCIE1A  6 
#define OCIE1B  5 
#define OCIE2   4
#define TICIE1  3 
#define TOIE2   2
#define TOIE0   1
#define OCIE0   0

//TIFR 
#define TOV1 	7
#define OCF1A   6
#define OCF1B   5
#define OCF2    4
#define ICF1    3
#define TOV2    2
#define TOV0    1
#define OCF0    0
//SPMCR 
#define SPMIE 	7
#define RWWSB   6
#define RWWSRE  4
#define BLBSET  3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

//EMCUCR 
#define SM0 	7
#define SRL2    6
#define SRL1    5
#define SRL0    4
#define SRW01   3
#define SRW00   2
#define SRW11   1
#define ISC2    0

//MCUCR 
#define SRE 	7
#define SRW10   6
#define SE      5
#define SM1     4
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0
//MCUCSR 
#define JTD	7
#define SM2     5
#define JTRF    4
#define WDRF    3
#define BORF    2
#define EXTRF   1
#define PORF    0

//TCCR0 
#define FOC0 	7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

//SFIOR 
#define TSM 	7
#define XMBK    6
#define XMM2    5
#define XMM1    4
#define XMM0    3
#define PUD     2
#define PSR2    1
#define PSR310  0

//TCCR1A 
#define COM1A1 	7
#define COM1A0 	6
#define COM1B1 	5
#define COM1B0 	4
#define FOC1A  	3
#define FOC1B  	2
#define WGM11  	1
#define WGM10  	0

//TCCR1B 
#define ICNC1 	7
#define ICES1 	6
#define WGM13 	4
#define WGM12 	3
#define CS12  	2
#define CS11  	1
#define CS10  	0

//TCCR3A 
#define COM3A1 	7
#define COM3A0  6
#define COM3B1  5
#define COM3B0  4
#define FOC3A   3
#define FOC3B   2
#define WGM31   1
#define WGM30   0
//TCCR3B 
#define ICNC3 	7
#define ICES3   6
#define WGM33   4
#define WGM32   3
#define CS32    2
#define CS31    1
#define CS30    0

//ETIMSK 
#define TICIE3  5
#define OCIE3A  4
#define OCIE3B  3
#define TOIE3   2
//ETIFR 
#define ICF3    5
#define OCF3A   4
#define OCF3B   3
#define TOV3    2

//PCMSK1 
#define PCINT_15 7
#define PCINT_14 6
#define PCINT_13 5
#define PCINT_12 4
#define PCINT_11 3
#define PCINT_10 2
#define PCINT_9  1
#define PCINT_8  0

//PCMSK0 
#define PCINT_7 7
#define PCINT_6 6
#define PCINT_5 5
#define PCINT_4 4
#define PCINT_3 3
#define PCINT_2 2
#define PCINT_1 1
#define PCINT_0 0 

// UCSR0C
#define URSEL0 	7
#define UMSEL0   6
#define UPM01    5
#define UPM00    4
#define USBS0    3
#define UCSZ01   2
#define UCSZ00   1
#define UCPOL0   0

//ADMUX
#define REFS1	7
#define REFS0	6
#define ADLAR	5
#define MUX4	4
#define MUX3	3
#define MUX2	2
#define MUX1	1
#define MUX0	0

//ADCSRA
#define ADEN	7
#define ADSC	6
#define ADFR	5
#define ADIF	4
#define ADIE	3
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0

//TWCR
#define TWINT	7
#define TWEA	6
#define TWSTA	5
#define TWSTO	4
#define TWWC	3
#define TWEN	2
#define TWIE	0

//WDTCR
#define WDCE 	4
#define WDE	3
#define WDP2	2
#define WDP1	1
#define WDP0	0


// CLKPR 
#define CLKPCE 	7
#define CLKPS3  3
#define CLKPS2  2
#define CLKPS1  1
#define CLKPS0  0



// Needed by the power management functions (sleep.h)
#define __SLEEP_SUPPORTED__
#define __POWERDOWN_SUPPORTED__
#define __POWERSAVE_SUPPORTED__
#define __STANDBY_SUPPORTED__
#define __EXTENDED_STANDBY_SUPPORTED__
#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif
#endasm

#endif