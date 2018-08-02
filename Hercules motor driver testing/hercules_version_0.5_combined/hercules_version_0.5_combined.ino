#include<avr/io.h>

int speedMotor1;
int speedMotor2;
void setup() {
Serial.begin(9600);
//DDRB |= (1<<4)|(1<<0)|(1<<1)(1<<5)|(1<<2)|(1<<3);//////////////////////pwm at pin 5
DDRB = 0xFF;
PORTB = (1<<0)|(0<<1)|(1<<2)|(0<<3);

}

void loop() {
TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
TCCR1A |= (1<<7)|(1<<6)|(1<<1)|(1<<0);
//TCCR1B |= (1<<7)|(1<<6)|(1<<1)|(1<<0);
//TCCR1C |= (1<<7)|(1<<6)|(1<<1)|(1<<0);

for (speedMotor1= 0; speedMotor1 < 65535; ++speedMotor1){
  OCR1A= speedMotor1;
 _delay_ms(10);
}

for (speedMotor1 = 65535; speedMotor1 > 0; --speedMotor1){
OCR1A = speedMotor1; 
delay(10);
}


for (speedMotor2= 0; speedMotor2 < 65535; ++speedMotor2){
  OCR0= speedMotor2;
 _delay_ms(10);
}

for (speedMotor2 = 65535; speedMotor2 > 0; --speedMotor2){
OCR0= speedMotor2; 
delay(10);
}





