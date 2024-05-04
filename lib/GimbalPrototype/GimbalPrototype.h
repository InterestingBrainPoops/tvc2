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
class GimbalPrototype
{
private:
    Adafruit_MPU6050 mpu;

    Vector3f heading{0.0, 0.0, 0.0};
    Vector3f previous_reading{0.0, 0.0, 0.0};
    Vector3f offset{0.0, 0.0, 0.0};
    Gimbal gimbal;
    int tick = 0;
    int timestep = 10;
    Controller pitch_pid;
    Controller yaw_pid;

public:
    void setup()
    {
        // setup the enable led and turn it off
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);

        // configure the pitch and yaw pid loops with some bs constants and the dt
        pitch_pid = Controller(1.25, 15.0, 0.0, (float)timestep / 1000.0);
        yaw_pid = Controller(2.0, 15.0, 0.0, (float)timestep / 1000.0);

        // define the gimbal with some zeros and the pin defenitions for the zeros
        gimbal = Gimbal(21, 22, -13, 16, 30);

        Serial.begin(115200);

        // loop until we get an IMU
        if (!mpu.begin())
        {
            while (1)
            {
                delay(10);
            }
        }

        // delay to make sure that the imu finishes some internal configs (if any)
        delay(100);
        // get 50 samples to average over to get an idea of what "zero" velocity is like in terms of random noise and bs
        for (int n = 0; n < 50; n++)
        {
            sensors_event_t a, g, temp;
            mpu.getEvent(&a, &g, &temp);
            Vector3f gyro_reading{g.gyro.x, g.gyro.y, g.gyro.z};
            offset += gyro_reading;
            delay(10);
        }
        offset = offset / 50.0;
        // turn on the enable LED
        digitalWrite(LED_BUILTIN, HIGH);
    }

    void update()
    {
        tick += 1;

        // grab the acceleration, gyroscope, and temp values from the mpu
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        // "cast" the gyro readings into a usable vector: yaw, pitch, roll, (x,y,z)
        Vector3f gyro_reading{g.gyro.x, g.gyro.y, g.gyro.z};
        // compensate for the offset found during zeroing
        Vector3f compensated_reading = (gyro_reading - offset);
        // numerical integrate the velocity
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
        gimbal.set_pitch((int)(degrees(pitch_pid.get(0.0)) * 2.25));

        delay(timestep);
    }
};
