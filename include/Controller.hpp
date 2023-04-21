#include <Arduino.h>

class Controller{
    public:
        Controller(int pumpPin, int lightPin, unsigned long pumpOn, unsigned long pumpOff, unsigned long lightOn, int lightOff);
        void updatePumpState(int state);
        void updateLightState(int state);
        void updateAutopilotState(int state);
        void updateLightInterval(int interval);
        void updatePumpInterval(int interval);
        void autopilotMode();
    private:
        int pumpPin;
        int pumpState;
        int lightPin;
        int lightState;
        int autopilotState;
        int lightInterval;
        int pumpInterval;
};