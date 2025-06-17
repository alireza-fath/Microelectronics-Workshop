// Line_Tracking_Sensor_Reading.ino
// Example Arduino code for reading analog values from three line tracking sensors
// Designed for use in hands-on microelectronics and robotics workshops
// For the ELEGOO Smart Robot Car Kit V4.0 or similar hardware
// Reads sensor values and prints them to the Serial Monitor for debugging and classroom demonstration

// Define the analog input pins for the left, middle, and right IR sensors
const int leftIRpin = A2;    // Left line-tracking sensor connected to analog pin A2
const int middleIRpin = A1;  // Middle line-tracking sensor connected to analog pin A1
const int rightIRpin = A0;   // Right line-tracking sensor connected to analog pin A0

void setup() {
  // Initialize serial communication at 9600 bits per second.
  // This allows you to see sensor data in the Arduino Serial Monitor.
  Serial.begin(9600);
}

void loop() {
  delay(50); // Small delay for stability (reduce data spam and allow signal settling)

  // Read analog values from each sensor
  int L_IR = analogRead(leftIRpin);      // Read left sensor
  int R_IR = analogRead(rightIRpin);     // Read right sensor
  int M_IR = analogRead(middleIRpin);    // Read middle sensor

  // Print the sensor values to Serial Monitor in a readable format
  Serial.print("Left: ");
  Serial.print(L_IR);
  Serial.print("   ||   Middle: ");
  Serial.print(M_IR);
  Serial.print("   ||   Right: ");
  Serial.println(R_IR);

  // The output will look like:
  // Left: 865   ||   Middle: 400   ||   Right: 900
  // Use these readings to calibrate your sensors or debug your line-following robot
}
