// Load Wi-Fi library
#include <WiFi.h>
#include <WebServer.hpp>
#include <Arduino_JSON.h>
#include <SoilMoisture.hpp>
#include <Timer.hpp>

// Replace with your network credentials
const char* ssid = "Simha";
const char* password = "Jogi2Jogi";
//esp32 doesnt work with localhost or 127.0.0.1, get the actual ip address of machine it is hosted on
String toServer = "http://192.168.1.26:4000";


// WebServer server;
// SoilMoisture soil(2);
Timer pump;

void setup(){
  Serial.begin(9600);
  // server.initWebServer(ssid, password, toServer);
  pump.initTimer(1000, 2000);
  pump.startTimer();
}

void loop(){
  Serial.println("It is ON!");
  while(pump.isOn()){pump.updateTimer();}
  Serial.println("It is OFF!");
  while(!pump.isOn()){pump.updateTimer();}
}
