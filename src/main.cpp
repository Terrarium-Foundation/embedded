#include <WiFi.h>
#include <Arduino.h>

// Replace with your network credentials (STATION)
const char* ssid = "Simha";
const char* password = "Jogi2Jogi";

void initWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('>');
    delay(1000);
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting Terrarium!");
  initWifi();
  Serial.print("Connected To: ");
  Serial.print(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}
