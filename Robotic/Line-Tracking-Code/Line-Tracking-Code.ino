/*
  Line Tracking Example for ELEGOO Smart Robot Car Kit V4.0
  ---------------------------------------------------------
  This code enables the robot to follow a black line on a light surface using three IR sensors.
  The robot will adjust its movement to stay on the line, demonstrating basic sensor-based navigation.

  For K-12 teacher training workshops.
  Robot platform: https://us.elegoo.com/products/elegoo-smart-robot-car-kit-v-4-0

  Hardware:
    - Left IR Sensor:    A0
    - Middle IR Sensor:  A1
    - Right IR Sensor:   A2
    - Motor driver and connections as in other examples

  How it works:
    - Each sensor returns a value: high value = sees dark (line), low value = sees light (floor)
    - If the middle sensor is on the line, go straight.
    - If the left or right sensor is on the line, adjust direction.
    - If no sensor sees the line, spin in the last known direction to search.

  Workshop Use:
    - Use this code to teach how robots sense their environment and make decisions.
    - Open Serial Monitor to view real-time sensor readings.

  Dependencies:
    - None beyond standard Arduino libraries.
*/

// Sensor Pins
const int leftSensorPin = A0;
const int middleSensorPin = A1;
const int rightSensorPin = A2;

// Motor control pins
const int right_power = 5;        // PWM for right motor speed
const int left_power = 6;         // PWM for left motor speed
const int left_direction = 7;     // Direction for left motor
const int right_direction = 8;    // Direction for right motor
const int stby = 3;               // Standby pin for motor driver

// Speed settings
const int baseSpeed = 100;        // Normal forward speed
const int turnSpeed = 75;         // Speed for turning
const int searchSpeed = 75;       // Speed for searching when line lost

// Line detection threshold (adjust if needed)
const int threshold = 500;        // Value above which sensor detects the line

// Track last known direction: -1 = left, 1 = right, 0 = centered
int lastDirection = 1; // Default: search to right

void setup() {
  pinMode(left_power, OUTPUT);
  pinMode(right_power, OUTPUT);
  pinMode(left_direction, OUTPUT);
  pinMode(right_direction, OUTPUT);
  pinMode(stby, OUTPUT);
  digitalWrite(stby, HIGH); // Enable motor driver

  Serial.begin(9600);       // For sensor debugging
}

void loop() {
  // Read the sensor values
  int leftValue = analogRead(leftSensorPin);
  int middleValue = analogRead(middleSensorPin);
  int rightValue = analogRead(rightSensorPin);

  // Print sensor readings to Serial Monitor for debugging
  Serial.print("L: "); Serial.print(leftValue);
  Serial.print(" M: "); Serial.print(middleValue);
  Serial.print(" R: "); Serial.println(rightValue);

  // Determine if each sensor is on the line
  bool leftOnLine = (leftValue > threshold);
  bool middleOnLine = (middleValue > threshold);
  bool rightOnLine = (rightValue > threshold);

  // Decision logic for line tracking
  if (middleOnLine) {
    // Go straight if middle sensor is on the line
    moveForward(baseSpeed, baseSpeed);
    lastDirection = 0; // Centered
  } else if (leftOnLine) {
    // Turn left if left sensor is on the line
    moveForward(turnSpeed, baseSpeed);
    if (lastDirection == 0) lastDirection = -1;
  } else if (rightOnLine) {
    // Turn right if right sensor is on the line
    moveForward(baseSpeed, turnSpeed);
    if (lastDirection == 0) lastDirection = 1;
  } else {
    // If line is lost, spin in last known direction
    if (lastDirection == -1) {
      spinLeft();
    } else {
      spinRight();
    }
  }

  delay(50); // Small delay for stability
}

// Drive both motors forward at different speeds (for turning)
void moveForward(int leftSpeed, int rightSpeed) {
  digitalWrite(left_direction, HIGH);
  digitalWrite(right_direction, HIGH);
  analogWrite(left_power, leftSpeed);
  analogWrite(right_power, rightSpeed);
}

// Spin in place to the left (search for line)
void spinLeft() {
  digitalWrite(left_direction, LOW);
  digitalWrite(right_direction, HIGH);
  analogWrite(left_power, searchSpeed);
  analogWrite(right_power, searchSpeed);
}

// Spin in place to the right (search for line)
void spinRight() {
  digitalWrite(left_direction, HIGH);
  digitalWrite(right_direction, LOW);
  analogWrite(left_power, searchSpeed);
  analogWrite(right_power, searchSpeed);
}
