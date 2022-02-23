#include <Arduino.h>

// left joystick pins and codes
#define left_joystick_switch_pin 5
#define left_joystick_x_pin A0
#define left_joystick_y_pin A1

int left_joystick_x_position = 0;
int left_joystick_y_position = 0;
int left_joystick_switch_state = 0;
int left_joystick_mapped_x_position = 0;
int left_joystick_mapped_y_position = 0;

// right joystick
#define right_joystick_switch_pin 6
#define right_joystick_x_pin A2
#define right_joystick_y_pin A3

int right_joystick_x_position = 0;
int right_joystick_y_position = 0;
int right_joystick_switch_state = 0;
int right_joystick_mapped_x_position = 0;
int right_joystick_mapped_y_position = 0;

void setup() {
    pinMode(left_joystick_x_pin, INPUT);
    pinMode(left_joystick_y_pin, INPUT);
    pinMode(left_joystick_switch_pin,INPUT_PULLUP);

    pinMode(right_joystick_x_pin, INPUT);
    pinMode(right_joystick_y_pin, INPUT);
    pinMode(right_joystick_switch_pin, INPUT_PULLUP);

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

    // printing the results
    Serial.print("left, x: " + String(left_joystick_mapped_x_position) + " y: " + String(left_joystick_mapped_y_position) + " state: " + String(left_joystick_switch_state) + " ");
    Serial.println("right, y: " + String(right_joystick_mapped_x_position) + " y: " + String(right_joystick_mapped_y_position) + " state: " + String(right_joystick_switch_state));
}
