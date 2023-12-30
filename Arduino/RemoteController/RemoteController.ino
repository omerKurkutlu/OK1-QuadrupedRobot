#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(48,49); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
float data[8];
float message;

unsigned long previousTime=0;
unsigned long currentTime=0;
unsigned long previousSafetyTime=0;

int controlBeforeRadio=0;  // Print received sensor values from Remote

float servoPower=0;
float high=0;
float x_axis=0;
float y_axis=0;
float roll=0;
float pitch=0;
float yaw=0;
float elevation=0;
#define greenLed 3
#define redLed 4


void setup() {
  pinMode(2,INPUT);  // servo power
  pinMode(A0,INPUT);  //x-axis
  pinMode(A1,INPUT);  //y-axis
  pinMode(A2,INPUT);  //pitch
  pinMode(A3,INPUT);  //roll
  pinMode(A4,INPUT);  //yaw
  pinMode(A5,INPUT);  // elevation
  pinMode(A6,INPUT);  // Speed
  pinMode(greenLed,OUTPUT);  //greenLED
  pinMode(redLed,OUTPUT);  //redLED

  servoPower=0;
  high=3;
  x_axis=0;
  y_axis=0;
  yaw=0;
  pitch=0;
  roll=0;
  elevation=7;
  
  Serial.begin(9600);
  delay(100);
  radio.begin();
  delay(100);
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);

  digitalWrite(greenLed,LOW);    // green led is low
  digitalWrite(redLed,HIGH);   // red led is high
  delay(100);
}

void loop() {
  currentTime=millis();
  if(currentTime-previousTime>=10) //10
  {
    previousTime=currentTime;
    
    radio.stopListening();
    
    servoPower=digitalRead(2); 
    x_axis=range(analogRead(A0),0,1023,5,-5);  if(x_axis>=-0.3 && x_axis<=0.3) x_axis=0;
    y_axis=range(analogRead(A1),1023,0,2.5,-2.5);    if(y_axis>=-0.3 && y_axis<=0.3) y_axis=0;
    roll=range(analogRead(A2),1023,0,-5,5);   if(roll>=-0.4 && roll<=0.4) roll=0;
    pitch=range(analogRead(A3),0,1023,7,-7);  if(pitch>=-0.5 && pitch<=0.5) pitch=0;    
    yaw=range(analogRead(A4),1023,0,3,-3);  if(yaw>=-0.3 && yaw<=0.3) yaw=0;
    //yaw=range(analogRead(A4),1023,0,30,-30);  if(yaw>=-2 && yaw<=2) yaw=0;
    elevation=range(analogRead(A5),0,1023,0,23.5); // this must be between min=6 (reality is 8) and max=leg_length
    high=range(analogRead(A6),0,1023,2,4);
    data[0]=servoPower;
    data[1]=high;
    data[2]=x_axis;
    data[3]=y_axis;
    data[4]=roll;
    data[5]=pitch;
    data[6]=yaw;
    data[7]=elevation;
    radio.write(&data, sizeof(data));
    delay(3);

    radio.startListening();
    if(radio.available())
    {
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,HIGH);
      radio.read(&message, sizeof(message));
      //Serial.print("Battery Level=");   Serial.println(message); 
      previousSafetyTime=currentTime;
    }
    if(currentTime-previousSafetyTime>=1500)
    {
      //Serial.println("*no remote data* ");
      digitalWrite(redLed,HIGH);
      digitalWrite(greenLed,LOW);
      previousSafetyTime=currentTime;
    }
    delay(3);
    if(controlBeforeRadio==1) printInputValues(); 
  }  
}


void printInputValues()
{
  Serial.print("  servoPower=");  
  Serial.print(servoPower); 
  Serial.print("  x_axis="); 
  Serial.print(x_axis);
  Serial.print("  y_axis="); 
  Serial.print(y_axis);
  Serial.print("  pitch="); 
  Serial.print(pitch);
  Serial.print("  roll="); 
  Serial.print(roll);
  Serial.print("  yaw="); 
  Serial.print(yaw);
  Serial.print("  elevation="); 
  Serial.print(elevation);
  Serial.print("  Speed="); 
  Serial.println(high);
}

float range(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
