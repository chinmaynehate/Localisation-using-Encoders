#include<avr/io.h>
//#include<avr/interrupt.h>
int speedMotor = 0;

void setup() {
Serial.begin(9600);
DDRB |= (1<<4)|(1<<0)|(1<<1);
PORTB = (1<<0)|(0<<1);

}

void loop() {
TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
for (speedMotor= 0; speedMotor < 255; ++speedMotor){
OCR0 = speedMotor;
 _delay_ms(10);

}
for (speedMotor = 255; speedMotor > 0; --speedMotor){
OCR0 = speedMotor;
_delay_ms(10);

}
//Serial.println(speedMotor);
}


