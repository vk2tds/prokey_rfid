/*
 * Example on how to use the Wiegand reader library with interruptions.
 */

#include <Wiegand.h>

#include "wiegandOutput.h"
WiegandOut wiegandOut(D6,D5);

// These are the pins connected to the Wiegand D0 and D1 signals.
#define PIN_A0 D15
#define PIN_A1 D14
#define PIN_B0 D13
#define PIN_B1 D12
#define PIN_C0 D11
#define PIN_C1 D10
#define PIN_D0 D9
#define PIN_D1 D8


// The object that handles the wiegand protocol
Wiegand wiegand_A;
Wiegand wiegand_B;
Wiegand wiegand_C;
Wiegand wiegand_D;

// Initialize Wiegand reader
void setup() {
  Serial.begin(9600);

  //Install listeners and initialize Wiegand reader
  wiegand_A.onReceive(receivedData, "Card read A: ");
  wiegand_A.onReceiveError(receivedDataError, "Card read error: ");
  wiegand_A.onStateChange(stateChanged, "State changed: ");
  wiegand_A.begin(Wiegand::LENGTH_ANY, true);

  wiegand_B.onReceive(receivedData, "Card read B: ");
  wiegand_B.onReceiveError(receivedDataError, "Card read error: ");
  wiegand_B.onStateChange(stateChanged, "State changed: ");
  wiegand_B.begin(Wiegand::LENGTH_ANY, true);

  wiegand_C.onReceive(receivedData, "Card read C: ");
  wiegand_C.onReceiveError(receivedDataError, "Card read error: ");
  wiegand_C.onStateChange(stateChanged, "State changed: ");
  wiegand_C.begin(Wiegand::LENGTH_ANY, true);

  wiegand_D.onReceive(receivedData, "Card read D: ");
  wiegand_D.onReceiveError(receivedDataError, "Card read error: ");
  wiegand_D.onStateChange(stateChanged, "State changed: ");
  wiegand_D.begin(Wiegand::LENGTH_ANY, true);
  
  
  //initialize pins as INPUT
  pinMode(PIN_A0, INPUT);
  pinMode(PIN_A1, INPUT);
  pinMode(PIN_B0, INPUT);
  pinMode(PIN_B1, INPUT);
  pinMode(PIN_C0, INPUT);
  pinMode(PIN_C1, INPUT);
  pinMode(PIN_D0, INPUT);
  pinMode(PIN_D1, INPUT);

}

// Continuously checks for pending messages and polls updates from the wiegand inputs
void loop() {
  // Checks for pending messages
  wiegand_A.flush();

  // Check for changes on the the wiegand input pins
  wiegand_A.setPin0State(digitalRead(PIN_A0));
  wiegand_A.setPin1State(digitalRead(PIN_A1));

  wiegand_B.flush();

  // Check for changes on the the wiegand input pins
  wiegand_B.setPin0State(digitalRead(PIN_B0));
  wiegand_B.setPin1State(digitalRead(PIN_B1));

  wiegand_C.flush();

  // Check for changes on the the wiegand input pins
  wiegand_C.setPin0State(digitalRead(PIN_C0));
  wiegand_C.setPin1State(digitalRead(PIN_C1));

  wiegand_D.flush();

  // Check for changes on the the wiegand input pins
  wiegand_D.setPin0State(digitalRead(PIN_D0));
  wiegand_D.setPin1State(digitalRead(PIN_D1));

}

// Notifies when a reader has been connected or disconnected.
// Instead of a message, the seconds parameter can be anything you want -- Whatever you specify on `wiegand.onStateChange()`
void stateChanged(bool plugged, const char* message) {
    Serial.print(message);
    Serial.println(plugged ? "CONNECTED" : "DISCONNECTED");
}

// Notifies when a card was read.
// Instead of a message, the seconds parameter can be anything you want -- Whatever you specify on `wiegand.onReceive()`
void receivedData(uint8_t* data, uint8_t bits, const char* message) {
    Serial.print(message);
    Serial.print(bits);
    Serial.print("bits / ");
    //Print value in HEX
    uint32_t w = 0;
    uint8_t bytes = (bits+7)/8;
    for (int i=0; i<bytes; i++) {
        Serial.print(data[i] >> 4, 16);
        Serial.print(data[i] & 0xF, 16);
        w = (w << 8) | data[i];
    }
    Serial.println();
    switch (message[10]){
      case 'A': w = w | 0x00000; break;
      case 'B': w = w | 0x40000; break;
      case 'C': w = w | 0x80000; break;
      case 'D': w = w | 0xC0000; break;
    }
    Serial.println (w);

    wiegandOut.send(w,34,false);
    
}

// Notifies when an invalid transmission is detected
void receivedDataError(Wiegand::DataError error, uint8_t* rawData, uint8_t rawBits, const char* message) {
    Serial.print(message);
    Serial.print(Wiegand::DataErrorStr(error));
    Serial.print(" - Raw data: ");
    Serial.print(rawBits);
    Serial.print("bits / ");

    //Print value in HEX
    uint8_t bytes = (rawBits+7)/8;
    for (int i=0; i<bytes; i++) {
        Serial.print(rawData[i] >> 4, 16);
        Serial.print(rawData[i] & 0xF, 16);
    }
    Serial.println();
}
