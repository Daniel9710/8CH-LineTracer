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
//DC motor 함수
Timer/Counter 1 사용
motor_off() : 모터의 힘을 푸는 함수(모든 모터함수가 끝날때사용)
motor_speed(왼속,오속) : 모터의 속도와 회전방향을 결정하는 변수값을 바꾸는 함수
motor(왼속,오속,시간) : motor_speed함수에 시간까지 지속시간까지 더한 함수
exturn(왼속,오속,센서번호,브레이크시간) : 센서번호에 적힌 센서가 선을 감지할때까지 움직이는 함수
exline(왼속,오속,센서번호,브레이크시간) : 센서번호에 적힌 센서가 선을 감지 후 지나갈때까지 움직이는 함수
driver(45센,4_5센,34_56센,3_6센,2_7센,1_8센) : 함수에 적힌 값들을 s_driver함수에 대입하는 함수
hdriver(45센,4_5센,34_56센,3_6센,2_7센,1_8센) : 함수에 적힌 값들을 s_hdriver함수에 대입하는 함수
ldriver(45센,4_5센,34_56센,3_6센,2_7센,1_8센) : 함수에 적힌 값들을 s_ldriver함수에 대입하는 함수
s_driver(1센,2센,3센,34센,4센,45센,5센,56센,6센,7센,8센) : 함수에 적힌값들을 비교계산 후 all_driver함수에 대입하는 함수
s_hdriver(1센,2센,3센,34센,4센,45센,5센,56센,6센,7센,8센) : 함수에 적힌값들을 비교계산 후 all_hdriver함수에 대입하는 함수
s_ldriver(1센,2센,3센,34센,4센,45센,5센,56센,6센,7센,8센) : 함수에 적힌값들을 비교계산 후 all_ldriver함수에 대입하는 함수
all_driver(1센왼,1센오,2센왼,2센오,3센왼,3센오,34센왼,34센오,4센왼,4센오,45센왼,45센오,5센왼,5센오,56센왼,56센오,6센왼,6센오,7센왼,7센오,8센왼,8센오) : 함수에 적힌 값들을 sp[0][n]변수에 대입하는 함수
all_hdriver(1센왼,1센오,2센왼,2센오,3센왼,3센오,34센왼,34센오,4센왼,4센오,45센왼,45센오,5센왼,5센오,56센왼,56센오,6센왼,6센오,7센왼,7센오,8센왼,8센오) : 함수에 적힌 값들을 sp[1][n]변수에 대입하는 함수
all_ldriver(1센왼,1센오,2센왼,2센오,3센왼,3센오,34센왼,34센오,4센왼,4센오,45센왼,45센오,5센왼,5센오,56센왼,56센오,6센왼,6센오,7센왼,7센오,8센왼,8센오) : 함수에 적힌 값들을 sp[2][n]변수에 대입하는 함수
line_del(드라이버설정값,
//SERVO motor 함수
Timer/Counter0 사용

//기타 함수
Timer/Counter2 사용 
start() : 프로그램을 시작하기전 모든 기본 설정값이 다 들어 있는 함수
delay(지속시간) : 지속시간 함수 
wait() : startbutton을 눌러야 넘어감
init_sensor(센서on/off) : sensor를 on/off하는 함수
buzzer_on() : 버저를 on하는 함수
buzzer_off() : 버저를 off하는 함수
buzzer(on시간,off시간,횟수) : 버저를 on/off를 하는 횟수까지 정하는 함수
init_buzzer(버저on/off) : 센서가 선을 감지했을때 버저를 on/off할지 결정하는 함수
led_on() : led를 on하는 함수
led_off() : led를 off하는 함수 
led(on시간,off시간,횟수) : led를 on/off를 하는 횟수까지 정하는 함수

*/

/*
//DC motor 변수

* 전역 변수 
  mt_count : Timer/Count1의 PWM변수
  l_motor_speed : mt_count와 비교하여 lmotor enable을 on/off하는 변수
  r_motor_speed : mt_count와 비교하여 rmotor enable을 on/off하는 변수
  lm_dir : lmotor의 회전 방향을 나타내는 변수
  rm_dir : rmotor의 회전 방향을 나타내는 변수

* motor_speed 변수
  lm : 왼쪽 모터의 속도와 진행방향에 대한 데이터를 대입하는 변수
  rm : 오른쪽 모터의 속도와 진행방향에 대한 데이터를 대입하는 변수
* motor 변수 
  lm : motor_speed의 lm에 대입하는 변수
  rm : motor_speed의 rm에 대입하는 변수
  m_delay : delay함수에 대입하는 지속 시간 변수   
* exturn 변수
  lm : motor_speed의 lm에 대입하는 변수
  rm : motor_speed의 rm에 대입하는 변수
  sen : 감지할 센서번호에 대한 변수
  bk_delay : 브레이크시간에 대한 변수
* exline 변수
  lm : motor_speed의 lm에 대입하는 변수
  rm : motor_speed의 rm에 대입하는 변수
  sen : 감지할 센서번호에 대한 변수
  bk_delay : 브레이크시간에 대한 변수



//SERVO motor 변수

//기타 변수

* 전역 변수
sec : 1ms마다 카운팅 되는 변수
count : 
init_buzzer_data : 센서가 감지하면 버저를 on/off할지 결정하는 변수
init_sensor_data : sensor를 on/off할지 결정하는 변수

*delay 변수
sec_data : sec변수와 비교하는 변수
while_end : while문을 끝낼지 결정하는 변수

*init_sensor 변수
sens : sensor를 on/off할지 명령하는 변수

*buzzer 변수
on_time : buzzer를 켜는 시간변수
off_time : buzzer를 끄는 시간변수
buzzer_count : buzzer를 on/off하는 횟수를 결정하는 변수
buzzer_current : buzzer이 현재 몇번 on/off했는지 알려주는 변수

*init_buzzer 변수
buzz : buzzer를 on/off할지 명령하는 변수 

*led 변수
on_time : led를 켜는 시간변수
off_time : led를 끄는 시간변수
buzzer_count : led를 on/off하는 횟수를 결정하는 변수
buzzer_current : led가 현재 몇번 on/off했는지 알려주는 변수 
*/
