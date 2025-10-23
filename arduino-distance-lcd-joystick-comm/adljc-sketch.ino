#include <LiquidCrystal.h>
#include "SR04.h"

// Define pins for the ultrasonic sensor
#define TRIG_PIN 12
#define ECHO_PIN 11

// DC Motor Pins (L293D Motor Driver)
#define ENABLE 5
#define DIRA 6
#define DIRB 4

// Joystick Pins
const int SW_pin = 2;  // Switch
const int X_pin = A1;  // X-axis
const int Y_pin = A2;  // Y-axis

// Communication Message Format
#define START_BYTE 0x70
#define STOP_BYTE 0x71

// Initialize the LCD object (adjust pin numbers based on your setup)
LiquidCrystal lcd(7, 8, 3, 13, 10, 9);

// Create SR04 object for ultrasonic sensor
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

// Variables for joystick and motor control
int xValue, yValue, swState, motorSpeed;
int rxButton, rxTilt, rxPot, rxA, rxB, rxC, rxD;
char txButton, txTilt, txPot, txA, txB, txC, txD;
char txBuffer[8] = {0, 0, 0, 0, 0, 0, 0, STOP_BYTE};
long distance;

void setup() {

  // set the digital pin as output:
  pinMode(1, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Initialize motor pins
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize joystick pins
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Distance: ");
  delay(1000);
}

void loop() {
  // Get the distance from the ultrasonic sensor
  distance = sr04.Distance();

  // Read joystick values
  xValue = analogRead(X_pin);  // Joystick X-axis
  yValue = analogRead(Y_pin);  // Joystick Y-axis
  swState = digitalRead(SW_pin);  // Joystick button state
  
  // Map X-axis value to motor speed (PWM 0-255)
  motorSpeed = map(xValue, 0, 1023, 0, 255);

  // Determine motor direction (Y-axis)
  if (yValue < 400) {
    // Move Forward
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
  } else if (yValue > 600) {
    // Move Backward
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
  } else {
    // Stop
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
    motorSpeed = 0;
  }

  // Set motor speed
  analogWrite(ENABLE, motorSpeed);

  // Prepare communication message
  byte message[9] = {
    START_BYTE,        // Start byte
    swState,           // Button state (1 or 0)
    0x00,              // Placeholder for Tilt Switch
    0x00,              // Placeholder for Potentiometer
    motorSpeed,        // Motor speed (PWM value)
    xValue / 4,        // X-axis (scaled to 0-255 for 1-byte communication)
    yValue / 4,        // Y-axis (scaled to 0-255 for 1-byte communication)
    0x00,              // Placeholder for another input
    STOP_BYTE          // Stop byte
  };

  // Transmit message over Serial
  Serial.write(message, 9);

  // Debugging output to Serial Monitor
  Serial.print("Joystick X: ");
  Serial.print(xValue);
  Serial.print(" | Joystick Y: ");
  Serial.print(yValue);
  Serial.print(" | Motor Speed: ");
  Serial.print(motorSpeed);
  Serial.print(" | Button: ");
  Serial.println(swState);

  // Update LCD display with distance
  lcd.setCursor(0, 1);
  lcd.print("                ");  // Clear previous value
  lcd.setCursor(0, 1);
  lcd.print(distance);    // Print the distance value
  lcd.print(" cm");       // Append " cm" to the distance

  // Wait for a second before updating
  delay(1000);
}
