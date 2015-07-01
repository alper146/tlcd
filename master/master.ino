/*
    fluroplot ADC
    pins:
    cs=10
    sdo/rdy=12
    sck=13
    keypad=2-9
*/
#include <SPI.h>
#include <Keypad.h>
#define F_CPU 16000000UL
unsigned char sspin=10; //cs pin
uint16_t timer=10;
byte a=0;
union{
		int32_t value;
		uint8_t aa[4];
	} c ;
unsigned int command=0;
void perform_command(unsigned int task);
void send_adc(void);
void set_timer(void);

void setup(){
DDRB&=~(1<<4);
//pinMode(12,INPUT);  //to check ready pin
DDRB|=(1<<2);
DDRC|=(1<<5);

//pinMode(sspin,OUTPUT);
PORTB|=(1<<2);
//digitalWrite(sspin,HIGH);//for single conversion
SPI.begin();
SPI.setBitOrder(MSBFIRST);
SPI.setDataMode(SPI_MODE3);
SPI.setClockDivider(SPI_CLOCK_DIV8);//max. speed of chip is 5 Mhz
Serial.begin(9600);  

}

void loop(){

  
if(Serial.available()){
    command=Serial.read();
 //   Serial.print(11); // connection established, command received 
    perform_command(command);                 
                      }
  
  
}


void perform_command(unsigned int task){
switch(task){
    case 10:
          send_adc();
            break;
  
    case 20: 
          calibration();
            break;

       case 30:
         number_of_samples();
           }

}

 void send_adc(void){
   a=1;
   uint32_t toplam1;
    uint32_t toplam2;
     uint32_t toplam3;
   for(int i=0;i<a;i++){
  PORTC|=(1<<5);
 PORTB&=~(1<<2);

while(digitalRead(12)){
  
  //digitalWrite(sspin,LOW);
                    
                    }
                    PORTC&=~(1<<5);
  c.aa[2]=SPI.transfer(0x00);
  c.aa[1]=SPI.transfer(0x00);
  c.aa[0]=SPI.transfer(0x00);
  c.aa[3]=0x00;
  
 PORTB|=(1<<2);
   
   if((c.aa[2]&(1<<6))|(c.aa[2]&(1<<7))){
    c.aa[2]&=~(1<<6);}
     else if(c.aa[2]&(1<<5)){
    c.value=0x400000-c.value;}
    
 toplam1=toplam1+c.aa[0]; 
  toplam2=toplam2+c.aa[1]; 
  toplam3=toplam3+c.aa[2]; 
  
 }
 c.aa[0]=toplam1/a;
 c.aa[1]=toplam2/a;
 c.aa[2]=toplam3/a;
  //check if overflow has occured
  if((c.aa[2]&(1<<6))|(c.aa[2]&(1<<7))){
    c.aa[2]&=~(1<<6);
    Serial.write(c.aa[0]);  
     Serial.write(c.aa[1]);
    Serial.write(c.aa[2]);  
                                      }
//check if sign bit is affected. if so, since it is two's compliment,
// substract it from 2^N
  else if(c.aa[2]&(1<<5)){
    c.value=0x400000-c.value;
   Serial.write(c.aa[0]);
     Serial.write(c.aa[1]);
    Serial.write(c.aa[2]);  
                          }

  else{
   Serial.write(c.aa[0]);
     Serial.write(c.aa[1]);
    Serial.write(c.aa[2]);  
      }  
  delay(10);
  
   
          }
          
 void calibration(void){
 byte b;
 while(!Serial.available()){}
 b=Serial.read();//make it min
 send_adc();
 while(!Serial.available()){}
 b=Serial.read();// write to fram as max
 send_adc();
 // some curve fitting algorithms
 // ...
 
 }
 void number_of_samples(void)
 {
 while(!Serial.available()){
 a=Serial.read();
 
 }
 }


