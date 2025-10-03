/*
  Stepper Motor Control via Serial Monitor
  ----------------------------------------
  This program allows the user to type commands like:
    rotate 180
    rotate -270
  into the Serial Monitor to rotate the motor accordingly.

  Materials:
    - Stepper motor
    - Motor driver (e.g., ULN2003, L293D)
    - Arduino Uno
    - Jumper wires

  Created by: IRASUBIZA SALY NELSON
  Date: October 2025
*/

#include <Stepper.h>

const int stepsPerRevolution = 200; // Adjust if your motor differs
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // Pins connected to motor driver

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper Motor Angle Control");
  Serial.println("Type commands like: rotate 90 or rotate -180");
  Serial.println("---------------------------------------------");
}

void loop() {
  // Check if there is serial data available
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Read command until Enter key
    input.trim();  // Remove spaces or line breaks

    // Check if command starts with 'rotate'
    if (input.startsWith("rotate")) {
      // Extract the angle value from the input string
      int spaceIndex = input.indexOf(' ');
      if (spaceIndex > 0) {
        String angleString = input.substring(spaceIndex + 1);
        float angle = angleString.toFloat();  // Convert angle text to number

        // Convert angle to steps
        int stepsToMove = (int)(angle * stepsPerRevolution / 360.0);

        // Display info to user
        Serial.print("Rotating ");
        Serial.print(angle);
        Serial.print(" degrees -> ");
        Serial.print(stepsToMove);
        Serial.println(" steps.");

        // Rotate the motor
        myStepper.setSpeed(60);  // Speed in RPM (adjust if needed)
        myStepper.step(stepsToMove);

        Serial.println("Rotation complete.\n");
      } else {
        Serial.println("❌ Invalid format. Use: rotate <angle>");
      }
    } else {
      Serial.println("❌ Unknown command. Try: rotate 180 or rotate -90");
    }
  }
}
