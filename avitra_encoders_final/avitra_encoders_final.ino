#include <avr/io.h>
#include <avr/interrupt.h>


volatile int count1 = 0;
volatile int count2 = 0;
volatile int count3 = 0;
volatile int count4 = 0;                    

void setup() {

  sei();
  //port_init();
  Serial.begin(9600);
  ///////////////FOR ENCODER 1/////////////
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

void loop() {
 /*// Serial.println("1");
  //Serial.print("      ");
  Serial.print(count1);
 // Serial.println("2");
  Serial.print("      ");
  Serial.print(count2);
 // Serial.println("2");
  Serial.print("      ");
  Serial.print(count3);
  //Serial.println("2");
  Serial.print("      ");
  Serial.println(count4);
*/



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

