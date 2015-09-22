/*
This program demonstrates the use of the Micro Magician dual H bridge.
 The DC motor control function can independantly control 2 small DC motors.
 
 This program will gradually increase the speed of the 2 motors and then
 engage the brake when they are at full speed.
 The motors will then reverse direction and repeate the process.
 
 Written by Russell Cameron
 */
#include <microM.h>


void setup()
{ 
  microM.Setup();
  Serial.begin(19200); // set the serial port speed.
  microM.ircommand=10; // stopped.
}

void goStraight(int speed)
{
  if (speed == 0)
  {
    microM.Motors(0,0,1,1); // put on the brakes!
  } 
  else
  {
    microM.Motors(speed,speed,0,0);    // update motor controller
  }
}

void loop()
{
  static int leftSpeed=0;
  static int rightSpeed=0;
  const int minSpeed=25;
  const int FORWARDS_CODE = 2;
  const int LEFT_CODE=4;
  const int RIGHT_CODE=6;
  const int BACKWARDS_CODE=8;
  const int STOP_CODE=5;

  const int FORWARDS=500;
  const int REVERSE=-500;
  const int STOP=0;

  switch (microM.ircommand)
  {
  case STOP_CODE:
    Serial.println("Stopping");
    leftSpeed=STOP;
    rightSpeed=STOP;
    break;
  case FORWARDS_CODE:
    Serial.println("Forwards");
    leftSpeed=FORWARDS;
    rightSpeed=FORWARDS;
    break;
  case BACKWARDS_CODE:
    Serial.println("Backwards");
    leftSpeed=REVERSE;
    rightSpeed=REVERSE;
    break;
  case LEFT_CODE:
    Serial.println("Left");
    leftSpeed=STOP;
    rightSpeed=FORWARDS;
    break;
  case RIGHT_CODE:
    Serial.println("Right");
    leftSpeed=FORWARDS;
    rightSpeed=STOP;
    break;
  }
  microM.Motors(leftSpeed,rightSpeed,0,0);    // update motor controller

}

