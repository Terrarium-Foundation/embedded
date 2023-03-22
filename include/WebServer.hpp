#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>

class WebServer{
    public:
        void initWebServer(const char* ssid, const char* password, String serverName);
        int wifiConnected();
        String makeJson(std::vector<String> keys, std::vector<String> values);
        String getRequest(String header, String data);
        String postRequest(String header, String data);
    private:
        const char* ssid;
        const char* password;
        String serverName;

};
