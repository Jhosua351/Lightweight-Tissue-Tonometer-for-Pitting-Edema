#include <Wire.h>       // Include I2C communication library
#include <FDC1004.h>    // Include library for FDC1004 capacitive sensor

/******************************************************************************************/

/*********** FDC1004 **********/

// Define I2C pins for XIAO ESP32S3 board
const int SDA_PIN = SDA;  // GPIO5 = SDA line
const int SCL_PIN = SCL;  // GPIO6 = SCL line

// Variables for implementing a digital low-pass Butterworth filter
float yk1 = 0; // Previous output sample y[k-1]
float xk1 = 0; // Previous input sample x[k-1]

// Filter coefficients (pre-computed for cutoff = 10 Hz, sampling = 100 Hz)
const float a = 0.72848950367272; 
const float b = 0.13575752481636; 

// Create FDC1004 object, set sampling rate to 100 Hz
FDC1004 fdc(FDC1004_100HZ);

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud

  // Initialize I2C bus with defined pins
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000); // Set I2C clock speed to 100 kHz

  delay(50); // Small delay to stabilize communication

  // No explicit begin() for FDC1004 library; Wire initialization is sufficient
  Serial.println("FDC ready (Wire initialized).");
}

void loop() {
  // Read capacitance from channel CIN1
  // Returned value is in femtofarads (fF) as int32_t
  float c_fF = fdc.getCapacitance(0); // Channel 0 = CIN1

  // Convert femtofarads to picofarads (1 pF = 1000 fF)
  float pf = c_fF / 1000;

  // Apply digital low-pass filter:
  // y[k] = a*y[k-1] + b*x[k] + b*x[k-1]
  float yk_c = a * yk1 + b * pf + b * xk1;

  /* Example calibration reference:
     Contact detected around 11.4 pF
     Printing format: fixed values + filtered capacitance
  */
  Serial.print(9);          // Example constant (could be marker or ID)
  Serial.print(", ");
  Serial.print(11);         // Example constant (could be marker or ID)
  Serial.print(", ");
  Serial.println(yk_c, 2);  // Print filtered capacitance with 2 decimals

  // Update previous samples for next iteration
  xk1 = pf;   // Store current input
  yk1 = yk_c; // Store current output

  delay(10); // Delay ~10 ms → loop runs ~100 Hz
}
