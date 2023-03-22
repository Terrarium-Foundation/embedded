// Load Wi-Fi library
#include <WiFi.h>
#include <WebServer.hpp>
#include <Arduino_JSON.h>

// Replace with your network credentials
const char* ssid = "Simha";
const char* password = "Jogi2Jogi";
//esp32 doesnt work with localhost or 127.0.0.1, get the actual ip address of machine it is hosted on
String toServer = "http://192.168.1.26:4000";

WebServer server;

void setup(){
  Serial.begin(9600);
  server.initWebServer(ssid, password, toServer);
}

void loop(){

  std::vector<String> keys = {"p", "r", "a"};
  std::vector<String> values = {"n", "a", "v"};
  if(server.wifiConnected()){
    String jsonData = server.makeJson(keys, values);
    String response = server.postRequest("/esp32",jsonData);
    
    // JSONVar res = JSON.parse(response);
    // JSONVar keys = res.keys();

    // for(int i=0; i<keys.length(); i++){
    //   JSONVar value = res[keys[i]];
    //   Serial.print(keys[i]+": ");
    //   Serial.println(value);
    // }
  }

  delay(1000);
}
