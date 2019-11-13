volatile unsigned int mt_count=0;
volatile signed int l_motor_speed=0;
volatile signed int r_motor_speed=0;
volatile unsigned char lm_dir=0;
volatile unsigned char rm_dir=0;
volatile unsigned char sp[3][22]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


ISR(TIMER1_OVF_vect)//1ms
{
TCNT1H=0xFF;
TCNT1L=0xE0;

    if(mt_count<=l_motor_speed)
	{ 
	  if(lm_dir==1){PORTA&=~0x04;PORTA|=0x03;}
	  else if(lm_dir==2){PORTA&=~0x01;PORTA|=0x06;}
	  else if(lm_dir==3){PORTA|=0x07;}
	}
	else {PORTA|=0x07;}

	if(mt_count<=r_motor_speed)
	{ 
	  if(rm_dir==1){PORTA&=~0x20;PORTA|=0x18;}
	  else if(rm_dir==2){PORTA&=~0x10;PORTA|=0x28;}
	  else if(rm_dir==3){PORTA|=0x38;}
	}
	else {PORTA|=0x38;}

  if(mt_count>50){mt_count=1;}
  else {mt_count++;}


}

void motor_speed(signed char lm, signed char rm);
void motor(signed char lm, signed char rm, unsigned int m_delay);
void exturn(signed char lm, signed char rm, unsigned char sen, unsigned int bk_delay);
void exline(signed char lm, signed char rm, unsigned char sen, unsigned int bk_delay);
void line_del(unsigned char dr_num, unsigned char sen_dr, unsigned char mt_sp,unsigned int m_delay);
void linedelay(unsigned char sen_dr, unsigned char sp,unsigned int m_delay,unsigned int ps_delay);
void go(unsigned int sp_delay,unsigned char sen_dr,signed char ls, signed char rs, unsigned char mt_sp, unsigned int ps_delay);

void driver(signed char dr45, signed char dr4_5, signed char dr34_56, signed char dr3_6, signed char dr2_7, signed char dr1_8);
void hdriver(signed char dr45, signed char dr4_5, signed char dr34_56, signed char dr3_6, signed char dr2_7, signed char dr1_8);
void ldriver(signed char dr45, signed char dr4_5, signed char dr34_56, signed char dr3_6, signed char dr2_7, signed char dr1_8);
void s_driver(signed char dr1, signed char dr2, signed char dr3, signed char dr34, signed char dr4, signed char dr45, signed char dr5, signed char dr56, signed char dr6, signed char dr7, signed char dr8);
void s_hdriver(signed char dr1, signed char dr2, signed char dr3, signed char dr34, signed char dr4, signed char dr45, signed char dr5, signed char dr56, signed char dr6, signed char dr7, signed char dr8);
void s_ldriver(signed char dr1, signed char dr2, signed char dr3, signed char dr34, signed char dr4, signed char dr45, signed char dr5, signed char dr56, signed char dr6, signed char dr7, signed char dr8);
void all_driver(signed char dr1_l,signed char dr1_r,signed char dr2_l,signed char dr2_r,signed char dr3_l,signed char dr3_r,signed char dr34_l,signed char dr34_r,signed char dr4_l,signed char dr4_r,signed char dr45_l,signed char dr45_r,signed char dr5_l,signed char dr5_r,signed char dr56_l,signed char dr56_r,signed char dr6_l,signed char dr6_r,signed char dr7_l,signed char dr7_r,signed char dr8_l,signed char dr8_r);
void all_hdriver(signed char dr1_l,signed char dr1_r,signed char dr2_l,signed char dr2_r,signed char dr3_l,signed char dr3_r,signed char dr34_l,signed char dr34_r,signed char dr4_l,signed char dr4_r,signed char dr45_l,signed char dr45_r,signed char dr5_l,signed char dr5_r,signed char dr56_l,signed char dr56_r,signed char dr6_l,signed char dr6_r,signed char dr7_l,signed char dr7_r,signed char dr8_l,signed char dr8_r);
void all_ldriver(signed char dr1_l,signed char dr1_r,signed char dr2_l,signed char dr2_r,signed char dr3_l,signed char dr3_r,signed char dr34_l,signed char dr34_r,signed char dr4_l,signed char dr4_r,signed char dr45_l,signed char dr45_r,signed char dr5_l,signed char dr5_r,signed char dr56_l,signed char dr56_r,signed char dr6_l,signed char dr6_r,signed char dr7_l,signed char dr7_r,signed char dr8_l,signed char dr8_r);


void motor_speed(signed char lm, signed char rm)
{
  l_motor_speed=lm;
  r_motor_speed=rm;

  if(l_motor_speed<0){l_motor_speed=l_motor_speed*(-1);lm_dir=1;}
  else if(l_motor_speed>0){lm_dir=2;}
  else {lm_dir=3;}

  if(r_motor_speed<0){r_motor_speed=r_motor_speed*(-1);rm_dir=1;}
  else if(r_motor_speed>0){rm_dir=2;}
  else {rm_dir=3;}

}
void motor(signed char lm, signed char rm, unsigned int m_delay)
{
  motor_speed(lm,rm);
  delay(m_delay);
}

void exturn(signed char lm, signed char rm, unsigned char sen, unsigned int bk_delay)
{
  motor_speed(lm,rm);  
  while(1)
  {
    if(!(PINF&sen)) {break;}
  }
  if(bk_delay>0){motor(-lm,-rm,bk_delay);}
  buzzer(20,1,init_buzzer_data);
}
void exline(signed char lm, signed char rm, unsigned char sen, unsigned int bk_delay)
{
  motor_speed(lm,rm);  
  while(1)
  {
	if(!(PINF&sen)) {break;}
  }
  while(1)
  {
	if((!(PINF&sen))==0) {break;}
  }
  if(bk_delay>0){motor(-lm,-rm,bk_delay);}
  buzzer(20,1,init_buzzer_data);
}

void line_del(unsigned char dr_num, unsigned char sen_dr, unsigned char mt_sp,unsigned int m_delay)
{
unsigned char i=0;
unsigned int delcount=1;
i=dr_num;
  if(sen_dr<=2)
  { 
    while(delcount<=m_delay)
    {
      if(s4_data&&s5_data){motor_speed(sp[i][10]*mt_sp/20,sp[i][11]*mt_sp/20);}
	  else if(s4_data) {motor_speed(sp[i][8]*mt_sp/20,sp[i][9]*mt_sp/20);}
	  else if(s5_data) {motor_speed(sp[i][12]*mt_sp/20,sp[i][13]*mt_sp/20);}
	  else if(s3_data&&s4_data) {motor_speed(sp[i][6]*mt_sp/20,sp[i][7]*mt_sp/20);}
	  else if(s5_data&&s6_data) {motor_speed(sp[i][14]*mt_sp/20,sp[i][15]*mt_sp/20);}
	  else if(s3_data) {motor_speed(sp[i][4]*mt_sp/20,sp[i][5]*mt_sp/20);}
	  else if(s6_data) {motor_speed(sp[i][16]*mt_sp/20,sp[i][17]*mt_sp/20);}
	  else if(s2_data) {motor_speed(sp[i][2]*mt_sp/20,sp[i][3]*mt_sp/20);}
	  else if(s7_data) {motor_speed(sp[i][18]*mt_sp/20,sp[i][19]*mt_sp/20);}
	  else if(s1_data) {motor_speed(sp[i][0]*mt_sp/20,sp[i][1]*mt_sp/20);}
	  else if(s8_data) {motor_speed(sp[i][20]*mt_sp/20,sp[i][21]*mt_sp/20);}
	  delay(1);
	  delcount++;
	}
  }
  else if((sen_dr>=3)&&(sen_dr<=4))
  {	
    while(delcount<=m_delay)
	{
      if(s1_data) {motor_speed(sp[i][0]*mt_sp/20,sp[i][1]*mt_sp/20);}
	  else if(s2_data) {motor_speed(sp[i][2]*mt_sp/20,sp[i][3]*mt_sp/20);}
      else if(s3_data) {motor_speed(sp[i][4]*mt_sp/20,sp[i][5]*mt_sp/20);}
	  else if(s3_data&&s4_data) {motor_speed(sp[i][6]*mt_sp/20,sp[i][7]*mt_sp/20);}
	  else if(s4_data) {motor_speed(sp[i][8]*mt_sp/20,sp[i][9]*mt_sp/20);}	  
	  else if(s4_data&&s5_data){motor_speed(sp[i][10]*mt_sp/20,sp[i][11]*mt_sp/20);}
	  else if(s5_data) {motor_speed(sp[i][12]*mt_sp/20,sp[i][13]*mt_sp/20);}
	  else if(s5_data&&s6_data) {motor_speed(sp[i][14]*mt_sp/20,sp[i][15]*mt_sp/20);}
	  else if(s6_data) {motor_speed(sp[i][16]*mt_sp/20,sp[i][17]*mt_sp/20);}
	  else if(s7_data) {motor_speed(sp[i][18]*mt_sp/20,sp[i][19]*mt_sp/20);}
	  else if(s8_data) {motor_speed(sp[i][20]*mt_sp/20,sp[i][21]*mt_sp/20);}
      delay(1);
	  delcount++;
	  }
  }
  else if((sen_dr>=5)&&(sen_dr<=6))
  { 
    while(delcount<=m_delay)
	{
	  if(s8_data) {motor_speed(sp[i][20]*mt_sp/20,sp[i][21]*mt_sp/20);}      
	  else if(s7_data) {motor_speed(sp[i][18]*mt_sp/20,sp[i][19]*mt_sp/20);}	  
	  else if(s6_data) {motor_speed(sp[i][16]*mt_sp/20,sp[i][17]*mt_sp/20);}
	  else if(s5_data&&s6_data) {motor_speed(sp[i][14]*mt_sp/20,sp[i][15]*mt_sp/20);}	
	  else if(s5_data) {motor_speed(sp[i][12]*mt_sp/20,sp[i][13]*mt_sp/20);}	  
	  else if(s4_data&&s5_data){motor_speed(sp[i][10]*mt_sp/20,sp[i][11]*mt_sp/20);}	  
	  else if(s4_data) {motor_speed(sp[i][8]*mt_sp/20,sp[i][9]*mt_sp/20);}	 	  
	  else if(s3_data&&s4_data) {motor_speed(sp[i][6]*mt_sp/20,sp[i][7]*mt_sp/20);}	  
      else if(s3_data) {motor_speed(sp[i][4]*mt_sp/20,sp[i][5]*mt_sp/20);}
	  else if(s2_data) {motor_speed(sp[i][2]*mt_sp/20,sp[i][3]*mt_sp/20);}
	  else if(s1_data) {motor_speed(sp[i][0]*mt_sp/20,sp[i][1]*mt_sp/20);}
      delay(1);
	  delcount++;
	} 
  }
}

void linedelay(unsigned char sen_dr, unsigned char mt_sp,unsigned int m_delay,unsigned int ps_delay)
{
line_del(0,sen_dr,mt_sp,m_delay);
  if(ps_delay>0){motor(mt_sp,mt_sp,ps_delay);}

}
void go(unsigned int sp_delay, unsigned char sen_dr, signed char ls, signed char rs, unsigned char mt_sp,unsigned int ps_delay)
{
unsigned char sen_data=0;
unsigned int sp_count=0;
unsigned char lsen_data=0;
unsigned char rsen_data=0;

if(sp_delay==0)
{
  while(sen_data==0)
  {
    if(((!(PINF&ls)))||(ls==0)) {lsen_data=1;}
	if(((!(PINF&rs)))||(rs==0)) {rsen_data=1;}
    if((lsen_data==1)&&(rsen_data==1)){if((sen_dr%2)==1){sen_data=1;}else {sen_data=2;}}
	line_del(0,sen_dr,mt_sp,1);
  }
  lsen_data=0;
  rsen_data=0;
  while(sen_data==1)
  {	
    if(((!(PINF&ls))==0)||(ls==0)) {lsen_data=1;}
	if(((!(PINF&rs))==0)||(rs==0)) {rsen_data=1;}
	if((lsen_data==1)&&(rsen_data==1)){if((sen_dr%2)==1){sen_data=2;}}
	line_del(0,sen_dr,mt_sp,1);
  }
}
else 
{
  while((sp_count<=sp_delay)&&(sen_data==0))
  { 
    if(((!(PINF&ls)))||(ls==0)) {lsen_data=1;}
	if(((!(PINF&rs)))||(rs==0)) {rsen_data=1;}
    if((lsen_data==1)&&(rsen_data==1)){if((sen_dr%2)==1){sen_data=1;}else {sen_data=4;}}
	line_del(1,sen_dr,mt_sp,1);
	if(sp_count>=sp_delay){sen_data=2;}
	else {sp_count++;}
  }
  lsen_data=0;
  rsen_data=0;
  while(sen_data==1)
  {
    if(((!(PINF&ls))==0)||(ls==0)) {lsen_data=1;}
	if(((!(PINF&rs))==0)||(rs==0)) {rsen_data=1;}
    if((lsen_data==1)&&(rsen_data==1)){sen_data=4;break;}	
    
	if(sp_count<=sp_delay){line_del(1,sen_dr,mt_sp,1);sp_count++;}
	else{line_del(2,sen_dr,mt_sp,1);}
  }
  lsen_data=0;
  rsen_data=0;
  while(sen_data==2)
  {  
    if(((!(PINF&ls)))||(ls==0)) {lsen_data=1;}
	if(((!(PINF&rs)))||(rs==0)) {rsen_data=1;}	 
    if((lsen_data==1)&&(rsen_data==1)){if((sen_dr%2)==1){sen_data=3;}else{sen_data=4;}}
  	line_del(2,sen_dr,mt_sp,1);
  }
  lsen_data=0;
  rsen_data=0;
  while(sen_data==3)
  {
    if(((!(PINF&ls))==0)||(ls==0)) {lsen_data=1;}
	if(((!(PINF&rs))==0)||(rs==0)) {rsen_data=1;}
	if((lsen_data==1)&&(rsen_data==1)){sen_data=4;}
  	line_del(2,sen_dr,mt_sp,1);
  }
}
buzzer(20,1,init_buzzer_data);
}


void driver(signed char dr45, signed char dr4_5, signed char dr34_56, signed char dr3_6, signed char dr2_7, signed char dr1_8)
{
  s_driver(dr1_8,dr2_7,dr3_6,dr34_56,dr4_5,dr45,dr4_5,dr34_56,dr3_6,dr2_7,dr1_8);
}
void hdriver(signed char dr45, signed char dr4_5, signed char dr34_56, signed char dr3_6, signed char dr2_7, signed char dr1_8)
{
  s_hdriver(dr1_8,dr2_7,dr3_6,dr34_56,dr4_5,dr45,dr4_5,dr34_56,dr3_6,dr2_7,dr1_8);
}
void ldriver(signed char dr45, signed char dr4_5, signed char dr34_56, signed char dr3_6, signed char dr2_7, signed char dr1_8)
{
  s_ldriver(dr1_8,dr2_7,dr3_6,dr34_56,dr4_5,dr45,dr4_5,dr34_56,dr3_6,dr2_7,dr1_8);
}
void s_driver(signed char dr1, signed char dr2, signed char dr3, signed char dr34, signed char dr4, signed char dr45, signed char dr5, signed char dr56, signed char dr6, signed char dr7, signed char dr8)
{
  if(dr45>dr4)
  {
    if(dr5>dr45)
	{
	  if(dr56>dr5)
	  {
		if(dr6>dr56)
		{
		  if(dr7>dr6)
		  {
		    if(dr8>dr7) {all_driver(dr1,dr8,dr2,dr8,dr3,dr8,dr34,dr8,dr4,dr8,dr45,dr8,dr5,dr8,dr56,dr8,dr6,dr8,dr7,dr8,dr8,dr8);}
			else {all_driver(dr1,dr7,dr2,dr7,dr3,dr7,dr34,dr7,dr4,dr7,dr45,dr7,dr5,dr7,dr56,dr7,dr6,dr7,dr7,dr7,dr7,dr8);}
		  }
		  else {all_driver(dr1,dr6,dr2,dr6,dr3,dr6,dr34,dr6,dr4,dr6,dr45,dr6,dr5,dr6,dr56,dr6,dr6,dr6,dr6,dr7,dr6,dr8);}
        }  
		else {all_driver(dr1,dr56,dr2,dr56,dr3,dr56,dr34,dr56,dr4,dr56,dr45,dr56,dr5,dr56,dr56,dr56,dr56,dr6,dr56,dr7,dr56,dr8);}
	  }
	  else {all_driver(dr1,dr5,dr2,dr5,dr3,dr5,dr34,dr5,dr4,dr5,dr45,dr5,dr5,dr5,dr5,dr56,dr5,dr6,dr5,dr7,dr5,dr8);}
	}
	else {all_driver(dr1,dr45,dr2,dr45,dr3,dr45,dr34,dr45,dr4,dr45,dr45,dr45,dr45,dr5,dr45,dr56,dr45,dr6,dr45,dr7,dr45,dr8);}
  }
  else if(dr45<=dr4)
  {
    if(dr4<dr34)
	{
	  if(dr34<dr3)
	  {
	    if(dr3<dr2)
		{
		  if(dr2<dr1) {all_driver(dr1,dr1,dr1,dr2,dr1,dr3,dr1,dr34,dr1,dr4,dr1,dr45,dr1,dr5,dr1,dr56,dr1,dr6,dr1,dr7,dr1,dr8);}
		  else {all_driver(dr1,dr2,dr2,dr2,dr2,dr3,dr2,dr34,dr2,dr4,dr2,dr45,dr2,dr5,dr2,dr56,dr2,dr6,dr2,dr7,dr2,dr8);}
		}
		else {all_driver(dr1,dr3,dr2,dr3,dr3,dr3,dr3,dr34,dr3,dr4,dr3,dr45,dr3,dr5,dr3,dr56,dr3,dr6,dr3,dr7,dr3,dr8);}
	  }
	  else {all_driver(dr1,dr34,dr2,dr34,dr3,dr34,dr34,dr34,dr34,dr4,dr34,dr45,dr34,dr5,dr34,dr56,dr34,dr6,dr34,dr7,dr34,dr8);}
	}
	else{all_driver(dr1,dr4,dr2,dr4,dr3,dr4,dr34,dr4,dr4,dr4,dr4,dr45,dr4,dr5,dr4,dr56,dr4,dr6,dr4,dr7,dr4,dr8);}
  }

}
void s_hdriver(signed char dr1, signed char dr2, signed char dr3, signed char dr34, signed char dr4, signed char dr45, signed char dr5, signed char dr56, signed char dr6, signed char dr7, signed char dr8)
{
  if(dr45>dr4)
  {
    if(dr5>dr45)
	{
	  if(dr56>dr5)
	  {
		if(dr6>dr56)
		{
		  if(dr7>dr6)
		  {
		    if(dr8>dr7) {all_hdriver(dr1,dr8,dr2,dr8,dr3,dr8,dr34,dr8,dr4,dr8,dr45,dr8,dr5,dr8,dr56,dr8,dr6,dr8,dr7,dr8,dr8,dr8);}
			else {all_hdriver(dr1,dr7,dr2,dr7,dr3,dr7,dr34,dr7,dr4,dr7,dr45,dr7,dr5,dr7,dr56,dr7,dr6,dr7,dr7,dr7,dr7,dr8);}
		  }
		  else {all_hdriver(dr1,dr6,dr2,dr6,dr3,dr6,dr34,dr6,dr4,dr6,dr45,dr6,dr5,dr6,dr56,dr6,dr6,dr6,dr6,dr7,dr6,dr8);}
        }  
		else {all_hdriver(dr1,dr56,dr2,dr56,dr3,dr56,dr34,dr56,dr4,dr56,dr45,dr56,dr5,dr56,dr56,dr56,dr56,dr6,dr56,dr7,dr56,dr8);}
	  }
	  else {all_hdriver(dr1,dr5,dr2,dr5,dr3,dr5,dr34,dr5,dr4,dr5,dr45,dr5,dr5,dr5,dr5,dr56,dr5,dr6,dr5,dr7,dr5,dr8);}
	}
	else {all_hdriver(dr1,dr45,dr2,dr45,dr3,dr45,dr34,dr45,dr4,dr45,dr45,dr45,dr45,dr5,dr45,dr56,dr45,dr6,dr45,dr7,dr45,dr8);}
  }
  else if(dr45<dr4)
  {
    if(dr4<dr34)
	{
	  if(dr34<dr3)
	  {
	    if(dr3<dr2)
		{
		  if(dr2<dr1) {all_hdriver(dr1,dr1,dr1,dr2,dr1,dr3,dr1,dr34,dr1,dr4,dr1,dr45,dr1,dr5,dr1,dr56,dr1,dr6,dr1,dr7,dr1,dr8);}
		  else {all_hdriver(dr1,dr2,dr2,dr2,dr2,dr3,dr2,dr34,dr2,dr4,dr2,dr45,dr2,dr5,dr2,dr56,dr2,dr6,dr2,dr7,dr2,dr8);}
		}
		else {all_hdriver(dr1,dr3,dr2,dr3,dr3,dr3,dr3,dr34,dr3,dr4,dr3,dr45,dr3,dr5,dr3,dr56,dr3,dr6,dr3,dr7,dr3,dr8);}
	  }
	  else {all_hdriver(dr1,dr34,dr2,dr34,dr3,dr34,dr34,dr34,dr34,dr4,dr34,dr45,dr34,dr5,dr34,dr56,dr34,dr6,dr34,dr7,dr34,dr8);}
	}
	else{all_hdriver(dr1,dr4,dr2,dr4,dr3,dr4,dr34,dr4,dr4,dr4,dr4,dr45,dr4,dr5,dr4,dr56,dr4,dr6,dr4,dr7,dr4,dr8);}
  }

}
void s_ldriver(signed char dr1, signed char dr2, signed char dr3, signed char dr34, signed char dr4, signed char dr45, signed char dr5, signed char dr56, signed char dr6, signed char dr7, signed char dr8)
{
  if(dr45>dr4)
  {
    if(dr5>dr45)
	{
	  if(dr56>dr5)
	  {
		if(dr6>dr56)
		{
		  if(dr7>dr6)
		  {
		    if(dr8>dr7) {all_ldriver(dr1,dr8,dr2,dr8,dr3,dr8,dr34,dr8,dr4,dr8,dr45,dr8,dr5,dr8,dr56,dr8,dr6,dr8,dr7,dr8,dr8,dr8);}
			else {all_ldriver(dr1,dr7,dr2,dr7,dr3,dr7,dr34,dr7,dr4,dr7,dr45,dr7,dr5,dr7,dr56,dr7,dr6,dr7,dr7,dr7,dr7,dr8);}
		  }
		  else {all_ldriver(dr1,dr6,dr2,dr6,dr3,dr6,dr34,dr6,dr4,dr6,dr45,dr6,dr5,dr6,dr56,dr6,dr6,dr6,dr6,dr7,dr6,dr8);}
        }  
		else {all_ldriver(dr1,dr56,dr2,dr56,dr3,dr56,dr34,dr56,dr4,dr56,dr45,dr56,dr5,dr56,dr56,dr56,dr56,dr6,dr56,dr7,dr56,dr8);}
	  }
	  else {all_ldriver(dr1,dr5,dr2,dr5,dr3,dr5,dr34,dr5,dr4,dr5,dr45,dr5,dr5,dr5,dr5,dr56,dr5,dr6,dr5,dr7,dr5,dr8);}
	}
	else {all_ldriver(dr1,dr45,dr2,dr45,dr3,dr45,dr34,dr45,dr4,dr45,dr45,dr45,dr45,dr5,dr45,dr56,dr45,dr6,dr45,dr7,dr45,dr8);}
  }
  else if(dr45<dr4)
  {
    if(dr4<dr34)
	{
	  if(dr34<dr3)
	  {
	    if(dr3<dr2)
		{
		  if(dr2<dr1) {all_ldriver(dr1,dr1,dr1,dr2,dr1,dr3,dr1,dr34,dr1,dr4,dr1,dr45,dr1,dr5,dr1,dr56,dr1,dr6,dr1,dr7,dr1,dr8);}
		  else {all_ldriver(dr1,dr2,dr2,dr2,dr2,dr3,dr2,dr34,dr2,dr4,dr2,dr45,dr2,dr5,dr2,dr56,dr2,dr6,dr2,dr7,dr2,dr8);}
		}
		else {all_ldriver(dr1,dr3,dr2,dr3,dr3,dr3,dr3,dr34,dr3,dr4,dr3,dr45,dr3,dr5,dr3,dr56,dr3,dr6,dr3,dr7,dr3,dr8);}
	  }
	  else {all_ldriver(dr1,dr34,dr2,dr34,dr3,dr34,dr34,dr34,dr34,dr4,dr34,dr45,dr34,dr5,dr34,dr56,dr34,dr6,dr34,dr7,dr34,dr8);}
	}
	else{all_ldriver(dr1,dr4,dr2,dr4,dr3,dr4,dr34,dr4,dr4,dr4,dr4,dr45,dr4,dr5,dr4,dr56,dr4,dr6,dr4,dr7,dr4,dr8);}
  }

}
void all_driver(signed char dr1_l,signed char dr1_r,signed char dr2_l,signed char dr2_r,signed char dr3_l,signed char dr3_r,signed char dr34_l,signed char dr34_r,signed char dr4_l,signed char dr4_r,signed char dr45_l,signed char dr45_r,signed char dr5_l,signed char dr5_r,signed char dr56_l,signed char dr56_r,signed char dr6_l,signed char dr6_r,signed char dr7_l,signed char dr7_r,signed char dr8_l,signed char dr8_r)
{
  sp[0][0]=dr1_l;
  sp[0][1]=dr1_r;
  sp[0][2]=dr2_l;
  sp[0][3]=dr2_r;
  sp[0][4]=dr3_l;
  sp[0][5]=dr3_r;
  sp[0][6]=dr34_l;
  sp[0][7]=dr34_r;
  sp[0][8]=dr4_l;
  sp[0][9]=dr4_r;
  sp[0][10]=dr45_l;
  sp[0][11]=dr45_r;
  sp[0][12]=dr5_l;
  sp[0][13]=dr5_r;
  sp[0][14]=dr56_l;
  sp[0][15]=dr56_r;
  sp[0][16]=dr6_l;
  sp[0][17]=dr6_r;
  sp[0][18]=dr7_l;
  sp[0][19]=dr7_r;
  sp[0][20]=dr8_l;
  sp[0][21]=dr8_r;
}
void all_hdriver(signed char dr1_l,signed char dr1_r,signed char dr2_l,signed char dr2_r,signed char dr3_l,signed char dr3_r,signed char dr34_l,signed char dr34_r,signed char dr4_l,signed char dr4_r,signed char dr45_l,signed char dr45_r,signed char dr5_l,signed char dr5_r,signed char dr56_l,signed char dr56_r,signed char dr6_l,signed char dr6_r,signed char dr7_l,signed char dr7_r,signed char dr8_l,signed char dr8_r)
{
  sp[1][0]=dr1_l;
  sp[1][1]=dr1_r;
  sp[1][2]=dr2_l;
  sp[1][3]=dr2_r;
  sp[1][4]=dr3_l;
  sp[1][5]=dr3_r;
  sp[1][6]=dr34_l;
  sp[1][7]=dr34_r;
  sp[1][8]=dr4_l;
  sp[1][9]=dr4_r;
  sp[1][10]=dr45_l;
  sp[1][11]=dr45_r;
  sp[1][12]=dr5_l;
  sp[1][13]=dr5_r;
  sp[1][14]=dr56_l;
  sp[1][15]=dr56_r;
  sp[1][16]=dr6_l;
  sp[1][17]=dr6_r;
  sp[1][18]=dr7_l;
  sp[1][19]=dr7_r;
  sp[1][20]=dr8_l;
  sp[1][21]=dr8_r;
}
void all_ldriver(signed char dr1_l,signed char dr1_r,signed char dr2_l,signed char dr2_r,signed char dr3_l,signed char dr3_r,signed char dr34_l,signed char dr34_r,signed char dr4_l,signed char dr4_r,signed char dr45_l,signed char dr45_r,signed char dr5_l,signed char dr5_r,signed char dr56_l,signed char dr56_r,signed char dr6_l,signed char dr6_r,signed char dr7_l,signed char dr7_r,signed char dr8_l,signed char dr8_r)
{
  sp[2][0]=dr1_l;
  sp[2][1]=dr1_r;
  sp[2][2]=dr2_l;
  sp[2][3]=dr2_r;
  sp[2][4]=dr3_l;
  sp[2][5]=dr3_r;
  sp[2][6]=dr34_l;
  sp[2][7]=dr34_r;
  sp[2][8]=dr4_l;
  sp[2][9]=dr4_r;
  sp[2][10]=dr45_l;
  sp[2][11]=dr45_r;
  sp[2][12]=dr5_l;
  sp[2][13]=dr5_r;
  sp[2][14]=dr56_l;
  sp[2][15]=dr56_r;
  sp[2][16]=dr6_l;
  sp[2][17]=dr6_r;
  sp[2][18]=dr7_l;
  sp[2][19]=dr7_r;
  sp[2][20]=dr8_l;
  sp[2][21]=dr8_r;
}


