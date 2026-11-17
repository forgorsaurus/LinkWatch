#include "onboard_led.h"

void OnboardLED::init() {
    pinMode(ONBOARD_LED_PIN, OUTPUT);
}

void OnboardLED::on(){
    digitalWrite(ONBOARD_LED_PIN, HIGH); // idupin
    LEDstate = HIGH;
}

void OnboardLED::off(){
    digitalWrite(ONBOARD_LED_PIN, LOW); // matiin
    LEDstate = LOW;
}

void OnboardLED::toggle(){
    digitalWrite(ONBOARD_LED_PIN, !LEDstate); // atur output menjadi kebalikan dari kondisi output pin
    LEDstate = !LEDstate;
}

bool OnboardLED::status(){
    return LEDstate;
}

