/*
* More basic drive functions for the SortME v2 robot.
* Author trevor sherrard
* github: SherrardTr4129
* uses the AFmotor library found here:
* https://github.com/adafruit/Adafruit-Motor-Shield-library
*/

#include <AFMotor.h>

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);
void setup(){
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m4.setSpeed(255);
}


void loop()
{
  driveInOcto();
}

void straifL()
{
  m1.run(FORWARD);
  m2.run(BACKWARD);
  m3.run(FORWARD);
  m4.run(BACKWARD);
  delay(100);
}

void StraifR()
{
  m2.run(FORWARD);
  m1.run(BACKWARD);
  m4.run(FORWARD);
  m3.run(BACKWARD);
  delay(100); 
}

void left()
{
  m1.run(FORWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
  m4.run(FORWARD);
  delay(100); 
}

void right()
{
  m1.run(BACKWARD);
  m2.run(BACKWARD);
  m3.run(BACKWARD);
  m4.run(BACKWARD);
  delay(100); 
}

void forward()
{

  m4.run(BACKWARD);
  m3.run(FORWARD);
  m1.run(BACKWARD);
  m2.run(FORWARD);
  delay(100);
}

void Reverse()
{
  m3.run(BACKWARD);
  m4.run(FORWARD);
  m2.run(BACKWARD);
  m1.run(FORWARD);
  delay(100);
}

void RightDuP()
{
  m3.run(FORWARD);
  m4.run(BACKWARD);
}

void LeftDDown()
{
  m3.run(BACKWARD);
  m4.run(FORWARD);
}
void RightDDown()
{
  m1.run(FORWARD);
  m2.run(BACKWARD);
}
void leftDup()
{
  m1.run(BACKWARD);
  m2.run(FORWARD);
}


void driveInOcto()
{
  straifL();
  delay(2000);
  mStop();
  LeftDDown();
  delay(2000);
  mStop();
  Reverse();
  delay(2000);
  mStop();
  RightDDown();
  delay(2000);
  mStop();
  StraifR();
  delay(2000);
  mStop();
  RightDuP();
  delay(2000);
  mStop();
  forward();
  delay(2000);
  mStop();
  leftDup();
  delay(2000);
  mStop();
  
  
  
  
  
  
}

void mStop()
{
  m3.run(RELEASE);
  m4.run(RELEASE);
  m2.run(RELEASE);
  m1.run(RELEASE);
  delay(100);
}
