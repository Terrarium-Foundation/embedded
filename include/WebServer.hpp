#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>

class WebServer{
    public:
        WebServer(const char* ssid, const char* password, String serverName);
        int wifiConnected();
        String makeJson(std::vector<String> keys, std::vector<String> values);
        void sendPostRequest(String header, String data);
    private:
        const char* ssid;
        const char* password;
        String serverName;

};
