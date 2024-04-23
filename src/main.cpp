#include <Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include <ArduinoEigen.h>
#include <Pose.h>

Adafruit_MPU6050 mpu;

float z_rotation = 0.0;
float y_rotation = 0.0;
float z_rotation_old = 0.0;
float y_rotation_old = 0.0;
float z_integral = 0.0;
Servo thing1;
Servo thing2;
int thing1_pos = 90;
int thing2_pos = 90;
int tick = 0;
void setup(void)
{
  thing1.attach(23);
  thing2.attach(22);
  Serial.begin(115200);
  // while (!Serial)
  //   delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");
  thing1.write(thing1_pos);
  thing2.write(thing2_pos);
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
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println("");
  delay(100);
}

void loop()
{
  tick += 1;
  if (mpu.getMotionInterruptStatus() || 1)
  {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    /* Print out the values */
    z_rotation_old = z_rotation;
    y_rotation_old = y_rotation;
    z_rotation += g.gyro.z * 0.010;
    y_rotation += g.gyro.y * 0.010;
    // float setpoint = sin((float)tick / 50.0) * (PI / 4.0);

    float setpoint = 0.0;
    float error1 = setpoint - z_rotation;
    z_integral += error1 * 0.010;
    int effort1 = (int)floor(error1 * 15.0) + (int)floor(z_integral * 0.2);
    thing1_pos += effort1;
    thing1.write(thing1_pos);
    Serial.printf("y_rotation %.2f, z_rotation: %.2f\n", y_rotation, z_rotation);
    // setpoint = 0.0;
    // float error2 = setpoint - y_rotation;
    // int effort2 = -(int)floor(error2 * 20.0);
    // thing2_pos += effort2;
    thing2.write(90);
  }

  delay(10);
}