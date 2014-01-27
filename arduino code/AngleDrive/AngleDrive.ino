#include <AFMotor.h>

/*
* Mecanum drive method for SortME V2 robot
 * Author: Trevor Sherrard
 * using the AFMotor library found here:
 * https://github.com/adafruit/Adafruit-Motor-Shield-library
 */



AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

int speedm1 = 0;
int speedm2 = 1;
int speedm3 = 2;
int speedm4 = 3;


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  double speed1, speed2, speed3, speed4 = 0;
  speed1 = getSpeedArray(30, 1, 1);
  speed2 = getSpeedArray(30, 1, 2);
  speed3 = getSpeedArray(30, 1, 3);
  speed4 = getSpeedArray(30, 1, 4);
  Serial.print(speed1);

  speed1 = modifiedMap(speed1, -1, 1, -255, 255);
  speed2 = modifiedMap(speed2, -1, 1, -255, 255);
  speed3 = modifiedMap(speed3, -1, 1, -255, 255);
  speed4 = modifiedMap(speed4, -1, 1, -255, 255);
  
  int speedArr[4];
  speedArr[0] = speed1;
  speedArr[1] = speed2;
  speedArr[2] = speed3;
  speedArr[3] = speed4;


  if(checkReverse1(speedArr[0]))
  {
    m1.setSpeed(abs(speedArr[0]));
    m1.run(BACKWARD);
  }
  else
  {
    m1.setSpeed(speedArr[0]);
    m1.run(FORWARD);
  }
  
  if(checkReverse1(speedArr[1]))
  {
    m2.setSpeed(abs(speedArr[1]));
    m1.run(BACKWARD);
  }
  else
  {
    m2.setSpeed(speedArr[1]);
    m2.run(FORWARD);
  }
    if(checkReverse1(speedArr[2]))
  {
    m3.setSpeed(abs(speedArr[2]));
    m3.run(BACKWARD);
  }
  else
  {
    m3.setSpeed(speedArr[2]);
    m3.run(FORWARD);
  }
    if(checkReverse1(speedArr[3]))
  {
    m4.setSpeed(abs(speedArr[3]));
    m4.run(BACKWARD);
  }
  else
  {
    m4.setSpeed(speedArr[3]);
    m4.run(FORWARD);
  }
  delay(1000);
}

boolean checkReverse1(double speedm)
{
  if(speedm < 0)
  {
    return true;
  }
  else
  {
    return false;
  }

}

double modifiedMap(double x, double in_min, double in_max, double out_min, double out_max)
{
  double temp = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  temp = (int) (4*temp + .5);
  return (double) temp/4;
}

double getSpeedArray(double angle, double magnitude, int wheelnumber)
{
  double motorSpeed;
  if(magnitude > 1)
  {
    magnitude = 1;
  }
  if(magnitude < -1)
  {
    magnitude = -1;
  }

  if(angle > 360)
  {
    angle = 360;
  }
  double rad = angle * (PI/180);
  double xcos = cos(rad);
  double ysin = sin(rad);
  if(wheelnumber == 1)
  {
    motorSpeed = ysin * magnitude; //front left
  }
  else if(wheelnumber == 2)
  {
    motorSpeed = xcos * magnitude; //front right
  }
  else if(wheelnumber == 3)
  {
    motorSpeed = xcos * magnitude; //rear left
  }
  else if(wheelnumber == 4)
  {
    motorSpeed = ysin * magnitude; //rear right
  }
  return motorSpeed;
}


