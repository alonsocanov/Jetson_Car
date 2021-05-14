/*  Arduino DC Motor Control - PWM | H-Bridge | L298N */
#include "motor.hpp"
#include "utils.hpp"
#include <Servo.h>

// motor
#define enA 11
#define inA1 12
#define inA2 13

// servo motor
#define servo_pin 9

String data;

int ind1, ind2, ind3;
float speed, angle, y, x, time;
String speed_str, angle_str, time_str;

Motor motor = Motor(enA, inA1, inA2);
Servo servo_dir;

void setup()
{
    //I2C COmunication
    // initialize serial:
    Serial.begin(9600);

    servo_dir.attach(servo_pin);
    servo_dir.write(90);
    motor.stop();
}

void loop()
{
    if (Serial.available())
    {

        data = Serial.readStringUntil('\n');
        //finds location of first comma (,)
        ind1 = data.indexOf(',', 0);
        ind2 = data.indexOf(',', ind1 + 1);

        speed_str = data.substring(0, ind1);
        angle_str = data.substring(ind1 + 1, ind2);
        time_str = data.substring(ind2 + 1, data.length());

        speed = check_negative(speed_str) * 100.0;
        angle = check_negative(angle_str);
        time = check_negative(time_str);

        // y = y_speed(deg_to_rad(angle)) * speed;
        angle = angle + 90;
        motor.move(speed);
        servo_dir.write(angle);

        delay(time);
        Serial.println(data);
    }
    else
    {
        motor.stop();
    }
}
