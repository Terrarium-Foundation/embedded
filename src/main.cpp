#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <WebServer.hpp>
#include <Timer.hpp>
#include <Controller.hpp>

// Define your WiFi credentials
const char* ssid = "Simha";
const char* password = "Jogi2Jogi";


WebServer server;

// Initialize the AsyncWebServer object
AsyncWebServer router(80);

Timer collectData;
bool collect = true;

Controller master(2, 4, 1000, 1000, 3000, 5000);

void setup() {

  Serial.begin(9600);

  server.initWebServer(ssid, password, "http://localhost:4000");

  pinMode(2, OUTPUT);

  //collect dataOn is set to 10ms in the hopes it will only collect once
  collectData.initTimer(10, 5000);

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
    Serial.println(action);

    //update controller state
    if((strcmp(action, "on") == 0) && (strcmp(type, "water") == 0)){
      master.updatePumpState(HIGH);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "water") == 0)){
      master.updatePumpState(LOW);
    }
    else if((strcmp(action, "on") == 0) && (strcmp(type, "light") == 0)){
      master.updateLightState(HIGH);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "light") == 0)){
      master.updateLightState(LOW);
    }
    else if((strcmp(action, "on") == 0) && (strcmp(type, "autopilot") == 0)){
      master.updateAutopilotState(HIGH);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "autopilot") == 0)){
      master.updateAutopilotState(LOW);
    }
    else if((strcmp(action, "on") == 0) && (strcmp(type, "lightInterval") == 0)){
      Serial.println("lightInterval on");
      master.updateLightInterval(HIGH);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "lightInterval") == 0)){
      master.updateLightInterval(LOW);
    }
    else if((strcmp(action, "on") == 0) && (strcmp(type, "pumpInterval") == 0)){
      master.updatePumpInterval(HIGH);
    }
    else if((strcmp(action, "off") == 0) && (strcmp(type, "pumpInterval") == 0)){
      master.updatePumpInterval(LOW);
    }

    request->send(200);
  });

  // Start the server
  router.begin();
}

void loop() {
  // collectData.updateTimer();
  // if(collectData.isOn()){
  //   //collect data
  //   //send it to server
  // }
  // else{
  //   //wait, don't do anything
  // }

  master.autopilotMode();
}
