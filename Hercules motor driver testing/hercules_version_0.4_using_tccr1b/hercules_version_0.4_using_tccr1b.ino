#include<avr/io.h>
//#include<avr/interrupt.h>
//int speedMotor1 = (40/100)*255;
//int speedMotor2 = (40/100)*255;
int speedMotor;
void setup() {
Serial.begin(9600);
DDRB |= (1<<5)|(1<<2)|(1<<3);          //pwm pin = B5,,direction pins B2,B3
//DDRB = 0xFF;
PORTB = (1<<0)|(0<<1);

}

void loop() {
//TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
TCCR1A |= (1<<7)|(1<<6)|(1<<1)|(1<<0);
for (speedMotor= 0; speedMotor < 65535; ++speedMotor){
  OCR1A= speedMotor;
 _delay_ms(10);
 Serial.print(speedMotor);

}
for (speedMotor = 65535; speedMotor > 0; --speedMotor){
//OCR0 = speedMotor;
//_delay_ms(10);
//TCCR1A |= (1<<7)|(1<<6);
OCR1A = speedMotor; 
delay(10);
}
//Serial.println(speedMotor);
}


