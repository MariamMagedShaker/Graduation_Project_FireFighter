#include <SoftwareSerial.h>
//#include <Ultrasonic.h>
#include <Servo.h> 
#include <Wire.h> 
#define echopin1 A2 
#define trigpin1 A3
#define echopin2 A4 
#define trigpin2 A5

Servo myservo;  // create servo object to control a servo

int pos = 0;  
int LFLAM=9;
int CFLAM=10;
int RFLAM=11;
int WaterP=12;

int distanceFwd;
int distanceBwd;
long duration2;
long duration1;

int data=0;
int motor2Pin1 = 6;
int motor2Pin2 = 7;

int motor1Pin1 = 2;
int motor1Pin2 = 3; 

int Speed = 225;
int timer = 0;

SoftwareSerial BT(0, 1);
void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);
BT.begin(9600);
pinMode (trigpin1, OUTPUT);
pinMode (echopin1, INPUT );

pinMode (trigpin2, OUTPUT);
pinMode (echopin2, INPUT );

myservo.attach(WaterP);

pinMode(LFLAM,INPUT);
pinMode(CFLAM,INPUT);
pinMode(RFLAM,INPUT);

pinMode(motor2Pin1,OUTPUT);
pinMode(motor2Pin2,OUTPUT);
pinMode(motor1Pin1,OUTPUT);
pinMode(motor1Pin2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    //data=Serial.parseInt();
     //   Serial.print("data:");
       // Serial.print(data+1);
        //Serial.println("...");
    data=BT.read();
    distanceFwd = dataaFwd(); 
    //Serial.print("Fwd :");
    Serial.println(distanceFwd);
    //Serial.print("....");

    distanceBwd = dataaBwd();
    //Serial.print("Bwd:");  
 //   Serial.print(distanceBwd);
    //Serial.println("...");
    if(data==1){
      Serial.println("1");
      forword();
      Serial.println("Go Forward!");
      }
      else if(data== 2){   
      Serial.println("2");
      backword();
      Serial.println("Reverse!");
        }
      else if(data== 3){   
      Serial.println("3");
      turnLeft();
      Serial.println("Turn LEFT");
        }
      else if(data== 4){   
      Serial.println("4");
      turnRight();
      Serial.println("Turn RIGHT");;
        }      
       else if(data== 5){   
      Serial.println("5");
      Stop();
      Serial.println("STOP!");
        }

        
      /*if(digitalRead(LFLAM)== HIGH )and (data !=  )
       {
         Serial.println("LFLAM  LL"); 
         turnLeft();  
         delay(30);
         Stop();
        }
       else if((distanceFwd>20)&& (digitalRead(CFLAM)==HIGH))
       {
          Serial.println("CFLAM  SS"); 
          forword();
          delay(30);
          Stop();
       }  
       else if(digitalRead(RFLAM)==HIGH)
       {
          Serial.println("RFLAM  RR"); 
          turnRight();
          delay(30);
          Stop();
       } 
       else if  ((digitalRead(RFLAM)==LOW)&&(digitalRead(CFLAM)==LOW)&&(digitalRead(LFLAM)==LOW))
       {
   
          Serial.println("No fire");
       }
       else if(((distanceFwd<20)&&(digitalRead(CFLAM)==HIGH))||data==6)
       {
           pos = analogRead(WaterP);
           // reads the value of the potentiometer (value between 0 and 1023)
           pos = map(pos, 0, 1023, 0, 180);
           // scale it to use it with the servo (value between 0 and 180)
           myservo.write(pos); // sets the servo position according to the scaled value
       }
  /*  timer = timer+1;
if(timer>4000){
     

// BT.write(distanceFwd);
   Serial.print(distanceFwd);
 timer=0; 
}*/
}
}


void forword(){

    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,HIGH); 
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,HIGH);

}

void backword(){

    digitalWrite(motor1Pin1,HIGH);
    digitalWrite(motor1Pin2,LOW); 
    digitalWrite(motor2Pin1,HIGH);
    digitalWrite(motor2Pin2,LOW);

}

void turnLeft(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);

}

void turnRight(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);

}



void Stop(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
}


long dataaFwd() 
{
  digitalWrite(trigpin1,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1,LOW);
  duration1=pulseIn (echopin1,HIGH);
  return duration1 / 29 / 2; 
}
long dataaBwd() 
{
  digitalWrite(trigpin2,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin2,LOW);
  duration2=pulseIn(echopin2,HIGH);
  return duration2 / 29 / 2; 
}
