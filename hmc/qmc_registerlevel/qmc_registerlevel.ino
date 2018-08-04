#include <io.h>
#include <interrupt.h>
#include <stdint.h>
//#define address 0x0D
//#define mode 0x09
#define mode_type 0x01
//#include <Wire.h>
//#include <MechaQMC5883.h>

//MechaQMC5883 qmc;
uint16_t qmc_dataX;
uint16_t qmc_dataZ;
uint16_t qmc_dataY;


uint16_t qmcX;
uint16_t qmcZ;
uint16_t qmcY;

uint8_t qmc_dataXmsb;  /////when sensor gives 16 bit data
uint8_t qmc_dataYmsb;
uint8_t qmc_dataZmsb;
uint8_t qmc_dataXlsb;  /////when sensor gives 16 bit data
uint8_t qmc_dataYlsb;
uint8_t qmc_dataZlsb;


void setup() {
  Serial.begin(9600);
  DDRD = 0xFF;
  PORTD = 0xFF;
 // qmc.init();
  i2c_init();
  i2c_start();
  i2c_write(0x0D);
  i2c_write(0x09);
  i2c_write(0x0A);
  i2c_stop();
  //Serial.print("x: ");
  
}

void loop() {
 // Serial.print("x: ");

  // put your main code here, to run repeatedly:
  //int x,y,z = 0;
i2c_start();
i2c_write(0x00);
i2c_stop();

/////////////////////////////////////////for x///////////
          //pull up resistor
i2c_init();
i2c_start();

i2c_write(0x00); 
qmc_dataXlsb = i2c_read(1);

i2c_write(0x01); 
qmc_dataXmsb = i2c_read(1);


i2c_write(0x02); 
qmc_dataYlsb = i2c_read(1);

i2c_write(0x03); 
qmc_dataYmsb = i2c_read(1);


i2c_write(0x04); 
qmc_dataZlsb = i2c_read(1);


i2c_write(0x05); 
qmc_dataZlsb = i2c_read(1);


i2c_stop();

qmc_dataX |= qmc_dataXmsb;
qmcX |= qmc_dataX<<8;
qmcX |= qmc_dataXlsb ; //////////lsb saved 

qmc_dataY |= qmc_dataYmsb;
qmcY |= qmc_dataY<<8;
qmcY |= qmc_dataYlsb ; //////////lsb saved 

qmc_dataZ |= qmc_dataZmsb;
qmcZ |= qmc_dataZ<<8;
qmcZ |= qmc_dataZlsb ; //////////lsb saved 


  Serial.print("x: ");
  Serial.print(qmcX);
  Serial.print("  y: ");
  Serial.print(qmcY);
  Serial.print("  z: ");
  Serial.println(qmcZ);
 //Serial.println(qmc_dataY<<8);
  delay(250);

}





void i2c_init(){
  TWBR = 0b00001100;                    ////SET SCL FREQUENCY
  TWSR = 0x00;                     ////SET PRESCALAR
  TWCR |= (1<<2);            ////ENABLE TWI
}


void i2c_start(){
  TWCR |= (1<<2)|(1<<5)|(1<<7) ;    
  while ( (TWCR & (1<<2)) ==0);       //////////POLL
  
  }

unsigned char i2c_read(unsigned char a){
  if(a==0)
    {
       TWCR |=(1<<7)|(1<<2)|(1<<6) ;
    }
   else
    {
       TWCR |=(1<<7)|(1<<2) ; 
    } 
  while ( (TWCR & (1<<7)) == 0 );
      {
       return TWDR;
      }
 }

  


void i2c_write(unsigned char data){
  TWDR = data;
  TWCR |= (1<<2)|(1<<7);
  }

void i2c_stop(){
TWCR |= (1<<2)|(1<<4)|(1<<7);
}

