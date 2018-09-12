#include <SoftwareSerial.h>
//these pins can not be changed 2/3 are special pins
int encoderPin1 = 18;
int encoderPin2 = 19;
int encoderPin3 = 2;
int encoderPin4 = 3;

 
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
volatile int lastEncoded1 = 0;
volatile long encoderValue1 = 0;
int m1=22,m2=24,m3=26,m4=28;
 
long lastencoderValue = 0;
long lastencoderValue1 = 0; 
int lastMSB = 0;
int lastLSB = 0;
int lastMSB1 = 0;
int lastLSB1 = 0;


 
void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}
void setup() {
 Serial.begin (115200);
 
 pinMode(encoderPin1, INPUT); 
 pinMode(encoderPin2, INPUT);
 pinMode(encoderPin3, INPUT); 
 pinMode(encoderPin4, INPUT);
 pinMode(m1,OUTPUT);
 pinMode(m2,OUTPUT);
 pinMode(m3,OUTPUT);
 pinMode(m4,OUTPUT);
 pinMode(30,OUTPUT);
 pinMode(32,OUTPUT);
 
 //digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
 //digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
 
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
attachInterrupt(0, updateEncoder, CHANGE); 
attachInterrupt(1, updateEncoder, CHANGE);
attachInterrupt(4, updateEncoder1, CHANGE); 
attachInterrupt(5, updateEncoder1, CHANGE);

}
void loop(){ 
  //Do stuff here
 
  Serial.print(encoderValue);
  Serial.print(',');
Serial.print(encoderValue1);
Serial.print('\n');
// delay(1000); //just here to slow down the output, and show it will work  even during a delay
digitalWrite(30,HIGH);
digitalWrite(32,HIGH);
digitalWrite(m1,HIGH);
digitalWrite(m2,LOW);
digitalWrite(m3,HIGH);
digitalWrite(m4,LOW);
//delay(1000);
//updateEncoder();
//updateEncoder1();
}
 

void updateEncoder1(){
  int MSB1 = digitalRead(encoderPin3); //MSB = most significant bit
  int LSB1 = digitalRead(encoderPin4); //LSB = least significant bit
 
  int encoded1 = (MSB1 << 1) |LSB1; //converting the 2 pin value to single number
  int sum1  = (lastEncoded1 << 2) | encoded1; //adding it to the previous encoded value
 
  if(sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011) encoderValue1 ++;
  if(sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000) encoderValue1 --;
 
  lastEncoded1 = encoded1; //store this value for next time
}
