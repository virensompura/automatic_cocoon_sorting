#include "HX711.h"

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

HX711 scale;
float calibration_factor = 0; // Initialize calibration factor to 0

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration");

  // Initialize load cell
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1.0); // Set the scale to 1 by default
  scale.tare(); // Reset the scale to zero

  Serial.println("Place a 1 kg weight on the load cell...");
}

void loop() {
  if (scale.is_ready()) {
    float reading = scale.get_units(); // Get the current reading from the load cell

    if (reading > 500) { // Wait for the weight to stabilize (about 2 seconds)
      calibration_factor = reading / 1000.0; // Calculate the calibration factor (1 kg = 1000 grams)
      Serial.print("Calibration factor: ");
      Serial.println(calibration_factor);
      Serial.println("Remove the weight from the load cell and press any key to continue...");
      while (!Serial.available()); // Wait for user input
      Serial.read(); // Clear the input buffer
      scale.set_scale(calibration_factor); // Set the calibration factor
      scale.tare(); // Reset the scale to zero
      Serial.println("Calibration complete");
      while (true); // Stop the program
    }
  }
  delay(100); // Wait for 100 milliseconds
}
