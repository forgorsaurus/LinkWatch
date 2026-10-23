#pragma once
#include "Arduino.h"
#include "pinout.h"

class OnboardLED {
    public:
        void init();
        void on();
        void off();
        void toggle();
};