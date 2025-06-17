/*
  Wireless Control Example for ELEGOO Smart Robot Car Kit V4.0
  ------------------------------------------------------------
  This code enables wireless (serial) control of the robot car.
  The robot listens for simple serial commands to move forward, backward, left, or right.
  Useful for teaching how robots can be remotely controlled via Wi-Fi.

  For use in K-12 teacher training workshops.
  Robot platform: https://us.elegoo.com/products/elegoo-smart-robot-car-kit-v-4-0

  Serial Command Format:
    - Send a string in the format {n}, where n is:
        1 = Move Forward
        2 = Move Backward
        3 = Turn Right
        4 = Turn Left
    - Any other input will stop the robot.

  This code assumes a Wi-Fi is connected to the Arduino's hardware serial.

  Connections:
    - Standby Pin (STBY): Digital pin 3
    - Right Motor Power (PWMA): Digital pin 5 (PWM)
    - Right Motor Direction (DIRA): Digital pin 8
    - Left Motor Power (PWMB): Digital pin 6 (PWM)
    - Left Motor Direction (DIRB): Digital pin 7
*/

// Motor control pins
const int standby = 3;         // Standby control for motor driver (HIGH = enabled)
const int right_power = 5;     // PWM for right motor speed
const int right_direction = 8; // Direction for right motor
const int left_power = 6;      // PWM for left motor speed
const int left_direction = 7;  // Direction for left motor

void setup() {
  Serial.begin(9600);                // Start serial communication
  pinMode(standby, OUTPUT);
  digitalWrite(standby, HIGH);       // Enable motor driver
  pinMode(right_power, OUTPUT);
  pinMode(right_direction, OUTPUT);
  pinMode(left_power, OUTPUT);
  pinMode(left_direction, OUTPUT);
}

void loop() {
  Event();
  delay(10); // Short delay to avoid overwhelming the serial port
}

// Handles new serial commands and moves robot accordingly
void Event() {
  int status = SerialPortDataAnalysis();
  if (status) {
    switch (status) {
      case 1: // Move forward
        analogWrite(right_power, 100);
        digitalWrite(right_direction, HIGH);
        analogWrite(left_power, 100);
        digitalWrite(left_direction, HIGH);
        delay(1000);
        analogWrite(right_power, 0);
        analogWrite(left_power, 0);
        break;
      case 2: // Move backward
        analogWrite(right_power, 100);
        digitalWrite(right_direction, LOW);
        analogWrite(left_power, 100);
        digitalWrite(left_direction, LOW);
        delay(1000);
        analogWrite(right_power, 0);
        analogWrite(left_power, 0);
        break;
      case 3: // Turn right
        analogWrite(right_power, 100);
        digitalWrite(right_direction, HIGH);  
        analogWrite(left_power, 100);
        digitalWrite(left_direction, LOW);    
        delay(1000);
        analogWrite(right_power, 0);
        analogWrite(left_power, 0);
        break;
      case 4: // Turn left
        analogWrite(right_power, 100);
        digitalWrite(right_direction, LOW);  
        analogWrite(left_power, 100);
        digitalWrite(left_direction, HIGH);   
        delay(1000);
        analogWrite(right_power, 0);
        analogWrite(left_power, 0);
        break;
      default: // Stop
        analogWrite(right_power, 0);
        analogWrite(left_power, 0);
        delay(1000);
        break;
    }
  }
}

// Reads and parses serial data of the form {n}
int SerialPortDataAnalysis(void) {
  String SerialPortData = "";
  uint8_t c = "";
  if (Serial.available() > 0) {
    while (c != '}' && Serial.available() > 0) {
      c = Serial.read();
      SerialPortData += (char)c;
    }
    if (c == '}') {
      delay(50); // Small delay for stability
      // Extract command number between curly braces
      return atoi((char*)(SerialPortData.substring(1, SerialPortData.length() - 1).c_str()));
    }
  }
  return 0; // No valid data received
}

// Helper function (not used in this example)
uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}
