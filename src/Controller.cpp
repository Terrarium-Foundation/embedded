#include <Controller.hpp>

Timer pumpTimer;
Timer lightTimer;

Controller::Controller(int pumpPin, int lightPin, unsigned long pumpOn, unsigned long pumpOff, unsigned long lightOn, int lightOff){
    Controller::pumpPin = pumpPin;
    Controller::lightPin = lightPin;
    Controller::pumpState = 0;
    Controller::lightState = 0;

    pumpTimer.initTimer(pumpOn, pumpOff);
    lightTimer.initTimer(lightOn, lightOff);
}

void Controller::updatePumpState(int state){
    Controller::pumpState = state;
    digitalWrite(Controller::pumpPin, state);
}

void Controller::updateLightState(int state){ //state=HIGH or LOW
    Controller::lightState = state;
    digitalWrite(Controller::lightPin, state);
}

void Controller::updateAutopilotState(int state){
    if(!state){
        pumpTimer.startTimer();
        lightTimer.startTimer();
    }
    else{
        pumpTimer.stopTimer();
        lightTimer.stopTimer();
    }
    Controller::autopilotState = state;
}

void Controller::updateInterval(int interval){
    Controller::interval = interval;
}

//rules + also runs pump/light intervals
//if interval is on, use intervals to turn on/off pump/light
//if autopilot is on, use rules to turn on/off pump/light
//both interval and manual light/pump cannot be on at the same time, must be mutually exclusive
void Controller::autopilotMode(){
    if(Controller::autopilotState){
        //define autopilot rules
    }
    else if(Controller::interval == 0){
        pumpTimer.updateTimer();
        lightTimer.updateTimer();
        if(pumpTimer.isOn()){
            Controller::updatePumpState(HIGH);
        }else{
            Controller::updatePumpState(LOW);
        }
        if(lightTimer.isOn()){
            Controller::updateLightState(HIGH);
        }else{
            Controller::updateLightState(LOW);
        }
    }
}