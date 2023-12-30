#include<Servo.h>
#include<MPU6050.h> // SLC and SDA pins connect to respected pin in Arduino 
#include<Wire.h>
#include <PID_v1.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "myServo_class.h" // to calculate the pre/curr/next position of servos
#include "Quadruped.h"

#define led1 22
#define led2 23
#define led3 24
#define led4 25
#define led5 26
#define led6 27

int controlBeforeRadio=0;  // Print received sensor values from Remote & imu

int delayForServos=7;

myServo s[12];
int* servoAngles; //to read servo anngles from Quadruped class we ned to use referance

MPU6050 mpu;

// Radio 
RF24 radio(40,42); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
float data[8];

//lipo battety level
float vPower=4.5;   // lipododan arduinoya gelen volt benimki icin 5.3 olmali 
float r1=2200;
float r2=220;

//valiables for IMU
int acceX,acceY,acceZ,gyroX,gyroY,gyroZ;
int previous_acceX=0;
int previous_acceY=0;

unsigned long previousTime=0;
unsigned long currentTime=0;
unsigned long previousWalkTime=0;
unsigned long previousSafetyTime=0; // for radio singal control
unsigned long loopBegin,loopEnd;
// received sensor values from Remote
float servoPower=0;
float high=3;   
float x_axis=0;
float y_axis=0;
float yaw=0;        // it gives angle to rotate
float pitch=0;      // it gives cm
float roll=0;       // it gives cm
float elevation=15;


#define relay1 14
#define relay2 15

Quadruped Quad(11.5,12); 

void setup() {
  Serial.begin(9600);
  
  //setup radio
  radio.begin();
  delay(100);
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  delay(50);
  
  //setup IMU
  Wire.begin();
  mpu.initialize();
  
  //setup pins
  pinMode(A0,INPUT); // Battery Level
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);

  
  //initial values
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);

  //LEDs are ON
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led5,HIGH);
  digitalWrite(led6,HIGH);
  
  servoAngles=Quad.signalValues();
  for(int i=0;i<12;i++)
      {
        
        s[i].setPin(i+2);            //set pin number 
        s[i].setOffset(servoAngles[i]);  // drive servo to offset position
        s[i].currentAngle=servoAngles[i];     // initialy currAng is set to offset
        s[i].setTargetAngle(servoAngles[i]);     // initialy currAng is set to offset
        //Serial.print("servo ");Serial.print(i+1);Serial.print("= ");Serial.println(s[i].targetAngle);
      }
   //execute(servoAngles);  // we can't execute because Relays are off...!
  delay(100);
}

void loop() {
  
  loopBegin=currentTime=millis();
  
  if(currentTime-previousTime>=10)
  {
    previousTime=currentTime;

    //Read Radio Data
    radio.startListening();
    if (radio.available())
    {
      radio.read(&data, sizeof(data));
      previousSafetyTime=currentTime;

      servoPower=data[0];
      high=data[1];   
      x_axis=data[2];
      y_axis=data[3];
      roll=data[4];
      pitch=data[5];
      yaw=data[6];
      elevation=data[7];
    }
    delay(3);
    
    // check whether remote disconnected
    if(currentTime-previousSafetyTime>=3000)
    {
      Serial.println("*no remote data* ");
      previousSafetyTime=currentTime;
      // set everthing to offset value
    }
  
    //Read IMI values
    mpu.getAcceleration(&acceX,&acceY,&acceZ);
    mpu.getRotation(&gyroX,&gyroY,&gyroZ);
    
    acceX=map(acceX,-17000,17000,-90,90);
    if(abs(previous_acceX-acceX)>=15)
    {
      previous_acceX=acceX;
    }
    else
    {
      acceX=previous_acceX;
    } 
    acceX=acceX/5; 
    //if(acceX>=-1 && acceX<=1) acceX=0;  
    
    
    acceY=map(acceY,-17000,17000,90,-90);
    if(acceY>=-3 && acceY<=3) acceY=0;
    
    // sent t battary level to remote
    radio.stopListening();
    float v=(analogRead(0)*vPower)/1024.0;
    float volt=v/(r2/(r1+r2));
    radio.write(&volt, sizeof(volt));
    delay(3);

    /*
     * code there
     */
    if(servoPower==1)
    {
     digitalWrite(relay1,HIGH);
     digitalWrite(relay2,HIGH);
    }
    else
    {
     digitalWrite(relay1,LOW);
     digitalWrite(relay2,LOW);
    }
    
    Quad.setVariables(x_axis,y_axis,roll,pitch,yaw,elevation,high,acceX,acceY);
    //Quad.displayVariables();
    servoAngles=Quad.signalValues();

    fireServoSignal(servoAngles);

    if(controlBeforeRadio==1) sensorDatas(); //print remote/ imu / sensors data
 
  }// end time-loop

  //delay(1000);
  
  loopEnd=millis();
  //Serial.print("Loop Time"); Serial.println(loopEnd-loopBegin);
}//end void loop
