/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

// Import required libraries
// #include <ESP8266WiFi.h>
// #include "ESPAsyncWebServer.h"

// Create AsyncWebServer object on port 80
// AsyncWebServer server(80);

String readDHTTemperature() {

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)

  //  float t = dht.readTemperature();

  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    // Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)


  //  float h = dht.readHumidity();
  // float h = x;
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    // Serial.println(h);
    return String(h);
  }
}
String readDust() {

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //  float d = dht.readHumidity();
  // float d = x;
  if (isnan(c)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    // Serial.println(c);
    return String(c);
  }
}



// Replaces placeholder with DHT values
String processor(const String& var) {
  //Serial.println(var);
  if (var == "TEMPERATURE") {
    return readDHTTemperature();
  } else if (var == "HUMIDITY") {
    return readDHTHumidity();
  } else if (var == "DUST") {
    return readDust();
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  // Serial.begin(115200);

  //  dht.begin();

  // Connect to Wi-Fi
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi..");
  // }

  // // Print ESP32 Local IP Address
  // Serial.println(WiFi.localIP());

  arduinoSetup();
  YonovaOTASetup("EST2023", AP_ONLY);


  // Route for root / web page




  YONOVAwebServer.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  YONOVAwebServer.on("/temperature", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  YONOVAwebServer.on("/humidity", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
  YONOVAwebServer.on("/dust", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/plain", readDust().c_str());
  });
  YONOVAwebServer.on("/localip", HTTP_GET, [](AsyncWebServerRequest* request) {
    String ipAddress = WiFi.localIP().toString();
    String htmlResponse = "<div style='display: flex; justify-content: center; align-items: center; flex-direction: column; height: 100vh; font-size: 3rem;'>Connected with IP " + ipAddress + "</div>";
    request->send(200, "text/html", htmlResponse);
  });
  // //WiFi_AP
  // YONOVAwebServer.onNotFound([](AsyncWebServerRequest* request) {
  //   request->redirect("/localip");  // send all DNS requests to root
  //                                   //request->send_P(200, "text/html", root_html);
  // });
  //AP_ONLY
  YONOVAwebServer.onNotFound([](AsyncWebServerRequest* request) {
    request->redirect("/");  // send all DNS requests to root
                             //request->send_P(200, "text/html", root_html);
  });
  xsetup();
}

void loop() {

  arduinoLoop();
}
