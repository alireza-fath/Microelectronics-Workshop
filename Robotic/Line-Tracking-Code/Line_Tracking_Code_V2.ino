/*
  Line Tracking Example for ELEGOO Smart Robot Car Kit V4.0
  ---------------------------------------------------------
  This code enables the robot to follow a black line on a light surface using three IR sensors.
  The robot uses sensor readings to adjust its movement and stay on the line, demonstrating basic sensor-based navigation.

  For K-12 microelectronics and robotics workshops.
  Robot platform: https://us.elegoo.com/products/elegoo-smart-robot-car-kit-v-4-0

  Hardware Connections:
    - Left IR Sensor:    A2
    - Middle IR Sensor:  A1
    - Right IR Sensor:   A0
    - Motor driver and other connections as in ELEGOO V4.0 examples

  How it works:
    - Each IR sensor returns a value: high value = sees dark (line), low value = sees light (floor)
    - If the middle sensor is on the line, the robot moves straight.
    - If only the left or right sensor is on the line, the robot turns to correct its path.
    - If no sensor sees the line, the robot spins in the last known direction to search for the line.

  Workshop Use:
    - Use this code to illustrate how robots can sense their environment and make decisions.
    - Open Serial Monitor to view real-time sensor readings.

  Dependencies:
    - Standard Arduino libraries only.
*/

// Sensor Pins
const int leftIRpin= A2;
const int middleIRpin = A1;
const int rightIRpin = A0;

// Motor Control Pins
const int standby = 3;
const int right_power = 5;
const int right_direction = 8;
const int left_power = 6;
const int left_direction = 7;

// Control Variables
int memory = 0; // +1 = right, -1 = left
int threshold = 500;
int baseSpeed = 75;
int searchSpeed = 75;
int turnSpeed = 125;

void setup() {
  // Initialize serial communication and motor driver pins
  Serial.begin(9600);
  pinMode(standby, OUTPUT);
  digitalWrite(standby, HIGH);
  pinMode(right_power, OUTPUT);
  pinMode(right_direction, OUTPUT);
  pinMode(left_power, OUTPUT);
  pinMode(left_direction, OUTPUT);
}

void loop() {
  delay(100);
  // Read sensor values
  int L_IR = analogRead(leftIRpin);
  int R_IR = analogRead(rightIRpin);
  int M_IR = analogRead(middleIRpin);

  // Determine if each sensor is on the line
  bool leftOnLine = (L_IR > threshold);
  bool rightOnLine = (R_IR  > threshold);
  bool middleOnLine = (M_IR  > threshold);

  // Decision logic for line tracking
  if (middleOnLine){
    moveForward(baseSpeed, baseSpeed);
  }
  else if (rightOnLine){
    moveForward(turnSpeed, baseSpeed);
    memory = 1; 
  }
  else if (leftOnLine){
    moveForward(baseSpeed, turnSpeed);
    memory = -1; 
  }
  else {
    // If line is lost, spin in last known direction
    if (memory==1){
      spinRight();
    }
    else if (memory==-1){
      spinLeft();
    }
  }

  // Print sensor readings for debugging
  Serial.print("Left:");
  Serial.print(L_IR);
  Serial.print("   ||   Middle:");
  Serial.print(M_IR);
  Serial.print("   ||   Right:");
  Serial.println(R_IR);
}

// Move both motors forward with independent speeds
void moveForward(int leftSpeed, int rightSpeed) {
  digitalWrite(left_direction, HIGH);
  digitalWrite(right_direction, HIGH);
  analogWrite(right_power, rightSpeed);
  analogWrite(left_power, leftSpeed);
}

// Spin in place to the right (search for line)
void spinRight() {
  digitalWrite(left_direction, LOW);
  digitalWrite(right_direction, HIGH);
  analogWrite(right_power, searchSpeed);
  analogWrite(left_power, searchSpeed);
}

// Spin in place to the left (search for line)
void spinLeft() {
  digitalWrite(left_direction, HIGH);
  digitalWrite(right_direction, LOW);
  analogWrite(right_power, searchSpeed);
  analogWrite(left_power, searchSpeed);
}