volatile unsigned char angle_1 = 0;
volatile unsigned char angle_2 = 0;
volatile unsigned char angle_3 = 0;
volatile unsigned char angle_4 = 0;
volatile unsigned char angle_5 = 0;
volatile unsigned char angle_6 = 0;
volatile unsigned char angle_7 = 0;
volatile unsigned char angle_8 = 0;
volatile unsigned char sv_data[8];//center servo값//
volatile unsigned char svf_data[8];//목표서보값//
volatile unsigned char svo_data[8];//원래서보값//
volatile unsigned char svm_data[8];//변하는서보값//

ISR(TIMER0_OVF_vect)//0.01ms//
{

TCNT0=0x5F;

count++;

  //서보1,2제어//
  if(count<=200) 
  {
    if(count<=80) {PORTC=0x03;}
    else if(count>80) 
    {
	if(count>(angle_1+80)) {PORTC&=~0x01;}
	if(count>(angle_2+80)) {PORTC&=~0x02;}
	}
  }
  //서보3,4제어//
  else if(count<=400) 
  {
    if(count<=280) {PORTC=0x0C;}
    else if(count>280) 
    {
	if(count>(angle_3+280)) {PORTC&=~0x04;}
	if(count>(angle_4+280)) {PORTC&=~0x08;}
	}
  }
  //서보5,6제어//
  else if(count<=600) 
  {
    if(count<=480) {PORTC=0x30;}
    else if(count>480) 
    {
	if(count>(angle_5+480)) {PORTC&=~0x10;}
	if(count>(angle_6+480)) {PORTC&=~0x20;}
	}
  }
  //서보7,8제어//
  else if(count<=800) 
  {
    if(count<=680) {PORTC=0xC0;}
    else if(count>680) 
    {
	if(count>(angle_7+680)) {PORTC&=~0x40;}
	if(count>(angle_8+680)) {PORTC&=~0x80;}
	}
  }

  if(count>=2001) {count=0;}
}


void servo1(unsigned char ang);
void servo2(unsigned char ang);
void servo3(unsigned char ang);
void servo4(unsigned char ang);
void servo5(unsigned char ang);
void servo6(unsigned char ang);
void servo7(unsigned char ang);
void servo8(unsigned char ang);
void center_servo_set(unsigned char sv1, unsigned char sv2, unsigned char sv3, unsigned char sv4,unsigned char sv5,unsigned char sv6,unsigned char sv7,unsigned char sv8,unsigned int del);
void motion1_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8);
void motion2_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8);
void motion3_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8);
void motion4_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8);
void motion1(unsigned char sv_sp, unsigned int del);
void motion2(unsigned char sv_sp, unsigned int del);
void motion3(unsigned char sv_sp, unsigned int del);
void motion4(unsigned char sv_sp, unsigned int del);

void servo1(unsigned char ang)
{angle_1=ang;}
void servo2(unsigned char ang)
{angle_2=ang;}
void servo3(unsigned char ang)
{angle_3=ang;}
void servo4(unsigned char ang)
{angle_4=ang;}
void servo5(unsigned char ang)
{angle_5=ang;}
void servo6(unsigned char ang)
{angle_6=ang;}
void servo7(unsigned char ang)
{angle_7=ang;}
void servo8(unsigned char ang)
{angle_8=ang;}


void center_servo_set(unsigned char sv1, unsigned char sv2, unsigned char sv3, unsigned char sv4,unsigned char sv5,unsigned char sv6,unsigned char sv7,unsigned char sv8,unsigned int del)
{
sv_data[0]=s1;sv_data[1]=s2;sv_data[2]=s3;sv_data[3]=s4;sv_data[4]=s5;sv_data[5]=s6;sv_data[6]=s7;sv_data[7]=s8;
servo1(s1);servo2(s2);servo3(s3);servo4(s4);servo5(s5);servo6(s6);servo7(s7);servo8(s8);
svo_data[0]=s1;svo_data[1]=s2;svo_data[2]=s3;svo_data[3]=s4;svo_data[4]=s5;svo_data[5]=s6;svo_data[6]=s7;svo_data[7]=s8;
delay(del);
}
void motion1_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8)
{svf_data[0]=sv_data[0]+sv1;svf_data[1]=sv_data[1]+sv2;svf_data[2]=sv_data[2]+sv3;svf_data[3]=sv_data[3]+sv4;svf_data[4]=sv_data[4]+sv5;svf_data[5]=sv_data[5]+sv6;svf_data[6]=sv_data[6]+sv7;svf_data[7]=sv_data[7]+sv8;}
void motion2_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8)
{svf_data[0]=sv_data[0]+sv1;svf_data[1]=sv_data[1]+sv2;svf_data[2]=sv_data[2]+sv3;svf_data[3]=sv_data[3]+sv4;svf_data[4]=sv_data[4]+sv5;svf_data[5]=sv_data[5]+sv6;svf_data[6]=sv_data[6]+sv7;svf_data[7]=sv_data[7]+sv8;}
void motion3_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8)
{svf_data[0]=sv_data[0]+sv1;svf_data[1]=sv_data[1]+sv2;svf_data[2]=sv_data[2]+sv3;svf_data[3]=sv_data[3]+sv4;svf_data[4]=sv_data[4]+sv5;svf_data[5]=sv_data[5]+sv6;svf_data[6]=sv_data[6]+sv7;svf_data[7]=sv_data[7]+sv8;}
void motion4_set(char sv1, char sv2,char sv3,char sv4,char sv5,char sv6,char sv7,char sv8)
{svf_data[0]=sv_data[0]+sv1;svf_data[1]=sv_data[1]+sv2;svf_data[2]=sv_data[2]+sv3;svf_data[3]=sv_data[3]+sv4;svf_data[4]=sv_data[4]+sv5;svf_data[5]=sv_data[5]+sv6;svf_data[6]=sv_data[6]+sv7;svf_data[7]=sv_data[7]+sv8;}



void motion1(unsigned char sv_sp, unsigned int del)
{
  svm_data[0]=svo_data[0];
  svm_data[1]=svo_data[1];
  svm_data[2]=svo_data[2];
  svm_data[3]=svo_data[3];
  svm_data[4]=svo_data[4];
  svm_data[5]=svo_data[5];
  svm_data[6]=svo_data[6];
  svm_data[7]=svo_data[7];
  while(1)
  {	
    delay(sv_sp);

    if(svm_data[0]>svf_data[0]){svm_data[0]--;}
    else if(svm_data[0]<svf_data[0]){svm_data[0]++;}
	if(svm_data[1]>svf_data[1]){svm_data[1]--;}
    else if(svm_data[1]<svf_data[1]){svm_data[1]++;}
	if(svm_data[2]>svf_data[2]){svm_data[2]--;}
    else if(svm_data[2]<svf_data[2]){svm_data[2]++;}
	if(svm_data[3]>svf_data[3]){svm_data[3]--;}
    else if(svm_data[3]<svf_data[3]){svm_data[3]++;}
    if(svm_data[4]>svf_data[4]){svm_data[4]--;}
    else if(svm_data[4]<svf_data[4]){svm_data[4]++;}
	if(svm_data[5]>svf_data[5]){svm_data[5]--;}
    else if(svm_data[5]<svf_data[5]){svm_data[5]++;}
    if(svm_data[6]>svf_data[6]){svm_data[6]--;}
    else if(svm_data[6]<svf_data[6]){svm_data[6]++;}
	if(svm_data[7]>svf_data[7]){svm_data[7]--;}
    else if(svm_data[7]<svf_data[7]){svm_data[7]++;}
	servo1(svm_data[0]);
    servo2(svm_data[1]);
	servo3(svm_data[2]);
    servo4(svm_data[3]);
	servo5(svm_data[4]);
    servo6(svm_data[5]);
	servo7(svm_data[6]);
    servo8(svm_data[7]);
    if((svm_data[0]==svf_data[0])&&(svm_data[1]==svf_data[1])&&(svm_data[2]==svf_data[2])&&(svm_data[3]==svf_data[3])&&(svm_data[4]==svf_data[4])&&(svm_data[5]==svf_data[5])&&(svm_data[6]==svf_data[6])&&(svm_data[7]==svf_data[7])){break;}
  }
  delay(del);
  svo_data[0]=svf_data[0];
  svo_data[1]=svf_data[1];
  svo_data[2]=svf_data[2];
  svo_data[3]=svf_data[3];
  svo_data[4]=svf_data[4];
  svo_data[5]=svf_data[5];
  svo_data[6]=svf_data[6];
  svo_data[7]=svf_data[7];
}
void motion2(unsigned char sv_sp, unsigned int del)
{
    svm_data[0]=svo_data[0];
  svm_data[1]=svo_data[1];
  svm_data[2]=svo_data[2];
  svm_data[3]=svo_data[3];
  svm_data[4]=svo_data[4];
  svm_data[5]=svo_data[5];
  svm_data[6]=svo_data[6];
  svm_data[7]=svo_data[7];
  while(1)
  {	
    delay(sv_sp);

    if(svm_data[0]>svf_data[0]){svm_data[0]--;}
    else if(svm_data[0]<svf_data[0]){svm_data[0]++;}
	if(svm_data[1]>svf_data[1]){svm_data[1]--;}
    else if(svm_data[1]<svf_data[1]){svm_data[1]++;}
	if(svm_data[2]>svf_data[2]){svm_data[2]--;}
    else if(svm_data[2]<svf_data[2]){svm_data[2]++;}
	if(svm_data[3]>svf_data[3]){svm_data[3]--;}
    else if(svm_data[3]<svf_data[3]){svm_data[3]++;}
    if(svm_data[4]>svf_data[4]){svm_data[4]--;}
    else if(svm_data[4]<svf_data[4]){svm_data[4]++;}
	if(svm_data[5]>svf_data[5]){svm_data[5]--;}
    else if(svm_data[5]<svf_data[5]){svm_data[5]++;}
    if(svm_data[6]>svf_data[6]){svm_data[6]--;}
    else if(svm_data[6]<svf_data[6]){svm_data[6]++;}
	if(svm_data[7]>svf_data[7]){svm_data[7]--;}
    else if(svm_data[7]<svf_data[7]){svm_data[7]++;}
	servo1(svm_data[0]);
    servo2(svm_data[1]);
	servo3(svm_data[2]);
    servo4(svm_data[3]);
	servo5(svm_data[4]);
    servo6(svm_data[5]);
	servo7(svm_data[6]);
    servo8(svm_data[7]);
    if((svm_data[0]==svf_data[0])&&(svm_data[1]==svf_data[1])&&(svm_data[2]==svf_data[2])&&(svm_data[3]==svf_data[3])&&(svm_data[4]==svf_data[4])&&(svm_data[5]==svf_data[5])&&(svm_data[6]==svf_data[6])&&(svm_data[7]==svf_data[7])){break;}
  }
  delay(del);
  svo_data[0]=svf_data[0];
  svo_data[1]=svf_data[1];
  svo_data[2]=svf_data[2];
  svo_data[3]=svf_data[3];
  svo_data[4]=svf_data[4];
  svo_data[5]=svf_data[5];
  svo_data[6]=svf_data[6];
  svo_data[7]=svf_data[7];
}
void motion3(unsigned char sv_sp, unsigned int del)
{
    svm_data[0]=svo_data[0];
  svm_data[1]=svo_data[1];
  svm_data[2]=svo_data[2];
  svm_data[3]=svo_data[3];
  svm_data[4]=svo_data[4];
  svm_data[5]=svo_data[5];
  svm_data[6]=svo_data[6];
  svm_data[7]=svo_data[7];
  while(1)
  {	
    delay(sv_sp);

    if(svm_data[0]>svf_data[0]){svm_data[0]--;}
    else if(svm_data[0]<svf_data[0]){svm_data[0]++;}
	if(svm_data[1]>svf_data[1]){svm_data[1]--;}
    else if(svm_data[1]<svf_data[1]){svm_data[1]++;}
	if(svm_data[2]>svf_data[2]){svm_data[2]--;}
    else if(svm_data[2]<svf_data[2]){svm_data[2]++;}
	if(svm_data[3]>svf_data[3]){svm_data[3]--;}
    else if(svm_data[3]<svf_data[3]){svm_data[3]++;}
    if(svm_data[4]>svf_data[4]){svm_data[4]--;}
    else if(svm_data[4]<svf_data[4]){svm_data[4]++;}
	if(svm_data[5]>svf_data[5]){svm_data[5]--;}
    else if(svm_data[5]<svf_data[5]){svm_data[5]++;}
    if(svm_data[6]>svf_data[6]){svm_data[6]--;}
    else if(svm_data[6]<svf_data[6]){svm_data[6]++;}
	if(svm_data[7]>svf_data[7]){svm_data[7]--;}
    else if(svm_data[7]<svf_data[7]){svm_data[7]++;}
	servo1(svm_data[0]);
    servo2(svm_data[1]);
	servo3(svm_data[2]);
    servo4(svm_data[3]);
	servo5(svm_data[4]);
    servo6(svm_data[5]);
	servo7(svm_data[6]);
    servo8(svm_data[7]);
    if((svm_data[0]==svf_data[0])&&(svm_data[1]==svf_data[1])&&(svm_data[2]==svf_data[2])&&(svm_data[3]==svf_data[3])&&(svm_data[4]==svf_data[4])&&(svm_data[5]==svf_data[5])&&(svm_data[6]==svf_data[6])&&(svm_data[7]==svf_data[7])){break;}
  }
  delay(del);
  svo_data[0]=svf_data[0];
  svo_data[1]=svf_data[1];
  svo_data[2]=svf_data[2];
  svo_data[3]=svf_data[3];
  svo_data[4]=svf_data[4];
  svo_data[5]=svf_data[5];
  svo_data[6]=svf_data[6];
  svo_data[7]=svf_data[7];
}
void motion4(unsigned char sv_sp, unsigned int del)
{
    svm_data[0]=svo_data[0];
  svm_data[1]=svo_data[1];
  svm_data[2]=svo_data[2];
  svm_data[3]=svo_data[3];
  svm_data[4]=svo_data[4];
  svm_data[5]=svo_data[5];
  svm_data[6]=svo_data[6];
  svm_data[7]=svo_data[7];
  while(1)
  {	
    delay(sv_sp);

    if(svm_data[0]>svf_data[0]){svm_data[0]--;}
    else if(svm_data[0]<svf_data[0]){svm_data[0]++;}
	if(svm_data[1]>svf_data[1]){svm_data[1]--;}
    else if(svm_data[1]<svf_data[1]){svm_data[1]++;}
	if(svm_data[2]>svf_data[2]){svm_data[2]--;}
    else if(svm_data[2]<svf_data[2]){svm_data[2]++;}
	if(svm_data[3]>svf_data[3]){svm_data[3]--;}
    else if(svm_data[3]<svf_data[3]){svm_data[3]++;}
    if(svm_data[4]>svf_data[4]){svm_data[4]--;}
    else if(svm_data[4]<svf_data[4]){svm_data[4]++;}
	if(svm_data[5]>svf_data[5]){svm_data[5]--;}
    else if(svm_data[5]<svf_data[5]){svm_data[5]++;}
    if(svm_data[6]>svf_data[6]){svm_data[6]--;}
    else if(svm_data[6]<svf_data[6]){svm_data[6]++;}
	if(svm_data[7]>svf_data[7]){svm_data[7]--;}
    else if(svm_data[7]<svf_data[7]){svm_data[7]++;}
	servo1(svm_data[0]);
    servo2(svm_data[1]);
	servo3(svm_data[2]);
    servo4(svm_data[3]);
	servo5(svm_data[4]);
    servo6(svm_data[5]);
	servo7(svm_data[6]);
    servo8(svm_data[7]);
    if((svm_data[0]==svf_data[0])&&(svm_data[1]==svf_data[1])&&(svm_data[2]==svf_data[2])&&(svm_data[3]==svf_data[3])&&(svm_data[4]==svf_data[4])&&(svm_data[5]==svf_data[5])&&(svm_data[6]==svf_data[6])&&(svm_data[7]==svf_data[7])){break;}
  }
  delay(del);
  svo_data[0]=svf_data[0];
  svo_data[1]=svf_data[1];
  svo_data[2]=svf_data[2];
  svo_data[3]=svf_data[3];
  svo_data[4]=svf_data[4];
  svo_data[5]=svf_data[5];
  svo_data[6]=svf_data[6];
  svo_data[7]=svf_data[7];
}


