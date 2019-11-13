#define s1_data  (!(PINF&0x02))
#define s2_data  (!(PINF&0x04))
#define s3_data  (!(PINF&0x08))
#define s4_data  (!(PINF&0x10))
#define s5_data  (!(PINF&0x20))
#define s6_data  (!(PINF&0x40))
#define s7_data  (!(PINF&0x80))
#define s8_data  (!(PINF&0x01))
#define s1 0x02
#define s2 0x04
#define s3 0x08
#define s4 0x10
#define s5 0x20
#define s6 0x40
#define s7 0x80
#define s8 0x01

#define ff 1
#define ss 2
#define ttl 3
#define ssl 4
#define ttr 5
#define ssr 6

#define IN1  1
#define IN2  2
#define IN3  3
#define IN4  4
#define IN5  5
#define IN6  6 
#define IN7  7
#define IN8  8
#define OUT1 9 
#define OUT2  10
#define OUT3  11
#define OUT4  12
#define OUT5  13
#define OUT6  14
#define OUT7  15
#define OUT8  16

volatile unsigned char init_buzzer_data=0;
volatile unsigned char init_sensor_data=0;
volatile unsigned int buzzer_on_time=0;
volatile unsigned int buzzer_on_count=0;
volatile unsigned int buzzer_off_time=0;
volatile unsigned int buzzer_off_count=0;
volatile unsigned int buzz_count=0;
volatile unsigned int buzz_time=0;
volatile unsigned int sec = 0;
volatile unsigned int count = 0;
volatile unsigned int randombox = 0;

ISR(TIMER2_OVF_vect)//1ms//
{
TCNT2=0x05;
sec++;

if(buzz_time>0)
{
  if(buzzer_on_count<buzzer_on_time){PORTD|=(1<<PD0);buzzer_on_count++;}
  else 
  {
    PORTD&=~(1<<PD0);
	if(buzzer_off_count<buzzer_off_time){buzzer_off_count++;}
	else{buzzer_on_count=0;buzzer_off_count=0;buzz_time--;}
  }
}

}


void start();
void end();
void delay(unsigned int sec_data);
void IO_set(unsigned int IO_data);
void delay(unsigned int sec_data);
void wait();
void init_sensor(unsigned char sens);
void buzzer_on();
void buzzer_off();
void buzzer(unsigned int on_time, unsigned int off_time, unsigned char buzzer_count);
void init_buzzer(unsigned char buzz);
void led_on();
void led_off();
void led(unsigned int on_time, unsigned int off_time, unsigned char led_count);

void start()
{
DDRA=0xFF; //DC모터제어//
DDRC=0xFF; //서보모터제어//
DDRE=0xFF; //"I/O핀"제어//
DDRF=0x00; //센서제어//
DDRD=0x01; //기타잡것들//
PORTA=0x00;
PORTD=0x00;
PORTC=0x00;
PORTE=0x00;

TCCR0 = (1<<CS00);
TCCR1B = (1<<CS11) | (1<<CS10);
TCCR2 = (1<<CS20) | (1<<CS21);

TCNT0 = 0x5F;
TCNT1H = 0xFF;
TCNT1L = 0x05;
TCNT2 = 0x05;
TIMSK = (1<<TOIE2) | (1<<TOIE1) | (1<<TOIE0);



sei();
buzzer(40,40,1);
delay(80);
buzzer(40,40,1);
}
void end()
{
PORTA=0x00;
PORTB=0x00;
PORTC=0x00;
PORTE=0x00;
TCCR0=0x00;
TCCR1B=0x00;
TCCR2=0x00;
TIMSK = 0x00;
cli();
}
void delay(unsigned int sec_data)
{
sec=0;
char while_end=0;
 while(1)
 {
  if(while_end==1) {break;}
  if(sec<sec_data) {while_end=0;}
  else if(sec>sec_data){while_end=1;}
 }
}
void IO_set(unsigned int IO_data)
{
  switch (IO_data)
  {
    case 1 : DDRE&=~0x01;
	case 2 : DDRE&=~0x02;
	case 3 : DDRE&=~0x04;
    case 4 : DDRE&=~0x08;
	case 5 : DDRE&=~0x10;
	case 6 : DDRE&=~0x20;
	case 7 : DDRE&=~0x40;
	case 8 : DDRE&=~0x80;
	case 9 : DDRE|=0x01;
	case 10 : DDRE|=0x02;
	case 11 : DDRE|=0x04;
    case 12 : DDRE|=0x08;
	case 13 : DDRE|=0x10;
	case 14 : DDRE|=0x20;
	case 15 : DDRE|=0x40;
	case 16 : DDRE|=0x80;
  }
}

void wait()
{ 
  delay(10);
  while(1)
  {
    if(!(PIND&0x02)){buzzer(50,1,1);break;}
	randombox++;
	delay(1);
  }
  while(1)
  {
    if(PIND&0x02){break;}
  }
  delay(50);
}

void init_sensor(unsigned char sens)
{
  if(sens==1){PORTD|=(1<<PD3);}
  else {PORTD&=~(1<<PD3);}
}

void buzzer_on(){PORTD|=(1<<PD0);}

void buzzer_off(){PORTD&=~(1<<PD0);}

void buzzer(unsigned int on_time, unsigned int off_time, unsigned char buzzer_count)
{
buzz_time=buzzer_count;
buzzer_on_time=on_time;
buzzer_off_time=buzzer_off_count;
}

void init_buzzer(unsigned char buzz)
{
  init_buzzer_data=buzz;
}

void led_on(){PORTD|=(1<<PD2);}

void led_off(){PORTD&=~(1<<PD2);}

void led(unsigned int on_time, unsigned int off_time, unsigned char led_count)
{
unsigned char led_current;
  for(led_current=0;led_current<=led_count;led_current++)
  {
	PORTD|=(1<<PD2);
	_delay_ms(on_time);
	PORTD&=~(1<<PD2);
	_delay_ms(off_time);
  }
}


