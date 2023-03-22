#include <WebServer.hpp>

void WebServer::initWebServer(const char* ssid, const char* password, String toServer){

  WiFiServer server(80);
  WebServer::serverName = toServer;
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

int WebServer::wifiConnected(){
    return WiFi.status() == WL_CONNECTED;
}

String WebServer::makeJson(std::vector<String> keys, std::vector<String> values){

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

    return jsonData;
}

void WebServer::sendPostRequest(String header, String data){

    if(wifiConnected()){
        WiFiClient client;
        HTTPClient http;

        http.begin(client, WebServer::serverName+header);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(data);
        
        http.end();
    }
}