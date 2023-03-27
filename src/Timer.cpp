#include <Timer.hpp>

void Timer::initTimer(unsigned long on, unsigned long off){
    Timer::intervalOn = on;
    Timer::intervalOff = off;
    Timer::lastSaved = 0;
    Timer::timerState = true;
}

void Timer::startTimer(){
    Timer::intervalRunning = true; //intervalRunning starts/stops the running of this Timer and resume from wherever it left off
}

void Timer::stopTimer(){
    Timer::intervalRunning = false;
}

void Timer::updateTimer(){
    
    Timer::now = millis();
    if(intervalRunning){
        if(Timer::timerState){ //if timerstate = 'true' then it is ON( how long it should be on )
            unsigned long diff = now - lastSaved;
            Timer::elapsed+=diff;
            if(Timer::elapsed >= intervalOn){
                Timer::timerState = false; //put it in offstate
                Timer::elapsed = 0;
            }
        }
        else{
            unsigned long diff = now - lastSaved;
            Timer::elapsed+=diff;
            if(Timer::elapsed >= intervalOff){
                Timer::timerState = true; //put it in offstate
                Timer::elapsed = 0;
            }
        }
    }
    Timer::lastSaved = now;
}

bool Timer::isOn(){
    return Timer::timerState;
}

