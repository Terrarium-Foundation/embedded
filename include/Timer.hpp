#include <Arduino.h>

class Timer{
    public:
        void initTimer(unsigned long on, unsigned long off);
        void updateTimer();
        bool isOn();
        void startTimer();
        void stopTimer();

    private:
        bool timerState; //if true, it is running "on". if false, it is running "off" state
        unsigned lastSaved; //for when interval switched off, save last state so you cna continue from it later
        unsigned long now;
        unsigned long intervalOn;
        unsigned long intervalOff;
        unsigned long elapsed;
        bool intervalRunning;
};