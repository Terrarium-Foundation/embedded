#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <WebServer.hpp>
#include <Timer.hpp>
#include <Controller.hpp>

// Define your WiFi credentials
const char* ssid = "ISA_ppr_leaked_goto_lib";
const char* password = "gglmonsta555";


WebServer server;

// Initialize the AsyncWebServer object
AsyncWebServer router(80);

Timer pumpTimer;

Controller master(2, 4, 1000, 1000, 1000, 1000);

void setup() {

  Serial.begin(9600);

  server.initWebServer(ssid, password, "http://localhost:4000");

  pinMode(2, OUTPUT);

  router.on("/updatestate", HTTP_POST, [](AsyncWebServerRequest * request){
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

    const char* type = doc["type"];
    const char* action = doc["action"];
    Serial.println(type);

    //update controller state
    if((strcmp(action, "on") == 0) && (strcmp(type, "pump") == 0)){
      master.updatePumpState(HIGH);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "pump") == 0)){
      master.updatePumpState(LOW);
    }
    else if((strcmp(action, "on") == 0) && (strcmp(type, "light") == 0)){
      master.updateLightState(HIGH);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "light") == 0)){
      master.updateLightState(LOW);
    }
    else if((strcmp(action, "on") == 0) && (strcmp(type, "autopilot") == 0)){
      master.updateAutopilotState(LOW);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "autopilot") == 0)){
      master.updateAutopilotState(HIGH);
    }
    else if((strcmp(action, "on") == 0) && (strcmp(type, "interval") == 0)){
      master.updateInterval(LOW);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "interval") == 0)){
      master.updateInterval(LOW);
    }

    request->send(200);
  });

  // Start the server
  router.begin();
}

void loop() {
  pumpTimer.updateTimer();
  if(pumpTimer.isOn()){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
}
