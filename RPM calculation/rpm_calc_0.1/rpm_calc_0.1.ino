#include <avr/io.h>
#include <avr/interrupt.h>


volatile long int prevtick =0;   
volatile long int currtick =0;
volatile long int ticks ;
float rpm;
unsigned long int prevtime =0;
unsigned long int currtime =0;
//unsigned long int tim = 0 ;


void setup() {
 
 sei();
  //port_init();
  Serial.begin(9600);
  DDRD &= ~(1 << PD1);
  PORTD |= (1 << PD1);
  DDRD  &= ~(1 << PD2);
  PORTD |= (1 << PD2);
  /////////////////////////////////////////////////////////
  EICRA |= (1 << ISC11) | (1 << ISC10); ////on rising
  //EIFR |= (1 << INTF1);
  EIMSK |= (1 << INT1);
  //Serial.print("hello fraandz") ;

}

void loop() {
  //Serial.println("chaai peeelo") ;
  
 
  currtime = millis();
  //tim = currtime - prevtime ;
  //Serial.println(currtime) ;
 // Serial.println(tim) ;
  if((currtime - prevtime) >= 100)
  {
    ticks = currtick - prevtick ;
    rpm = (ticks * 60)/600 ;
    Serial.print("Ticks = ") ;
    Serial.print(ticks);
    Serial.print(" RPM = ") ;
    Serial.println(rpm) ;
     prevtime = currtime ;
  prevtick = currtick ;

  }
 

}



ISR(INT1_vect) {
  if (bit_is_set(PIND, 2)) {
    currtick++;
  }
  else {
    currtick--;
  }
}

  











