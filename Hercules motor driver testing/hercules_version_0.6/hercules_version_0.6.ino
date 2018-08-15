///////formula page 130

#include<avr/io.h>
//#include<avr/interrupt.h>
//int speedMotor1 = (40/100)*255;
//int speedMotor2 = (40/100)*255;
int speedMotor;
void setup() {
Serial.begin(9600);
//DDRB |= (1<<6)|(1<<0)|(1<<1);          //pwm pin = B5,,direction pins B2,B3
DDRB = 0xFF;
DDRE = 0xFF;
PORTB = (1<<0)|(1<<1);
ICR1H = 0x02;
ICR1L = 0x9A;      /////666
/*TCCR1B |= (1<<WGM12)|(1<<WGM13)(1<<CS11);
TCCR1A &= ~(1<<WGM10);
TCCR1A |= (1<<WGM11);*/
ICR3H = 0x02;
ICR3L = 0x9A;
}

void loop() {
//TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11);
//TCCR1A &= ~(1<<WGM10);
//TCCR1A |= (1<<WGM11);
//TCCR1A = 0xAA;
TCCR1A = 0xAA;
//TCCR1A |= (1<<5);
  
OCR1A = 500;
OCR1B= 200;
OCR1C = 300;   //666


/*
TCCR3A |= (1<<7)|(1<<1);
TCCR3A &= ~(1<<6);
TCCR3A &= ~(1<<0);*/
TCCR3A = 0xAA;
TCCR3B |= (1<<4)|(1<<3)|(1<<1);
/*OCR3A = 650;
OCR3B = 250;
OCR3C = 454;*/

/*for (speedMotor= 0; speedMotor < 500; ++speedMotor){
  OCR3B= speedMotor;
  OCR3C= speedMotor;
  OCR3A = speedMotor;
  //ICR1 = speedMotor;
  
 _delay_ms(10);
 Serial.print(speedMotor);

}
for (speedMotor = 500; speedMotor > 0; --speedMotor){
//OCR0 = speedMotor;
//_delay_ms(10);
//TCCR1A |= (1<<7)|(1<<6);
OCR3B = speedMotor; 
OCR3C= speedMotor;
OCR3A = speedMotor;
//ICR1 = speedMotor;
delay(10);*/
}
//Serial.println(speedMotor);
}


