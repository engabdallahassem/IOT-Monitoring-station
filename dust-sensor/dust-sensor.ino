//ThatsEngineering
//Sending Data from Arduino to NodeMCU Via Serial Communication
//Arduino code

//DHT11 Lib
#include <DHT.h>

//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);

//Initialisation of DHT11 Sensor
#define DHTPIN 4

#define DHTTYPE DHT22      // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);  //// Initialize DHT sensor for normal 16mhz Arduino
// DHT dht(DHTPIN, DHT11);
float temp;
float hum;

void setup() {
  Serial.begin(9600);

  dht.begin();
  nodemcu.begin(9600);
  delay(1000);

  Serial.println("Program started");
}

void loop() {

  // StaticJsonDocument<1000> jsonBuffer;
  // JsonObject& data = jsonBuffer.createObject();

  // ArduinoJson 6
  DynamicJsonDocument data(1000);
  // doc["key"] = "value";
  // doc["raw"] = serialized("[1,2,3]");
  // serializeJson(doc, Serial);

  //Obtain Temp and Hum data
  dht11_func();


  //Assign collected data to JSON Object
  data["humidity"] = hum;
  data["temperature"] = temp;

  //Send data to NodeMCU
  // data.printTo(nodemcu);

  serializeJson(data, Serial);
  // jsonBuffer.clear();

  delay(2000);
}

void dht11_func() {

  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);
}