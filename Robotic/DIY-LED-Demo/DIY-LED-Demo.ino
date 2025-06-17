/*
  DIY RGB LED Demo for Microelectronics Workshop
  ----------------------------------------------
  This code demonstrates how to control a single RGB LED (Neopixel) using the FastLED library.
  The color of the LED can be changed wirelessly (via serial commands), allowing students
  and teachers to explore digital output and color mixing.

  For K-12 teacher training workshops.
  Hardware: ELEGOO Smart Robot Car Kit V4.0 or any Arduino with a Neopixel-compatible RGB LED.
  LED Data Pin: Digital pin 4

  Serial Command Format:
    - Send a string in the format {n}, where n is:
        1 = Set LED to blue
        2 = Set LED to magenta
        3 = Set LED to cyan
        4 = Set LED to green
    - Sending any other number or command will leave the LED unchanged.

  Workshop Usage:
    - Use this code to show how code can control colors and lights.
    - Example: Send "{1}" via Serial Monitor to make the LED blue.

  Dependencies:
    - FastLED library (https://fastled.io/)
*/

#include "FastLED.h"

#define PIN_RBGLED 4     // The pin where the RGB LED data line is connected
#define NUM_LEDS 1       // Number of LEDs in the strip (here, just one)
CRGB leds[NUM_LEDS];     // FastLED LED array

void setup() {
  Serial.begin(9600);    // Start serial communication for wireless commands
  FastLED.addLeds<NEOPIXEL, PIN_RBGLED>(leds, NUM_LEDS); // Initialize LED
  FastLED.setBrightness(20);   // Set LED brightness (0-255)
}

void loop() {
  Event();               // Check and process serial commands
  delay(10);             // Short delay to avoid overwhelming the serial port
}

// Handle incoming serial commands and set LED color
void Event() {
  int status = SerialPortDataAnalysis();
  if (status) {
    switch (status) {
      case 1: FastLED.showColor(Color(0, 0, 255)); break;        // Blue
      case 2: FastLED.showColor(Color(255, 0, 255)); break;      // Magenta
      case 3: FastLED.showColor(Color(0, 255, 255)); break;      // Cyan
      case 4: FastLED.showColor(Color(0, 255, 0)); break;        // Green
      default: break; // Ignore unknown commands
    }
  }
}

// Reads serial data of the form {n} and returns the number n
int SerialPortDataAnalysis(void) {
  String SerialPortData = "";
  uint8_t c = "";
  if (Serial.available() > 0) {
    while (c != '}' && Serial.available() > 0) {
      c = Serial.read();
      SerialPortData += (char)c;
    }
    if (c == '}') {
      delay(50); // Allow input to stabilize
      // Extract the number between curly braces
      return atoi((char*)(SerialPortData.substring(1, SerialPortData.length() - 1).c_str()));
    }
  }
  return 0; // No valid command received
}

// Helper function to convert RGB values to a 24-bit color
uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}
