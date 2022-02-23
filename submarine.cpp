#include <Arduino.h>

#define joystick_threshold 400
#define negative_joystick_threshold -400

// * left joystick pins and codes
#define left_joystick_switch_pin 5
#define left_joystick_x_pin A0
#define left_joystick_y_pin A1

int left_joystick_x_position = 0;
int left_joystick_y_position = 0;
int left_joystick_switch_state = 0;
int left_joystick_mapped_x_position = 0;
int left_joystick_mapped_y_position = 0;

// * right joystick
#define right_joystick_switch_pin 6
#define right_joystick_x_pin A2
#define right_joystick_y_pin A3

int right_joystick_x_position = 0;
int right_joystick_y_position = 0;
int right_joystick_switch_state = 0;
int right_joystick_mapped_x_position = 0;
int right_joystick_mapped_y_position = 0;

// * motor ports
#define left_motor_port1 1
#define left_motor_port2 2
// #define right_motor_port1 0
// #define right_motor_port2 0

// * Controller plans
// Left up => Left x positive
// Left down => Left x negative
// Left left => Left y negative
// Left right => Left y positive

// Right up => Right x positive
// Right down => Right x negative
// Right left => Right y negative
// Right right => Right y positive

// When the sub needs to go forward

void setup() {
    pinMode(left_joystick_x_pin, INPUT);
    pinMode(left_joystick_y_pin, INPUT);
    pinMode(left_joystick_switch_pin, INPUT_PULLUP);

    pinMode(right_joystick_x_pin, INPUT);
    pinMode(right_joystick_y_pin, INPUT);
    pinMode(right_joystick_switch_pin, INPUT_PULLUP);

    pinMode(left_motor_port1, OUTPUT);
    pinMode(left_motor_port2, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    // getting joystick input for both joysticks
    left_joystick_x_position = analogRead(left_joystick_x_pin);
    left_joystick_y_position = analogRead(left_joystick_y_pin);
    left_joystick_switch_state = digitalRead(left_joystick_switch_pin);

    right_joystick_x_position = analogRead(right_joystick_x_pin);
    right_joystick_y_position = analogRead(right_joystick_y_pin);
    right_joystick_switch_state = digitalRead(right_joystick_switch_pin);

    // converting joystick's mapped position
    left_joystick_mapped_x_position = map(left_joystick_x_position, 0, 1023, 512, -512);
    left_joystick_mapped_y_position = map(left_joystick_y_position, 0, 1023, 512, -512);

    right_joystick_mapped_x_position = map(right_joystick_x_position, 0, 1023, 512, -512);
    right_joystick_mapped_y_position = map(right_joystick_y_position, 0, 1023, 512, -512);

    digitalWrite(left_motor_port1, LOW);
    digitalWrite(left_motor_port2, LOW);
    delay(2000);

    digitalWrite(left_motor_port1, HIGH);
    digitalWrite(left_motor_port2, LOW);

    delay(2000);
    digitalWrite(left_motor_port1, LOW);
    digitalWrite(left_motor_port2, LOW);
    delay(2000);

    digitalWrite(left_motor_port1, LOW);
    digitalWrite(left_motor_port2, HIGH);
    delay(2000);

    digitalWrite(left_motor_port1, LOW);
    digitalWrite(left_motor_port2, LOW);
    delay(2000);

    // if (negative_joystick_threshold < left_joystick_mapped_x_position && left_joystick_mapped_x_position < joystick_threshold) {
    //     digitalWrite(left_motor_port1, LOW);
    //     digitalWrite(left_motor_port2, LOW);
    // } else {
    //     // Joystick going forward
    //     if (left_joystick_mapped_x_position > joystick_threshold) {
    //         digitalWrite(left_motor_port1, HIGH);
    //         digitalWrite(left_motor_port2, LOW);
    //     } else if (left_joystick_mapped_x_position < negative_joystick_threshold) {
    //         digitalWrite(left_motor_port1, LOW);
    //         digitalWrite(left_motor_port2, HIGH);
    //     }
    // }

    // if (left_joystick_mapped_y_position > negative_joystick_threshold) {
    //     digitalWrite(left_motor_port1, LOW);
    //     digitalWrite(left_motor_port2, HIGH);
    //     digitalWrite(right_motor_port1, HIGH);
    //     digitalWrite(right_motor_port2, LOW);
    // }
    // if (left_joystick_mapped_y_position > joystick_threshold) {
    //     digitalWrite(left_motor_port1, HIGH);
    //     digitalWrite(left_motor_port2, LOW);
    //     digitalWrite(right_motor_port1, LOW);
    //     digitalWrite(right_motor_port2, HIGH);
    // }

    // printing the results
    Serial.print("left, x: " + String(left_joystick_mapped_x_position) + " y: " + String(left_joystick_mapped_y_position) + " state: " + String(left_joystick_switch_state) + " ");
    Serial.println("right, x: " + String(right_joystick_mapped_x_position) + " y: " + String(right_joystick_mapped_y_position) + " state: " + String(right_joystick_switch_state));
}
