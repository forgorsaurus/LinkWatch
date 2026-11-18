#include "rot_enc.h"

RotaryEncoder::RotaryEncoder(uint8_t a_clk, uint8_t b_dt, uint8_t SW, unsigned long debounceTime){
    clk_pin = a_clk;
    dt_pin = b_dt;
    sw_pin = SW;
    debounceDuration = debounceTime;
}

void IRAM_ATTR RotaryEncoder::isrWrapper(void* arg){
    static_cast<RotaryEncoder*>(arg)->shaftMoved();
}

void IRAM_ATTR RotaryEncoder::shaftMoved(){
    if (millis() - lastShaftScan > 5){
        if (digitalRead(dt_pin) == 0)
        {
            position++;
            direction = 1;
        }
        if (digitalRead(dt_pin) == 1){
            position--;
            direction = -1;
        }
        lastShaftScan = millis();
    }
}


void RotaryEncoder::init(){
    pinMode(clk_pin, INPUT_PULLUP);
    pinMode(dt_pin, INPUT_PULLUP);
    pinMode(sw_pin, INPUT_PULLUP);
    attachInterruptArg(digitalPinToInterrupt(clk_pin), isrWrapper, this , FALLING);
}

int RotaryEncoder::getPosition(){
    return position;
}

int RotaryEncoder::getDirection(){
    oldDirection = direction;
    direction = 0;
    return oldDirection;
}

bool RotaryEncoder::getButtonState(){
    bool finalState = 0;
    if (millis() - lastTimeButtonStateChange >= debounceDuration){   
        bool buttonState = digitalRead(sw_pin);
        if (buttonState != lastButtonState){
            lastTimeButtonStateChange = millis();
            lastButtonState = buttonState;
            if (buttonState == LOW)
            {
                finalState = 1;
            } else if (buttonState == HIGH){
                finalState = 0;
            }
        }
    }
    return finalState;
}

