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

    // Calculate v_led and i_led
    int v_led = analogValue0 - analogValue1;
    int i_led = analogValue1;

    // Print the values to the serial monitor in the desired format
    Serial.print(" COUNT: ");
    Serial.print(counter);
    Serial.print(" | V: ");
    Serial.print(v_led);
    Serial.print(" I: ");
    Serial.print(i_led);
    

    // Increment the counter and reset if it reaches 8
    counter = (counter + 1) % 128;

    // Add a small delay before the next loop
    delay(10);
}