#include <Arduino.h>
#include <Servo.h>

#define FREEDOM_DEGREES 10
#define MAX_SERVO_RANGE 180
// 1 - 180 => 1 - 100%
Servo thumb_finger;
Servo index_finger;
Servo middle_finger;
Servo ring_finger;
Servo pinky_finger;
Servo wrist;

const int pos_thumb;
const int pos_index;
const int pos_middle;
const int pos_ring;
const int pos_pinky;
const int pos_wrist;

const int pin_thumb = 3;
const int pin_index = 5;
const int pin_middle = 6;
const int pin_ring = 9;
const int pin_pinky = 10;
const int pin_wrist = 11;

int convert_percentage_to_pos(int percentage_value);
int convert_pos_to_freedom_degree(int pos_value);
void execute_movement(int degree_value, Servo motor_to_move);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    thumb_finger.attach(pin_thumb);
    index_finger.attach(pin_index);
    middle_finger.attach(pin_middle);
    ring_finger.attach(pin_ring);
    pinky_finger.attach(pin_pinky);
    wrist.attach(pin_wrist);
}

void loop()
{
    // put your main code here, to run repeatedly:
    pinky_finger.write(90);
    delay(100000);
}

int convert_percentage_to_pos(int percentage_value)
{
    int max_percentage = 100;
    return (percentage_value * MAX_SERVO_RANGE) / max_percentage;
}

int convert_pos_to_freedom_degree(int pos_value)
{
    int available_freedom_degrees = MAX_SERVO_RANGE / FREEDOM_DEGREES;
    int actual_pos = available_freedom_degrees;
    int actual_degree = 1;
    for (int i = 1; i <= FREEDOM_DEGREES; i++)
    {
        if (pos_value < actual_pos)
        {
            actual_degree = i;
            break;
        }
        else
        {
            actual_pos += available_freedom_degrees;
        }
    }
    return actual_degree;
}

void execute_movement(int degree_value, Servo motor_to_move)
{
    int available_freedom_degrees = MAX_SERVO_RANGE / FREEDOM_DEGREES;
    // extract total position with the average value of the
    // range according to the last freedom degree
    int pos_to_move = ((available_freedom_degrees * degree_value) - (available_freedom_degrees / 2));
    motor_to_move.write(pos_to_move);
}