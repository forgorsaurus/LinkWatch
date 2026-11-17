#pragma once
#include "Arduino.h"
#include "hw_config.h"

class OnboardLED {
    private:
        bool LEDstate;

    public:
        void init();
        void on();
        void off();
        void toggle();
        bool status();
};