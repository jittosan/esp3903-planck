#include<cmath>

int counter = 0; // Declare and initialize counter
int rest = 1000;
int bit_count = 8;

void setup() {
    // Initialize digital pins 0 to 7 as outputs
    for (int i = 0; i < bit_count; i++) {
        pinMode(i, OUTPUT);
    }

    

    // Initialize serial communication at 9600 bits per second
    Serial.begin(9600);
}

void loop() {
    
    
    // Set each pin based on the corresponding bit value of the counter
    for (int i = 0; i < bit_count; i++) {
        digitalWrite(i, (counter & (1 << i)) ? HIGH : LOW);
        // Serial.print((counter & (1 << i)) ? 1 : 0);
        // Serial.print(" ");
    }
    // Serial.println();
    // Read the value from the analog inputs
    int analogValue0 = analogRead(A0);
    int analogValue1 = analogRead(A1);

    // Convert analog readings to voltage
    float referenceVoltage = 5.0;
    float voltage0 = (analogValue0 / 1023.0) * referenceVoltage;
    float voltage1 = (analogValue1 / 1023.0) * referenceVoltage;

    // Calculate v_led and i_led
    float v_led = voltage0 - voltage1;
    float i_led = voltage1 / rest;

    // Print the values to the serial monitor in the desired format
    // Serial.print(" COUNT: ");
    // Serial.print(counter);
    // Serial.print(" | V: ");
    // Serial.print(v_led, 8);
    // Serial.print("V I: ");
    // Serial.print(i_led, 8);
    // Serial.println("A");

    Serial.print(counter);
    Serial.print(", ");
    Serial.print(v_led, 8);
    Serial.print(", ");
    Serial.println(i_led, 8);

    // Increment the counter and reset if it reaches 8
  
    counter = (counter + 1) % int(pow(2.0, bit_count));
    // counter = (counter + 1) % 100;

    // Add a small delay before the next loop
    delay(200);
}