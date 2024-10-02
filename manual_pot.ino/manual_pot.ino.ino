// C++ code
//

// Define constants at the start of the code
const float R = 100.0; // Example resistance value

// Analog input pins
const int ANALOG_IN_1 = A0;
const int ANALOG_IN_2 = A1;
const int ANALOG_IN_3 = A2;

// Analog output pin
const int ANALOG_OUT = 2; // PWM output (on pins 9, 10, etc.)

// Store results in an array
float results[4]; // Array to hold the differences and division result

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Configure the analog output pin
  pinMode(ANALOG_OUT, OUTPUT);
}

void loop() {
  // Read analog inputs
  float voltage1 = analogRead(A0) * (5.0 / 1023.0);
  float voltage2 = analogRead(A1) * (5.0 / 1023.0);

  // Calculate differences and division
  results[0] = voltage1 - voltage2;
  results[1] = voltage2;
  results[2] = voltage2 / R;

  // Output values to the Serial monitor
  Serial.print("A0: ");
  Serial.print(voltage1);
  Serial.print("V, A1: ");
  Serial.print(voltage2);
  Serial.print("V | V_LED: ");
  Serial.print(results[0]);
  Serial.print("V, V_R3: ");
  Serial.print(results[1]);
  Serial.print("V, I_R3: ");
  Serial.print(results[2]);
  Serial.print("A, I_R3: ");
  Serial.print(voltage2/R);
  Serial.println("A");

  // Small delay to stabilize readings
  delay(50);
  // After completing the sweep, you can either stop or reset
  // to repeat the process. Uncomment the following line to reset:
  // loop();
}