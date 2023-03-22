// Load Wi-Fi library
#include <WiFi.h>
#include <WebServer.hpp>

// Replace with your network credentials
const char* ssid = "Simha";
const char* password = "Jogi2Jogi";
//esp32 doesnt work with localhost or 127.0.0.1, get the actual ip address of machine it is hosted on
String toServer = "http://192.168.1.26:4000";

WiFiServer server(80);

// WebServer server(ssid, password, toServer);

void setup(){

    Serial.begin(9600);
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(">");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}

void loop(){

  std::vector<String> keys = {"a", "b", "c"};
  std::vector<String> values = {"1", "2", "3"};
  
  if(WiFi.status() == WL_CONNECTED){

    int size = keys.size();
    String jsonData = "";

    if(keys.size()==values.size()){
        jsonData+="{";
        for(int i=0; i<size; i++){
            jsonData+="\""+keys[i]+"\""+":\""+values[i]+"\",";
        }
        jsonData = jsonData.substring(0, jsonData.length()-1);
        jsonData+="}";
    }

    if(WiFi.status() == WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      http.begin(client, toServer+"/esp32");
      http.addHeader("Content-Type", "application/json");
      Serial.println(jsonData);
      int httpResponseCode = http.POST(jsonData);
      
      http.end();
    }
  }

  delay(10000);
}
