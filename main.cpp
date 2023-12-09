Source Code

#include "AFMotor.h"
#include <Servo.h>

#define echopin A4 
#define trigpin A5 

Servo myservo;

const int MOTOR_1 = 1;
const int MOTOR_2 = 2;
const int MOTOR_3 = 3;
const int MOTOR_4 = 4;

AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); 
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); 
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); 
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); 


int distance_L, distance_F, distance_R;
long distance;

int set = 20; //input distance

void setup() {
  Serial.begin(9600); 
  Serial.println("Start");

  myservo.attach(10);
  myservo.write(115);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  motor1.setSpeed(150); 
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
}


void loop() {
  distance_F = data();
  Serial.print("S=");
  Serial.println(distance_F);

  if (distance_F > set) {
    Serial.println("Forward");
    motor1.run(FORWARD); 
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  } else {
    hc_sr4();
  }
}

long data() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  distance = pulseIn(echopin, HIGH);
  return distance / 29 / 2;
}

void compareDistance() {
  if (distance_L > distance_R) {
    motor1.run(BACKWARD); 
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    delay(350);
  } else if (distance_R > distance_L) {
    motor1.run(FORWARD); 
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(350);
  } else {
    motor1.run(BACKWARD); 
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(500);
    motor1.run(FORWARD); 
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(500);
  }
}

void hc_sr4() {
  Serial.println("Stop");
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  myservo.write(0);
  delay(300);
  distance_R = data();
  delay(100);
  myservo.write(170);
  delay(500);
  distance_L = data();
  delay(100);
  myservo.write(90);
  delay(300);
  compareDistance();
}