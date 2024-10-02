void setup() {
    // Initialize digital pins 0 to 7 as outputs
    for (int i = 0; i <= 7; i++) {
        pinMode(i, OUTPUT);
    }

    // Initialize serial communication at 9600 bits per second
    Serial.begin(9600);
}

void loop() {
    static int counter = 0; // Declare and initialize counter
    
    // Set each pin based on the corresponding bit value of the counter
    for (int i = 0; i <= 7; i++) {
        digitalWrite(i, (counter & (1 << i)) ? HIGH : LOW);
    }

    // Read the value from the analog inputs
    int analogValue0 = analogRead(A0);
    int analogValue1 = analogRead(A1);

    // Convert analog readings to voltage
    float referenceVoltage = 5.0;
    float voltage0 = (analogValue0 / 1023.0) * referenceVoltage;
    float voltage1 = (analogValue1 / 1023.0) * referenceVoltage;

    // Calculate v_led and i_led
    float v_led = voltage0 - voltage1;
    float i_led = voltage1;

    // Print the values to the serial monitor in the desired format
    Serial.print(" COUNT: ");
    Serial.print(counter);
    Serial.print(" | V: ");
    Serial.print(v_led);
    Serial.print(" I: ");
    Serial.print(i_led);
    

    // Increment the counter and reset if it reaches 128
    counter = (counter + 1) % 128;

    // Add a small delay before the next loop
    delay(10);
}