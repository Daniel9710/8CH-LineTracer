#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned int result_sum[8] = {0,0,0,0,0,0,0,0};
volatile unsigned char result[8] = {0,0,0,0,0,0,0,0};
volatile unsigned char adc_ave[8] = {0,0,0,0,0,0,0,0};
volatile unsigned char sens_temp[8]={0,0,0,0,0,0,0,0};
volatile unsigned int adc_max[8]={0,0,0,0,0,0,0,0};
volatile unsigned int adc_min[8]={250,250,250,250,250,250,250,250};
volatile unsigned char adc_result=0;
volatile unsigned char adc_result_1=0;
volatile unsigned char adc_result_2=0;
volatile unsigned char i=0;
volatile unsigned int number[5] ={0,0,0,0,0};
volatile unsigned int data =0;
volatile unsigned char adc_mode=0;
volatile unsigned char trash=0;
void ADC_read(unsigned char sen);
void ADC_solve();
void ADC_sensing(unsigned char sensor_num);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);
int main()
{
DDRB=0xFF;
DDRC=0xC3;
DDRD=0x17;
DDRA=0x00;

ADMUX = (0<<REFS1) | (0<<REFS0) |(0<ADLAR);
ADMUX |= 0x00;

ADCSRA = 0xA7;
ADCSRA |=0x40;

sei();
for(i=0;i<=7;i++)
{
adc_min[i]=EEPROM_read(i+1);
if(adc_min[i]>0xFF){adc_min[i]=220;}
adc_max[i]=EEPROM_read(i+9);
if(adc_max[i]>0xFF){adc_max[i]=220;}
}
while(1)
{
  while(1)
  {
    for(i=0;i<=7;i++)
    {
    ADC_read(i);
    }
    ADC_solve();
    PORTB=adc_result;
    PORTC=adc_result_1;
    PORTD=adc_result_2;
    _delay_ms(10);
    if(!(PIND&0x08)) {PORTC=0xC3;PORTD=0x17;break;}
  }
  PORTC=0x00;
  PORTD=0x00;
  _delay_ms(2500);
  adc_min[0]=250;
  adc_min[1]=250;
  adc_min[2]=250;
  adc_min[3]=250;
  adc_min[4]=250;
  adc_min[5]=250;
  adc_min[6]=250;
  adc_min[7]=250;
  adc_max[0]=0;
  adc_max[1]=0;
  adc_max[2]=0;
  adc_max[3]=0;
  adc_max[4]=0;
  adc_max[5]=0;
  adc_max[6]=0;
  adc_max[7]=0;
  while(1)
  {
    for(i=0;i<=7;i++)
	{
      ADC_sensing(i);
	  _delay_ms(100);
	}
    if(!(PIND&0x08)) {break;}
  }
  PORTC=0xC3;PORTD=0x17;
    PORTC=0x00;
  PORTD=0x00;
  for(i=1;i<=8;i++)
  {
    EEPROM_write(i,adc_min[i-1]);
	EEPROM_write(i+8,adc_max[i-1]);
  } 
  _delay_ms(2500);
  
}

////////////////
return 0;
}

void ADC_read(unsigned char sen)
{
  if(sen==0) {ADMUX=0x60;} else if(sen==1) {ADMUX=0x61;} else if(sen==2) {ADMUX=0x62;} else if(sen==3) {ADMUX=0x63;} else if(sen==4) {ADMUX=0x64;} else if(sen==5) {ADMUX=0x65;}else if(sen==6) {ADMUX=0x66;}else if(sen==7) {ADMUX=0x67;}

  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADSC);
  while((ADCSRA&0x10)==0);
  ADCSRA |=0x10;  
  trash = ADCL;
  result[sen] = ADCH;
}
void ADC_solve()
{ unsigned char abc;
  unsigned char j=0;
  unsigned char l=0;
  unsigned char k=0;
  unsigned char m=0;
  for(abc=0;abc<=7;abc++)
  {
  if(result[abc]>=((adc_min[abc]+adc_max[abc])/2)){sens_temp[abc]=0;}
  else {sens_temp[abc]=1;}
  }
  if(sens_temp[0]==1){j+=64;k+=1;}
  if(sens_temp[1]==1){j+=128;k+=128;}
  if(sens_temp[2]==1){j+=16;k+=64;}
  if(sens_temp[3]==1){j+=32;l+=1;}
  if(sens_temp[4]==1){j+=4;l+=2;}
  if(sens_temp[5]==1){j+=8;l+=4;}
  if(sens_temp[6]==1){j+=1;l+=16;}
  if(sens_temp[7]==1){j+=2;k+=2;}

  adc_result=j;
  adc_result_1=k;
  adc_result_2=l;
}
void ADC_sensing(unsigned char sensor_num)
{
  unsigned char num;
  PORTD=0x00;
  PORTC=0x00;
  if(sensor_num==0){PORTC=0x01;}
  if(sensor_num==1){PORTC=0x80;}
  if(sensor_num==2){PORTC=0x40;}
  if(sensor_num==3){PORTD=0x01;}
  if(sensor_num==4){PORTD=0x02;}
  if(sensor_num==5){PORTD=0x04;}
  if(sensor_num==6){PORTD=0x10;}
  if(sensor_num==7){PORTC=0x02;}
  
  for(num=0;num<=9;num++)
  {
    ADC_read(sensor_num);
	result_sum[sensor_num]+=result[sensor_num];
  }
  adc_ave[sensor_num] = result_sum[sensor_num] / 10;
  if(adc_ave[sensor_num]<adc_min[sensor_num]){adc_min[sensor_num]=adc_ave[sensor_num];}
  else if(adc_ave[sensor_num]>adc_max[sensor_num]){adc_max[sensor_num]=adc_ave[sensor_num];}
  result_sum[sensor_num] = 0;

}
void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
  while(EECR & (1<<EEWE));

  EEAR = uiAddress;
  EEDR = ucData;

  EECR |= (1<<EEMWE);
  EECR |= (1<<EEWE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
  while(EECR & (1<<EEWE));

  EEAR = uiAddress;

  EECR |= (1<<EERE);
 
  return EEDR;
}

