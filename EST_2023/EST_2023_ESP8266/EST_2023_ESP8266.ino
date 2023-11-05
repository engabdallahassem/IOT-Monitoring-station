
//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//NodeMCU code

//Include Lib for Arduino to Nodemcu
// #include <SoftwareSerial.h>
#include <ArduinoJson.h>
float t, h, c;
//D6 = Rx & D5 = Tx
// SoftwareSerial nodemcu(D6, D5);


// #define Max_Temp 40
// #define Max_Hum 70
// #define Max_Dust 3000
// #define Beeb_Duration 1000
#include <EEPROM.h>

#define VAR1_ADDRESS 50
#define VAR2_ADDRESS 54
#define VAR3_ADDRESS 58
#define VAR4_ADDRESS 62




void arduinoSetup() {
  // Initialize Serial port
  Serial.begin(9600);
  // nodemcu.begin(9600);
  // while (!Serial) continue;
}

void arduinoLoop() {

  rxArduino();
}
void rxArduino() {

  DynamicJsonDocument data(200);
  DeserializationError error = deserializeJson(data, Serial);
  if (error)
    return;

  h = data["humidity"];
  t = data["temperature"];
  c = data["concentration"];


  txArduino();
}
void txArduino() {
  DynamicJsonDocument control(64);

  float Max_Temp, Max_Hum, Max_Dust, Beeb_Duration;
  EEPROM.get(VAR1_ADDRESS, Max_Temp);
  EEPROM.get(VAR2_ADDRESS, Max_Hum);
  EEPROM.get(VAR3_ADDRESS, Max_Dust);
  EEPROM.get(VAR4_ADDRESS, Beeb_Duration);


  if (t >= Max_Temp || h >= Max_Hum || c >= Max_Dust) {

    control["buzzer"] = 1;
    control["duration"] = Beeb_Duration;
    serializeJson(control, Serial);
  } else {
    control["buzzer"] = 0;
    control["duration"] = 0;
    serializeJson(control, Serial);
  }
}