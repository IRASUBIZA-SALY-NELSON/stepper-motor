#include <Stepper.h>
const int stepsPerRevolution = 2048; // for 28BYJ-48 (half-step mode)
const int in1Pin = 8;
const int in2Pin = 9;
const int in3Pin = 10;
const int in4Pin = 11;
Stepper myStepper(stepsPerRevolution, in1Pin, in3Pin, in2Pin, in4Pin);
float stepsPerDegree = stepsPerRevolution / 360.0;
void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(10); // RPM
  Serial.println("Enter command like: rotate 90 (positive = CW, negative = CCW)");
}
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.startsWith("rotate")) {
      // Extract angle after "rotate"
      int angle = input.substring(6).toInt();
      // Convert to steps
      long stepsToMove = angle * stepsPerDegree;
      // Move motor relative to current position
      myStepper.step(stepsToMove);
      // Debug info
      Serial.print("Rotated ");
      Serial.print(angle);
      Serial.println(" degrees");
    }
  }
}
