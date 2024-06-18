#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the pins for the NRF24L01
#define CE_PIN   8
#define CSN_PIN 10

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the address for the communication
const byte address[6] = "00002";

// Define the potentiometer pin
#define POT_PIN A0
#define POT_PIN2 A1

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Initialize the radio
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // Read the potentiometer values
  int potValue = analogRead(POT_PIN);
  int potValue2 = analogRead(POT_PIN2);

  // Map the potentiometer values from 0-1023 to 0-255
  int mappedValue = map(potValue, 0, 1023, 0, 255);
  int mappedValue2 = map(potValue2, 0, 1023, 0, 255);

  // Create a message containing the mapped values
  char message[32];
  snprintf(message, sizeof(message), "%d,%d", mappedValue, mappedValue2);

  // Print the potentiometer and mapped values to the Serial Monitor
  Serial.print("Pot1 Value: ");
  Serial.print(potValue);
  Serial.print("  Mapped Value: ");
  Serial.println(mappedValue);
  Serial.print("Pot2 Value: ");
  Serial.print(potValue2);
  Serial.print("  Mapped Value: ");
  Serial.println(mappedValue2);
  Serial.print("Sending Message: ");
  Serial.println(message);

  // Send the message
  bool report = radio.write(&message, sizeof(message));
  
  // Print if the transmission was successful or not
  if (report) {
    Serial.println("Transmission successful");
  } else {
    Serial.println("Transmission failed");
  }

  // Print the NRF24L01 status
  printRadioStatus();
  
  // Add a small delay before the next loop
   // Increased delay to reduce the frequency of messages
}

void printRadioStatus() {
  // Print the radio status
  radio.printDetails();
}