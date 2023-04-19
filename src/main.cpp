#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <WebServer.hpp>

// Define your WiFi credentials
const char* ssid = "Simha";
const char* password = "Jogi2Jogi";


WebServer server;

// Initialize the AsyncWebServer object
AsyncWebServer router(80);

void setup() {

  Serial.begin(9600);

  server.initWebServer(ssid, password, "http://localhost:4000");

  router.on("/a", HTTP_POST, [](AsyncWebServerRequest * request){
  }, NULL, [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    // Handle message       
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, data);
    if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      request->send(400, "text/plain", "Bad Request");
      return;
    }

    const char* message = doc["a"];
    Serial.println(message);

    request->send(200);
  });
  
  router.on("/b", HTTP_POST, [](AsyncWebServerRequest * request){
  }, NULL, [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    // Handle message       
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, data);
    if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      request->send(400, "text/plain", "Bad Request");
      return;
    }

    const char* message = doc["b"];
    Serial.println(message);

    request->send(200);
  });

    router.on("/c", HTTP_POST, [](AsyncWebServerRequest * request){
  }, NULL, [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    // Handle message       
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, data);
    if(error){
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      request->send(400, "text/plain", "Bad Request");
      return;
    }

    const char* message = doc["c"];
    Serial.println(message);

    request->send(200);
  });
  // Start the server
  router.begin();
}

void loop() {
}
