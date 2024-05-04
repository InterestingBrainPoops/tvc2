#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include <ArduinoEigen.h>
#include <Pose.h>
#include <Controller.h>
#include <ReactionWheel.h>
#include <Gimbal.h>

ReactionWheel<15> wheel;
void setup()
{
  wheel = ReactionWheel<15>(22, 23, 150, 255);

  Serial.begin(115200);
}

void loop()
{

  wheel.set_speed(0.2);
  Serial.printf(">rpm:%.2f\n", wheel.get_rpm());

  delay(10);
  // for (int x = 125; x > 125; x--)
  // {
  //   analogWrite(23, x);
  //   delay(15);
  // }
}
