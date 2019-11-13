#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "atmega128.h"
#include "servo.h"
#include "motor.h"

#define turn_left exline(-9,40,s1,0);exline(-7,30,s2,0);exturn(0,30,s3,0);
#define turn_right exline(40,-9,s8,0);exline(30,-7,s7,0);exturn(30,0,s6,0);

int main(void)
{
  char lsen_data = 0;
  char rsen_data = 0;
  signed char ls = s1;
  signed char rs = s8; 
  unsigned char mt_sp = 30;
  unsigned char end_phase = 0;  
start();
init_buzzer(1);
motor(0,0,1);
wait();

driver(20,14,10,6,3,1);
hdriver(20,14,10,6,3,1);
ldriver(12,10,6,3,0,0);

///////////////////////
wait();
delay(300);
buzzer(400,400,1);
delay(800);
buzzer(400,400,1);
delay(800);
buzzer(400,400,1);
delay(800);
buzzer(700,500,1);
delay(1200);
linedelay(ff,10,50,0);
linedelay(ff,20,50,0);
go(0,ff,s1,s8,35,0);
if(randombox%5 == 0)
{
  go(0,ttl,0,s8,45,0);
  go(0,ttl,0,s8,45,0);
  linedelay(ttl,45,200,0);
  linedelay(ttl,45,200,0);
}
else if(randombox%5 ==1)
{
  go(0,ff,s1,s8,50,0);
  go(0,ttl,0,s8,45,0);
  go(0,ttl,0,s8,45,0);
  linedelay(ttl,45,100,0);
}
else if(randombox%5 ==2)
{
  go(0,ff,s1,0,50,0);
  go(0,ff,s1,0,50,0);
  linedelay(ff,45,100,0);
}
else if(randombox%5 ==3)
{
  go(0,ff,s1,s8,50,0);
  go(0,ttr,s1,0,45,0);
  go(0,ttr,s1,0,45,0);
  linedelay(ttr,45,100,0);
}
else
{
  go(0,ttr,s1,0,45,0);
  go(0,ttr,s1,0,45,0);
  linedelay(ttr,45,200,0);
  linedelay(ttr,45,200,0);
}

  while(1)
  {
    if(!(PINF&ls)) {lsen_data = 1;}
	if(!(PINF&rs)) {rsen_data = 1;}
	
	if(end_phase == 1) {break;}
	else if(lsen_data)
	{
		motor_speed(10,10);  
  		while(1)
  		{
			if((!(PINF&ls))==0) {break;}
			if(!(PINF&rs)) {end_phase = 1; break;}
		}
		if(end_phase ==0)
		{
      	  buzzer(20,1,init_buzzer_data);
	  	  turn_left;
	  	  go(0,ss,0,rs,mt_sp,0);
	 	  turn_right;
	  	  lsen_data = 0;
		}
	}
	else if(rsen_data)
	{
		motor_speed(10,10);  
  		while(1)
  		{
			if((!(PINF&rs))==0) {break;}
			if(!(PINF&ls)) {end_phase = 1; break;}
		}
		if(end_phase ==0)
		{
      	  buzzer(20,1,init_buzzer_data);
	  	  turn_right;
	  	  go(0,ss,ls,0,mt_sp,0);
	  	  turn_left;
	  	  rsen_data = 0;
		}
	}
	line_del(0,ff,mt_sp,1);
  }
motor(0,0,200);
buzzer(100,100,init_buzzer_data);
delay(200);
buzzer(100,100,1);
delay(200);

//////////////////////
motor(0,0,3000);
end();

return 0;
}
