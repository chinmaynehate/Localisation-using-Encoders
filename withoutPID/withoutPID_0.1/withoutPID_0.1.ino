#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <math.h> //included to support power function



volatile int count1 = 0;
volatile int count2 = 0;
volatile int count3 = 0;
volatile int count4 = 0; 
volatile unsigned int Degrees;                   

void setup() {
  Serial.begin(9600);
  basic();
}

void loop() {
 

print_ticks();
print_rpm();
print_hmc_data();


}




void print_ticks(void){

  Serial.print("encoder:\t");
  Serial.print(count1);
  Serial.print("   ");
  Serial.print(count2);
  Serial.print("   ");
  Serial.print(count3);
  Serial.print("   ");
  Serial.print(count4);
  Serial.println("   ");

}
void deff_encoder(void){

  sei();
//////////////////FOR ENCODER 1/////////////
  DDRE &= ~(1 << PE5);
  PORTE |= (1 << PE5);
  DDRE  &= ~(1 << PE4);
  PORTE |= (1 << PE4);
  EICRB |= (1 << ISC51) | (1 << ISC50); ////on rising
  //EIFR |= (1 << INTF1);
  EIMSK |= (1 << INT5);

/////////////////FOR ENCODER 2///////////////////////
  DDRD &= ~(1 << PD1);
  PORTD |= (1 << PD1);
  DDRD  &= ~(1 << PD3);
  PORTD |= (1 << PD3);
  EICRA |= (1 << ISC11) | (1 << ISC10); ////on rising
  //EIFR |= (1 << INTF1);
  EIMSK |= (1 << INT1);
//////////////////FOR ENCODER 3//////////////////////////
  DDRE &= ~(1 << PE6);
  PORTE |= (1 << PE6);
  DDRE  &= ~(1 << PE7);
  PORTE |= (1 << PE7);
  EICRB |= (1 << ISC61) | (1 << ISC60); ////on rising
  //EIFR |= (1 << INTF1);
  EIMSK |= (1 << INT6);
//////////////////FOR ENCODER 4//////////////////////////
  DDRD &= ~(1 << PD0);
  PORTD |= (1 << PD0);
  DDRD  &= ~(1 << PD2);
  PORTD |= (1 << PD2);
  EICRA |= (1 << ISC01) | (1 << ISC00); ////on rising
  //EIFR |= (1 << INTF1);
  EIMSK |= (1 << INT0);
  
}
void basic(){
hercules_config();
hmc_config();
pid_config();
rpm();
deff_encoder();


}
void hercules_config(void){
deff_pwmPins();
deff_pwmConfig();
}
void deff_pwmPins(){
///using TIMER/Counter1 and TIMER/counter3

///In TIMER/Counter1..configuring TCCR1A and TCCR1B in fast PWM mode as given in the datasheet
///using ouput control register 1 for Timer/counter1 to set PWM values(OCR1A,OCR1B,OCR1C)....OCR1A gives pwm to B5...OCR1B gives pwm to B6.....OCR1C gives pwm to B7
///ICR register is used to store max pwm value which is equal to 666. i.e ICR1H = 0x02 and ICR1L = 0x9A


///In TIMER/Counter3..configuring TCCR3A and TCCR3B in fast PWM mode as given in the datasheet 
///using ouput control register 3 for Timer/counter1 to set PWM values(OCR3A,OCR3B,OCR3C)....OCR3A gives pwm to E3...OCR3B gives pwm to E4.....OCR3C gives pwm to E5
///ICR register is used to store max pwm value which is equal to 666. i.e ICR3H = 0x02 and ICR3L = 0x9A

//since we are using 4 motors, we need 4 pwm pins. We will use B5,B6 , E4,E5. ....B5,B6 FOR MOTOR1,MOTOR2.....E4,E5 for motor3,motor4

DDRB |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<5)|(1<<6);////B5=pwm for motor1..B6=pwm for motor2....B0,B1 are direction pins for motor1...B2,B3=direction pins of motor2
PORTB = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<5)|(1<<6);


DDRE |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);////E4=pwm for motor3..E5=pwm for motor4....E0,E1 are direction pins for motor3...E2,E3=direction pins of motor4
PORTE = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);

}

void deff_pwmConfig(){

deff_pwm12();

deff_pwm34();  

}

void deff_pwm12(){
ICR1H = 0x02;
ICR1L = 0x9A;      /////666    ICR1 register is for Timer/counter1....its max value is 666 i.e 0x029A
TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11);///setting TCCR1A and TCCR1B in fast pwm mode
TCCR1A = 0xAA;
OCR1A =0;
OCR1B= 0;
OCR1C =0; //this can be ignored as we dont need pwm at B7 
}

void deff_pwm34(){

ICR3H = 0x02;  ///// ICR1 register is for Timer/counter1....its max value is 666 i.e 0x029A
ICR3L = 0x9A;
TCCR3A = 0xAA;
TCCR3B |= (1<<4)|(1<<3)|(1<<1);
OCR3A =0;//this can be ignored as we dont need pwm at E3
OCR3B= 0;
OCR3C = 0; 

}
//////////////INT FOR ENCODER 1///////////
ISR(INT5_vect) {
  if (bit_is_set(PINE, 4)) {
    count1++;
  }
  else {
    count1--;
  }
}
//////////////INT FOR ENCODER 2///////////////////////////
ISR(INT1_vect){
  if (bit_is_set(PIND, 3)) {
    count2++;
  }
  else {
    count2--;
  }
}
////////////////INT FOR ENCODER 3//////////////////////
ISR(INT6_vect) {
  if (bit_is_set(PINE, 7)) {
    count3++;
  }
  else {
    count3--;
  }
}
////////////////INT FOR ENCODER 4//////////////////////
ISR(INT0_vect) {
  if (bit_is_set(PIND, 2)) {
    count4++;
  }
  else {
    count4--;
  }
}





//Function for velocity control
void velocity (unsigned char motor1, unsigned char motor2, unsigned char motor3, unsigned char motor4 )
{
	OCR1A = (unsigned char)motor1;
	OCR1B = (unsigned char)motor2;

	OCR3B = (unsigned char)motor3;
	OCR3C = (unsigned char)motor4;

}


//Function used for turning robot by specified degrees
//Function used for moving robot forward by specified distance
void linear_distance_motor1(unsigned float distance1){
int reqd_ticks = (135)*distance1/(pi*d);
while(1){
if(count1<=reqd_ticks){
velocity(300,0,0,0);

}


}








void calibrate_ticks1(){
if(count1<135){
velocity(200,0,0,0);
else{
velocity(0,0,0,0);
}

}

