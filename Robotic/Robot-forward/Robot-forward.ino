/*
  Robot Forward Motion Example
  ----------------------------
  This code demonstrates how to control the movement of the ELEGOO Smart Robot Car Kit V4.0.
  The robot will move forward and stop, in a repeating cycle.
  Use this as a teaching tool for basic motor and direction control.

  Connections:
    - Standby Pin (STBY): Digital pin 3
    - Right Motor Power (PWMA): Digital pin 5 (PWM)
    - Right Motor Direction (DIRA): Digital pin 8
    - Left Motor Power (PWMB): Digital pin 6 (PWM)
    - Left Motor Direction (DIRB): Digital pin 7

  For more information, see: https://us.elegoo.com/products/elegoo-smart-robot-car-kit-v-4-0
*/

// Define motor control pins
const int standby = 3;         // Standby control for motor driver
const int right_power = 5;     // PWM control for right motor speed
const int right_direction = 8; // Direction control for right motor
const int left_power = 6;      // PWM control for left motor speed
const int left_direction = 7;  // Direction control for left motor

void setup() {
  // Set motor control pins as outputs
  pinMode(standby, OUTPUT);
  digitalWrite(standby, HIGH); // Enable motor driver

  pinMode(right_power, OUTPUT);
  pinMode(right_direction, OUTPUT);
  pinMode(left_power, OUTPUT);
  pinMode(left_direction, OUTPUT);
}

void loop() {
  // Move forward
  analogWrite(right_power, 100);         // Set right motor speed (0-255)
  digitalWrite(right_direction, HIGH);   // Set right motor to forward
  analogWrite(left_power, 100);          // Set left motor speed (0-255)
  digitalWrite(left_direction, HIGH);    // Set left motor to forward
  delay(1000);                           // Move forward for 1 second

  // Stop motors
  analogWrite(right_power, 0);
  analogWrite(left_power, 0);
  delay(1000);                           // Stay stopped for 1 second
}
