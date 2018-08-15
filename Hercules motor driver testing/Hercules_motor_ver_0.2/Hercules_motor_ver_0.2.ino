#include<avr/io.h>
#include<avr/interrupt.h>
int speedMotor = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//DDRB |= (1<<4)|(1<<0)|(0<<1);
//PORTB = (1<<0)|(0<<1);
DDRB = 0xFF;
PORTB = 0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:

pwm_start();
for (speedMotor= 0; speedMotor < 255; ++speedMotor){
OCR0 = speedMotor;
 _delay_ms(10);
}
for (speedMotor = 255; speedMotor > 0; --speedMotor){
OCR0 = speedMotor;
_delay_ms(10);

}
Serial.println(speedMotor);
}

void pwm_start(){
  TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);          //////////CTC mode /initialize timer0 for pwm
}
