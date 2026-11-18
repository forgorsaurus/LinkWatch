#pragma once
#include <Arduino.h>

class RotaryEncoder {
    private:
        uint8_t clk_pin;
        uint8_t dt_pin;
        uint8_t sw_pin;
        
        volatile int position = 0;
        volatile int direction = 0; //-1 ccw, 1 cw
        volatile int oldDirection = 0; //-1 ccw, 1 cw
        volatile unsigned long lastShaftScan = 0;

        unsigned long lastTimeButtonStateChange = 0;
        unsigned long debounceDuration;
        bool oldButtonState = 0;
        bool lastButtonState = HIGH;
        
        //wrapper
        static void IRAM_ATTR isrWrapper(void* arg);
        //interrupt service routine
        void IRAM_ATTR shaftMoved();
    public:
        RotaryEncoder(uint8_t clk, uint8_t dt, uint8_t SW, unsigned long debounceTime);
        void init();
        int getPosition();
        int getDirection();
        bool getButtonState();
};