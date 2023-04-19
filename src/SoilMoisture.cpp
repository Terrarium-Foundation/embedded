#include <SoilMoisture.hpp>

SoilMoisture::SoilMoisture(int pin){
    SoilMoisture::pin = pin;
}

float SoilMoisture::readData(){
    SoilMoisture::moisture = analogRead(SoilMoisture::pin);
    // SoilMoisture::moisture = ((SoilMoisture::moisture-4950)/4950)*100;
    return SoilMoisture::moisture;
}