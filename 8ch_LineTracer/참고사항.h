/*

//PORTA = DC motors
*output :
PA1 l_motor_enable
PA2 l_motor_forward
PA3 l_motor_backward
PA4 r_motor_enable
PA5 r_motor_forward
PA6 r_motor_backward
 

//PORTC = SERVO motors
*output :
PC1 servo 1
PC2 servo 2
PC3 servo 3
PC4 servo 4
PC5 servo 5
PC6 servo 6
PC7 servo 7
PC8 servo 8

//PORTE = I/o port
PE1 i/o 1
PE2 i/o 2
PE3 i/o 3
PE4 i/o 4
PE5 i/o 5
PE6 i/o 6
PE7 i/o 7
PE8 i/o 8

//PORTF = sensors
*input : 
PF1  sen 1
PF2  sen 2
PF3  sen 3
PF4  sen 4
PF5  sen 5
PF6  sen 6
PF7  sen 7
PF8  sen 8

//PORTD = etc
*output :
PD1 buzzer
PD2 leds
PD3 sens_power

*input : 
PE5 start button
*/
/*
//DC motor �Լ�
Timer/Counter 1 ���
motor_off() : ������ ���� Ǫ�� �Լ�(��� �����Լ��� ���������)
motor_speed(�޼�,����) : ������ �ӵ��� ȸ�������� �����ϴ� �������� �ٲٴ� �Լ�
motor(�޼�,����,�ð�) : motor_speed�Լ��� �ð����� ���ӽð����� ���� �Լ�
exturn(�޼�,����,������ȣ,�극��ũ�ð�) : ������ȣ�� ���� ������ ���� �����Ҷ����� �����̴� �Լ�
exline(�޼�,����,������ȣ,�극��ũ�ð�) : ������ȣ�� ���� ������ ���� ���� �� ������������ �����̴� �Լ�
driver(45��,4_5��,34_56��,3_6��,2_7��,1_8��) : �Լ��� ���� ������ s_driver�Լ��� �����ϴ� �Լ�
hdriver(45��,4_5��,34_56��,3_6��,2_7��,1_8��) : �Լ��� ���� ������ s_hdriver�Լ��� �����ϴ� �Լ�
ldriver(45��,4_5��,34_56��,3_6��,2_7��,1_8��) : �Լ��� ���� ������ s_ldriver�Լ��� �����ϴ� �Լ�
s_driver(1��,2��,3��,34��,4��,45��,5��,56��,6��,7��,8��) : �Լ��� ���������� �񱳰�� �� all_driver�Լ��� �����ϴ� �Լ�
s_hdriver(1��,2��,3��,34��,4��,45��,5��,56��,6��,7��,8��) : �Լ��� ���������� �񱳰�� �� all_hdriver�Լ��� �����ϴ� �Լ�
s_ldriver(1��,2��,3��,34��,4��,45��,5��,56��,6��,7��,8��) : �Լ��� ���������� �񱳰�� �� all_ldriver�Լ��� �����ϴ� �Լ�
all_driver(1����,1����,2����,2����,3����,3����,34����,34����,4����,4����,45����,45����,5����,5����,56����,56����,6����,6����,7����,7����,8����,8����) : �Լ��� ���� ������ sp[0][n]������ �����ϴ� �Լ�
all_hdriver(1����,1����,2����,2����,3����,3����,34����,34����,4����,4����,45����,45����,5����,5����,56����,56����,6����,6����,7����,7����,8����,8����) : �Լ��� ���� ������ sp[1][n]������ �����ϴ� �Լ�
all_ldriver(1����,1����,2����,2����,3����,3����,34����,34����,4����,4����,45����,45����,5����,5����,56����,56����,6����,6����,7����,7����,8����,8����) : �Լ��� ���� ������ sp[2][n]������ �����ϴ� �Լ�
line_del(����̹�������,
//SERVO motor �Լ�
Timer/Counter0 ���

//��Ÿ �Լ�
Timer/Counter2 ��� 
start() : ���α׷��� �����ϱ��� ��� �⺻ �������� �� ��� �ִ� �Լ�
delay(���ӽð�) : ���ӽð� �Լ� 
wait() : startbutton�� ������ �Ѿ
init_sensor(����on/off) : sensor�� on/off�ϴ� �Լ�
buzzer_on() : ������ on�ϴ� �Լ�
buzzer_off() : ������ off�ϴ� �Լ�
buzzer(on�ð�,off�ð�,Ƚ��) : ������ on/off�� �ϴ� Ƚ������ ���ϴ� �Լ�
init_buzzer(����on/off) : ������ ���� ���������� ������ on/off���� �����ϴ� �Լ�
led_on() : led�� on�ϴ� �Լ�
led_off() : led�� off�ϴ� �Լ� 
led(on�ð�,off�ð�,Ƚ��) : led�� on/off�� �ϴ� Ƚ������ ���ϴ� �Լ�

*/

/*
//DC motor ����

* ���� ���� 
  mt_count : Timer/Count1�� PWM����
  l_motor_speed : mt_count�� ���Ͽ� lmotor enable�� on/off�ϴ� ����
  r_motor_speed : mt_count�� ���Ͽ� rmotor enable�� on/off�ϴ� ����
  lm_dir : lmotor�� ȸ�� ������ ��Ÿ���� ����
  rm_dir : rmotor�� ȸ�� ������ ��Ÿ���� ����

* motor_speed ����
  lm : ���� ������ �ӵ��� ������⿡ ���� �����͸� �����ϴ� ����
  rm : ������ ������ �ӵ��� ������⿡ ���� �����͸� �����ϴ� ����
* motor ���� 
  lm : motor_speed�� lm�� �����ϴ� ����
  rm : motor_speed�� rm�� �����ϴ� ����
  m_delay : delay�Լ��� �����ϴ� ���� �ð� ����   
* exturn ����
  lm : motor_speed�� lm�� �����ϴ� ����
  rm : motor_speed�� rm�� �����ϴ� ����
  sen : ������ ������ȣ�� ���� ����
  bk_delay : �극��ũ�ð��� ���� ����
* exline ����
  lm : motor_speed�� lm�� �����ϴ� ����
  rm : motor_speed�� rm�� �����ϴ� ����
  sen : ������ ������ȣ�� ���� ����
  bk_delay : �극��ũ�ð��� ���� ����



//SERVO motor ����

//��Ÿ ����

* ���� ����
sec : 1ms���� ī���� �Ǵ� ����
count : 
init_buzzer_data : ������ �����ϸ� ������ on/off���� �����ϴ� ����
init_sensor_data : sensor�� on/off���� �����ϴ� ����

*delay ����
sec_data : sec������ ���ϴ� ����
while_end : while���� ������ �����ϴ� ����

*init_sensor ����
sens : sensor�� on/off���� ����ϴ� ����

*buzzer ����
on_time : buzzer�� �Ѵ� �ð�����
off_time : buzzer�� ���� �ð�����
buzzer_count : buzzer�� on/off�ϴ� Ƚ���� �����ϴ� ����
buzzer_current : buzzer�� ���� ��� on/off�ߴ��� �˷��ִ� ����

*init_buzzer ����
buzz : buzzer�� on/off���� ����ϴ� ���� 

*led ����
on_time : led�� �Ѵ� �ð�����
off_time : led�� ���� �ð�����
buzzer_count : led�� on/off�ϴ� Ƚ���� �����ϴ� ����
buzzer_current : led�� ���� ��� on/off�ߴ��� �˷��ִ� ���� 
*/
