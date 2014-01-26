/*
* Mecanum drive method for SortME V2 robot
* Author: Trevor Sherrard
* using the AFMotor library found here:
* https://github.com/adafruit/Adafruit-Motor-Shield-library
*/


#include <AFMotor.h>

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);
AF_DCMotor motorArr[4];


int speedm1 = 0;
int speedm2 = 1;
int speedm3 = 2;
int speedm4 = 3;


void setup()
{
motorArr[0] = m1;
motorArr[1] = m2;
motorArr[2] = m3;
motorArr[3] = m4;
}

void loop()
{
  int speed1, speed2, speed3, speed4 = 0;
  double motors[4];
  motors = getSpeedArray(45, 1);
  speed1 = modifiedMap(motors[0], -1, 1, -256, 256);
  speed2 = modifiedMap(motors[1], -1, 1, -256, 256);
  speed3 = modifiedMap(motors[2], -1, 1, -256, 256);
  speed4 = modifiedMap(motors[3], -1, 1, -256, 256);
  
  int speedArr[4];
  speedArr[0] = speed1;
  speedArr[1] = speed2;
  speedArr[2] = speed3;
  speedArr[3] = speed4;
  
  for(int i = 0; i < 4; i++)
  {
    if(checkReverse(speedArr[i])
    {
      motors[i].setSpeed(abs(speedArr[i]));
      motors[i].run(BACKWARD);
    }
    else
    {
      motors.setSpeed(speedArr[i]);
      motors[i].run(FORWARD);
    }
  }
   
}

boolean checkReverse(speedm)
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

double[] getSpeedArray(double angle, double magnitude)
{
  double motors[4]
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
  xcos = cos(rad);
  ysin = sin(rad);
  motors[speedm4] = ysin * magnitude; //front left
  motors[speedm2] = xcos * magnitude; //front right
  motors[speedm1] = xcos * magnitude; //rear left
  motors[speedm3] = ysin * magnitude; //rear right
  return motors;
}

