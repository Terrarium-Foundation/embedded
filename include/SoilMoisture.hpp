#include <Arduino.h>

class SoilMoisture{
    public:
        SoilMoisture(int pin);
        float readData();
    private:
        int pin;
        float moisture;
};