// TCND5000 Calibration Script

// Define analog input pin connected to TCND5000 sensor
const int DISP_OUT = A8;

/* ---------------- Low-pass filter parameters ---------------- */

// Sampling period (in seconds). Here: 0.0001 s = 100 µs → 10 kHz sampling rate
float sample_period = 0.0001; 

// Desired cutoff frequency for the low-pass filter (Hz)
float cutOff_frequency = 2;

// Sampling rate derived from sample period
float sampling_rate = 1 / sample_period;

// Exponential smoothing factor for low-pass filter
// Formula: exp(-2π * fc / fs), where fc = cutoff frequency, fs = sampling rate
float smoothing_factor = expf(-2 * PI * cutOff_frequency / sampling_rate);

/* Stores the previous filtered value (initially 0) */
float filteredValue = 0;

void setup() {
  Serial.begin(115200);     // Initialize serial communication at 115200 baud
  pinMode(DISP_OUT, INPUT); // Configure sensor pin as input
}

// Main loop: reads sensor, applies filter, converts to displacement
void loop() {

  int samples = 50;       // Number of samples to average
  float total = 0.0;      // Accumulator for filtered values

  for (int i = 0; i < samples; i++) {

    /* Read raw analog data from TCND5000 sensor */
    float raw = analogRead(DISP_OUT);

    /* Apply exponential low-pass filter:
       filtered[k] = (1 - α)*raw + α*filtered[k-1]
       where α = smoothing_factor
    */
    filteredValue = (1.0f - smoothing_factor) * raw + smoothing_factor * filteredValue;
    
    /* Accumulate filtered samples */
    total += filteredValue;

    // Small delay to match sampling period (100 µs)
    delayMicroseconds(100);
  }

  /* Compute average of filtered samples */
  float average = total / samples; 

  /* Convert ADC reading to voltage (mV):
     - ADC resolution: 12-bit (0–4095)
     - Reference voltage: 3.3 V = 3300 mV
     Formula: (ADC_value / 4095) * 3300
  */
  float voltage_mV = (average / 4095.0) * 3300.0;

  /* Convert voltage to displacement (mm) using calibration equation:
     displacement = 227 - 0.973 * voltage_mV
     (linear mapping derived experimentally for TCND5000)
  */
  double displacement = 227 - 0.973 * voltage_mV;

  /* ---------------- Grading Scale ----------------
     Assign grade levels based on displacement thresholds
  */
  if (displacement < 2) {
      Serial.print("Grade level: 1, Displacement: ");
      Serial.println(displacement);
  }
  else if (displacement < 4) {
      Serial.print("Grade level: 2, Displacement: ");
      Serial.println(displacement);
  }
  else if (displacement < 6) {
      Serial.print("Grade level: 3, Displacement: ");
      Serial.println(displacement);
  }
  else if (displacement < 8) {
      Serial.print("Grade level: 4, Displacement: ");
      Serial.println(displacement);
  }

  /* Debug/marker output:
     Prints fixed values (-10, 10) followed by displacement
     Possibly used for plotting or calibration reference
  */
  Serial.print(-10);
  Serial.print(", ");
  Serial.print(10);
  Serial.print(", ");
  Serial.println(displacement, 2); // Print displacement with 2 decimal places
}
