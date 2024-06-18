#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CSN pins
#define CE_PIN D4
#define CSN_PIN D2

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the address for the communication
const byte address[6] = "00002";

void setup() {
  // Initialize the motor pins as outputs
  pinMode(D3, OUTPUT);
  pinMode(D8, OUTPUT);

  // Initialize the Serial Monitor
  Serial.begin(9600);

  // Initialize the radio
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    Serial.println("Signal received");

    // Define a buffer to hold the received message
    char message[32] = {0};

    // Read the message
    radio.read(&message, sizeof(message));

    // Extract the values from the message
    int receivedValue1, receivedValue2;
    sscanf(message, "%d,%d", &receivedValue1, &receivedValue2);

    // Print the received message and values to the Serial Monitor
    Serial.print("Received Message: ");
    Serial.println(message);
    Serial.print("Extracted Value 1: ");
    Serial.println(receivedValue1);
    Serial.print("Extracted Value 2: ");
    Serial.println(receivedValue2);

    // Output the received values to the motor pins
    analogWrite(D3, receivedValue1);
    analogWrite(D8, receivedValue2);
  }
}