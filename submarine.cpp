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
#define left_motor_port1 7
#define left_motor_port2 2
#define right_motor_port1 4
#define right_motor_port2 3
#define updown_motor_port1 8
#define updown_motor_port2 9

// * Controller plans
// Left up => Left x positive
// Left down => Left x negative
// Left left => Left y negative
// Left right => Left y positive

// Right up => Right x positive
// Right down => Right x negative
// Right left => Right y negative
// Right right => Right y positive

void setup() {
    pinMode(left_joystick_x_pin, INPUT);
    pinMode(left_joystick_y_pin, INPUT);
    pinMode(left_joystick_switch_pin, INPUT_PULLUP);

    pinMode(right_joystick_x_pin, INPUT);
    pinMode(right_joystick_y_pin, INPUT);
    pinMode(right_joystick_switch_pin, INPUT_PULLUP);

    pinMode(left_motor_port1, OUTPUT);
    pinMode(left_motor_port2, OUTPUT);
    pinMode(right_motor_port1, OUTPUT);
    pinMode(right_motor_port2, OUTPUT);
    pinMode(updown_motor_port1, OUTPUT);
    pinMode(updown_motor_port2, OUTPUT);

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

    if (left_joystick_mapped_x_position < negative_joystick_threshold || left_joystick_mapped_x_position > joystick_threshold ||
        left_joystick_mapped_y_position < negative_joystick_threshold || left_joystick_mapped_y_position > joystick_threshold) {
        // * Capture all 8 different movements a left joystick could be. Starting from the bottom.
        if (left_joystick_mapped_y_position < negative_joystick_threshold && left_joystick_mapped_x_position > joystick_threshold) {
            digitalWrite(left_motor_port1, HIGH);
            digitalWrite(left_motor_port2, LOW);
            digitalWrite(right_motor_port1, HIGH);
            digitalWrite(right_motor_port2, LOW);
            // * joystick going left up
            Serial.println("left going left up");
        } else if (left_joystick_mapped_y_position > joystick_threshold && left_joystick_mapped_x_position > joystick_threshold) {
            digitalWrite(left_motor_port1, LOW);
            digitalWrite(left_motor_port2, HIGH);
            digitalWrite(right_motor_port1, HIGH);
            digitalWrite(right_motor_port2, LOW);
            // * joystick going right up
            Serial.println("left going right up");
        } else if (left_joystick_mapped_y_position < negative_joystick_threshold && left_joystick_mapped_x_position < negative_joystick_threshold) {
            digitalWrite(left_motor_port1, HIGH);
            digitalWrite(left_motor_port2, LOW);
            digitalWrite(right_motor_port1, LOW);
            digitalWrite(right_motor_port2, HIGH);
            // * joystick going left down
            Serial.println("left going left down");
        } else if (left_joystick_mapped_y_position > joystick_threshold && left_joystick_mapped_x_position < negative_joystick_threshold) {
            digitalWrite(left_motor_port1, LOW);
            digitalWrite(left_motor_port2, HIGH);
            digitalWrite(right_motor_port1, LOW);
            digitalWrite(right_motor_port2, HIGH);
            // * joystick going right down
            Serial.println("left going right down");
        } else if (left_joystick_mapped_x_position > joystick_threshold) {
            digitalWrite(left_motor_port1, HIGH);
            digitalWrite(left_motor_port2, LOW);
            digitalWrite(right_motor_port1, HIGH);
            digitalWrite(right_motor_port2, LOW);
            // * joystick going only up
            Serial.println("left going only up");
        } else if (left_joystick_mapped_x_position < negative_joystick_threshold) {
            digitalWrite(left_motor_port1, LOW);
            digitalWrite(left_motor_port2, HIGH);
            digitalWrite(right_motor_port1, LOW);
            digitalWrite(right_motor_port2, HIGH);
            // * joystick going only down
            Serial.println("left going only down");
        } else if (left_joystick_mapped_y_position < negative_joystick_threshold) {
            digitalWrite(left_motor_port1, HIGH);
            digitalWrite(left_motor_port2, LOW);
            digitalWrite(right_motor_port1, LOW);
            digitalWrite(right_motor_port2, HIGH);
            // * joystick going only left
            Serial.println("left going only left");
        } else if (left_joystick_mapped_y_position > joystick_threshold) {
            digitalWrite(left_motor_port1, LOW);
            digitalWrite(left_motor_port2, HIGH);
            digitalWrite(right_motor_port1, HIGH);
            digitalWrite(right_motor_port2, LOW);
            // * joystick going only right
            Serial.println("left going only right");
        }
    } else {
        Serial.println("waiting for left joystick move");
        digitalWrite(left_motor_port1, LOW);
        digitalWrite(left_motor_port2, LOW);
        digitalWrite(right_motor_port1, LOW);
        digitalWrite(right_motor_port2, LOW);
    }

    if (right_joystick_mapped_x_position < negative_joystick_threshold || right_joystick_mapped_x_position > joystick_threshold ||
        right_joystick_mapped_y_position < negative_joystick_threshold || right_joystick_mapped_y_position > joystick_threshold) {
        if (right_joystick_mapped_x_position > joystick_threshold) {
            digitalWrite(updown_motor_port1, HIGH);
            digitalWrite(updown_motor_port2, LOW);
            Serial.println("right going up");
        } else if (right_joystick_mapped_x_position < negative_joystick_threshold) {
            digitalWrite(updown_motor_port1, LOW);
            digitalWrite(updown_motor_port2, HIGH);
            Serial.println("right going down");
        }
    } else {
        digitalWrite(updown_motor_port1, LOW);
        digitalWrite(updown_motor_port2, LOW);
        Serial.println("waiting for right joystick move");
    }
}
