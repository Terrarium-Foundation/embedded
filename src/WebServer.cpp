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

String WebServer::getRequest(String header, String data){

    String payload;

    if(wifiConnected()){
        WiFiClient client;
        HTTPClient http;

        //data not included in GET request as this would mainly be used to fetch instructions
        String serverPath = WebServer::serverName+header;
        http.begin(serverPath.c_str());

        payload = http.getString();
    }

    return payload;
}

String WebServer::postRequest(String header, String data){

    String payload;
    if(wifiConnected()){
        WiFiClient client;
        HTTPClient http;

        http.begin(client, WebServer::serverName+header);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(data);
        
        Serial.print("HTTP POST returned with response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
        //Serial.println(payload);

        http.end();
    }

    return payload;
}