/**********************************************************************************
 *  TITLE: Blynk 2.0 + Manual Button (Momentary) control 4 Relays using NodeMCU (Real time feedback)(No Wi-Fi control)
 *  I have Modified the Blynk.Edgent.Edgent_ESP8266 example code (https://blynk.io/) for this project
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/O9VYZqWPNEQ
 *  Related Blog : https://iotcircuithub.com/home-automation-using-nodemcu-and-blynk/
 *  by Subhajit (Tech StudyCell)
 *  Preferences--> Aditional boards Manager URLs : 
 *  https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  Download Board ESP8266 NodeMCU : https://github.com/esp8266/Arduino
 *  Download the libraries
 *  Blynk 1.0.1 Library:  https://github.com/blynkkk/blynk-library
 **********************************************************************************/

// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLmLjHpNqy"// Enter the Blynk template ID here
#define BLYNK_DEVICE_NAME "Anokhautomation"// Enter the Blynk Device Name here
//#define BLYNK_DEVICE_NAME ""

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

//#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD


// define the GPIO connected with Relays
#define RelayPin1 5  //connect Relay 1 to D1 pin of Node MCU
#define RelayPin2 4  //connect Relay 2 to D2 pin of Node MCU
#define RelayPin3 14 //connect Relay 3 to D5 pin of Node MCU
#define RelayPin4 12 //connect Relay 4 to D6 pin of Node MCU
// define the GPIO connected with push buttons
#define SwitchPin1 2  //connect push button 1 to D4 pin of NodeMCU
#define SwitchPin2 D3 //connect push button 2 to D3 pin of NodeMCU
#define SwitchPin3 13 //connect push button 3 to 7 pin of NodeMCU
#define SwitchPin4 3  //connect push button 4 to RX pin of NodeMCU

#define wifiLed   16   //D0

//Change the virtual pins according the rooms
#define VPIN_BUTTON_1    V1
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4

// Relay State
bool toggleState_1 = LOW; //Define integer to remember the toggle state for relay 1
bool toggleState_2 = LOW; //Define integer to remember the toggle state for relay 2
bool toggleState_3 = LOW; //Define integer to remember the toggle state for relay 3
bool toggleState_4 = LOW; //Define integer to remember the toggle state for relay 4

#include "BlynkEdgent.h"

BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
  Blynk.syncVirtual(VPIN_BUTTON_3);
  Blynk.syncVirtual(VPIN_BUTTON_4);
}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  if(toggleState_1 == 1){
    digitalWrite(RelayPin1, LOW);
  }
  else { 
    digitalWrite(RelayPin1, HIGH);
  }
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  if(toggleState_2 == 1){
    digitalWrite(RelayPin2, LOW);
  }
  else { 
    digitalWrite(RelayPin2, HIGH);
  }
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  if(toggleState_3 == 1){
    digitalWrite(RelayPin3, LOW);
  }
  else { 
    digitalWrite(RelayPin3, HIGH);
  }
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  if(toggleState_4 == 1){
    digitalWrite(RelayPin4, LOW);
  }
  else { 
    digitalWrite(RelayPin4, HIGH);
  }
}


void setup()
{
  Serial.begin(115200);
  delay(100);
  
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  digitalWrite(wifiLed, HIGH);

  BlynkEdgent.begin();

  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);

}

void loop() {

    BlynkEdgent.run();
    
    manual_control(); //Manual Switch Control   
}
