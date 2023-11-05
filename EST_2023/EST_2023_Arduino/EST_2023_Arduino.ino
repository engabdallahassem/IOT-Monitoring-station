// DHT11 Lib
#include <DHT.h>

// Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// DHT11 sensor pin and type
#define DHTPIN 2
#define DHTTYPE DHT22

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);


// PM2.5 sensor pin and variables
int pin = 3;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

// Initialize Arduino to NodeMCU communication
SoftwareSerial nodemcu(4, 5);  // RX, TX pins for communication with NodeMCU

// Initialize buzzerPin
const int buzzerPin = 6;

// Create JSON object
DynamicJsonDocument data(200);
void setup() {
  Serial.begin(9600);

  dht.begin();
  nodemcu.begin(9600);
  alarmSetup();
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  // Read PM2.5 concentration
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;

  if ((millis() - starttime) > sampletime_ms) {
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0);
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
    lowpulseoccupancy = 0;

    // Print PM2.5 concentration
    Serial.print("PM2.5 Concentration: ");
    Serial.println(concentration);

    data["humidity"] = hum;
    data["temperature"] = temp;
    data["concentration"] = concentration;
    serializeJson(data, Serial);
    serializeJson(data, nodemcu);

    starttime = millis();
  }
  alarmLoop();
}
