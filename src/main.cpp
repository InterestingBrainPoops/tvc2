#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include <ArduinoEigen.h>
#include <Pose.h>
#include <Controller.h>

#include <Gimbal.h>
using Eigen::Vector3f;

Adafruit_MPU6050 mpu;

Vector3f heading{0.0, 0.0, 0.0};
Vector3f previous_reading{0.0, 0.0, 0.0};
Vector3f offset{0.0, 0.0, 0.0};
Gimbal gimbal;
int tick = 0;
int timestep = 10;
Controller pitch_pid;
Controller yaw_pid;

void setup(void)
{

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pitch_pid = Controller(2.0, 15.0, 0.0, (float)timestep / 1000.0);
  yaw_pid = Controller(2.0, 15.0, 0.0, (float)timestep / 1000.0);

  gimbal = Gimbal(21, 22, -13, -3, 30);

  Serial.begin(115200);
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // setupt motion detection

  Serial.println("");

  delay(100);
  for (int n = 0; n < 50; n++)
  {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Vector3f gyro_reading{g.gyro.x, g.gyro.y, g.gyro.z};
    offset += gyro_reading;
    delay(10);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  offset = offset / 50.0;
}

void loop()
{
  tick += 1;

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Vector3f gyro_reading{g.gyro.x, g.gyro.y, g.gyro.z};

  Vector3f compensated_reading = ((gyro_reading - offset) + previous_reading) / 2.0;
  // previous_reading = gyro_reading - offset;
  heading += compensated_reading * ((float)timestep / 1000.0);
  Serial.printf(">pitch servo angle:%d\n", gimbal.get_pitch());
  Serial.printf(">yaw servo angle:%d\n", gimbal.get_yaw());
  Serial.printf(">integrated pitch:%.2f\n", heading.y());
  Serial.printf(">integrated yaw:%.2f\n", heading.x());
  Serial.printf(">avg pitch rate:%.2f\n", compensated_reading.y());
  Serial.printf(">avg yaw rate:%.2f\n", compensated_reading.x());

  Serial.printf(">raw pitch rate:%.2f\n", (gyro_reading - offset).y());
  Serial.printf(">raw yaw rate:%.2f\n", (gyro_reading - offset).x());
  pitch_pid.update(heading.y());
  yaw_pid.update(heading.x());
  gimbal.set_yaw(-(int)(degrees(yaw_pid.get(0.0)) * 2.25));
  // gimbal.set_yaw(0.0);
  gimbal.set_pitch((int)(degrees(pitch_pid.get(0.0)) * 2.25));

  delay(timestep);
}
