#include <Controller.hpp>
#include <Timer.hpp>

Timer pumpTimer;
Timer lightTimer;

Controller::Controller(int pumpPin, int lightPin, unsigned long pumpOn, unsigned long pumpOff, unsigned long lightOn, int lightOff){
    Controller::pumpPin = pumpPin;
    Controller::lightPin = lightPin;
    Controller::pumpState = 0;
    Controller::lightState = 0;
    Controller::lightInterval = 0;
    Controller::pumpInterval = 0;

    pinMode(Controller::pumpPin, OUTPUT);
    pinMode(Controller::lightPin, OUTPUT);

    pumpTimer.initTimer(pumpOn, pumpOff);
    lightTimer.initTimer(lightOn, lightOff);
}

void Controller::updatePumpState(int state){
    Controller::pumpState = state;
    digitalWrite(Controller::pumpPin, state);
    //Serial.println("Pump state updated");
}

void Controller::updateLightState(int state){ //state=HIGH or LOW
    Controller::lightState = state;
    digitalWrite(Controller::lightPin, state);
    //Serial.println("Light state updated");
}

void Controller::updateAutopilotState(int state){
    Controller::autopilotState = state;
    Serial.println("Autopilot state updated");
}

void Controller::updateLightInterval(int interval){
    if(interval){
        lightTimer.startTimer();
        Serial.println("start light timer");
    }
    else{
        lightTimer.stopTimer();
        Serial.println("stop light timer");
    }
    Controller::lightInterval = interval;
}

void Controller::updatePumpInterval(int interval){
    if(interval){
        pumpTimer.startTimer();
        Serial.println("start pump timer");
    }
    else{
        pumpTimer.stopTimer();
        Serial.println("stop pump timer");
    }
    Controller::pumpInterval = interval;
}

//rules + also runs pump/light intervals
//if interval is on, use intervals to turn on/off pump/light
//if autopilot is on, use rules to turn on/off pump/light
//both interval and manual light/pump cannot be on at the same time, must be mutually exclusive (in webapp)
//interval and autopilot are mutually exclusive too?
void Controller::autopilotMode(){
    if(Controller::autopilotState){
        //define autopilot rules
    }
    if(Controller::pumpInterval){
        pumpTimer.updateTimer();
        if(pumpTimer.isOn()){
            Controller::updatePumpState(HIGH);
        }else{
            Controller::updatePumpState(LOW);
        }
    }
    if(Controller::lightInterval){
        lightTimer.updateTimer();
        if(lightTimer.isOn()){
            Controller::updateLightState(HIGH);
        }else{
            Controller::updateLightState(LOW);
        }
    }
}