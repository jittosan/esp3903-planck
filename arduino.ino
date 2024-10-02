const int OUT_PIN = A0;  // Analog output pin
const int IN_PIN_1 = A1; // Analog input pin 1
const int IN_PIN_2 = A2; // Analog input pin 2
const int IN_PIN_3 = A3; // Analog input pin 3

const float OUT_MAX = 5.0;       // Maximum output voltage
const float OUT_MIN = 0.0;       // Minimum output voltage
const float OUT_INTERVAL = 0.1;  // Output voltage interval

const float R = 100.0;  // Resistance value for calculating i_led

const int NUM_SAMPLES = 100;  // Number of samples to collect

float v_led, v_r, i_led;  // Variables to store voltage and current values

float voltageArray[NUM_SAMPLES];  // Array to store voltage values

void setup() {
    pinMode(OUT_PIN, OUTPUT);   // Set OUT_PIN as output
    pinMode(IN_PIN_1, INPUT);   // Set IN_PIN_1 as input
    pinMode(IN_PIN_2, INPUT);   // Set IN_PIN_2 as input
    pinMode(IN_PIN_3, INPUT);   // Set IN_PIN_3 as input
}
    Serial.begin(9600);
}

void loop() {
    for (float voltage = OUT_MIN; voltage <= OUT_MAX; voltage += OUT_INTERVAL) {
        analogWrite(OUT_PIN, map(voltage, 0, 5, 0, 255));  // Set analog output voltage

        float voltage1 = analogRead(IN_PIN_1) * (5.0 / 1023.0);  // Read analog input 1
        float voltage2 = analogRead(IN_PIN_2) * (5.0 / 1023.0);  // Read analog input 2
        float voltage3 = analogRead(IN_PIN_3) * (5.0 / 1023.0);  // Read analog input 3

        v_led = voltage2 - voltage1;  // Calculate v_led
        v_r = voltage3 - voltage2;    // Calculate v_r
        i_led = v_r / R;              // Calculate i_led

        Serial.print("v_led: ");
        Serial.print(v_led);
        Serial.print(", i_led: ");
        Serial.println(i_led);

        static int sampleIndex = 0;
        voltageArray[sampleIndex] = v_led;  // Store v_led in the array
        sampleIndex++;

        if (sampleIndex >= NUM_SAMPLES) {
            // Array is full, do something with the collected data
            // For example, you can calculate the average of v_led values
            float averageV_led = 0.0;
            for (int i = 0; i < NUM_SAMPLES; i++) {
                averageV_led += voltageArray[i];
            }
            averageV_led /= NUM_SAMPLES;

            // Reset sampleIndex to start collecting new samples
            sampleIndex = 0;
        }

        delay(100);  // Delay between voltage sweeps
    }
}