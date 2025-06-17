//Sensor Pins
const int leftSensorPin = A0;
const int middleSensorPin = A1;
const int rightSensorPin = A2;

// Motor control pins
const int right_power = 5;
const int left_power = 6;
const int left_direction = 7;
const int right_direction = 8;
const int stby = 3;

// Speed settings
const int baseSpeed = 100;
const int turnSpeed = 75;
const int searchSpeed = 75;

// Line detection threshold
const int threshold = 500;

// Track last known direction: -1 = left, 1 = right
int lastDirection = 1; // Default: search to right

void setup() {
  pinMode(left_power, OUTPUT);
  pinMode(right_power, OUTPUT);
  pinMode(left_direction, OUTPUT);
  pinMode(right_direction, OUTPUT);
  pinMode(stby, OUTPUT);
  digitalWrite(stby, HIGH); // Enable motor driver

  Serial.begin(9600);
}

void loop() {
  int leftValue = analogRead(leftSensorPin);
  int middleValue = analogRead(middleSensorPin);    // This just reads the sensor
  int rightValue = analogRead(rightSensorPin);

  Serial.print("L: "); Serial.print(leftValue);
  Serial.print(" M: "); Serial.print(middleValue);    // This Prints the sensor data to the Serial Moniter
  Serial.print(" R: "); Serial.println(rightValue);

  bool leftOnLine = (leftValue > threshold);
  bool middleOnLine = (middleValue > threshold);    // This function just assigns true or false to each of the cases
  bool rightOnLine = (rightValue > threshold);

  if (middleOnLine) {
    moveForward(baseSpeed, baseSpeed);
    lastDirection = 0;    // This just sets the direction back to 0 only when the middle sensor is centered on the line
  } else if (leftOnLine) {
    moveForward(turnSpeed, baseSpeed);
    if (lastDirection == 0) lastDirection = -1; // Set's only if not centered
  } else if (rightOnLine) {
    moveForward(baseSpeed, turnSpeed);
    if (lastDirection == 0) lastDirection = 1; // Set's only if not centered
  } else {
    if (lastDirection == -1) {
      spinLeft();   // This searches in the last known direction of the line depending on the clauses above
    } else {
      spinRight();
    }
  }

  delay(50);
}

void moveForward(int leftSpeed, int rightSpeed) {
  digitalWrite(left_direction, 1);
  digitalWrite(right_direction, 1);
  analogWrite(left_power, 75);
  analogWrite(right_power, 75);
}

void spinLeft() {
  digitalWrite(left_direction, 0);
  digitalWrite(right_direction, 1);
  analogWrite(left_power, searchSpeed);
  analogWrite(right_power, searchSpeed);
}

void spinRight() {
  digitalWrite(left_direction, 1);
  digitalWrite(right_direction, 0);
  analogWrite(left_power, searchSpeed);
  analogWrite(right_power, searchSpeed);
}

