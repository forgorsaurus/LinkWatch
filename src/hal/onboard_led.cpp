#include "onboard_led.h"

void OnboardLED::init() {
    pinMode(ONBOARD_LED_PIN, OUTPUT); // inisialisasi
}

void OnboardLED::on(){
    digitalWrite(ONBOARD_LED_PIN, HIGH); // idupin
}

void OnboardLED::off(){
    digitalWrite(ONBOARD_LED_PIN, LOW); // matiin
}

void OnboardLED::toggle(){
    digitalWrite(ONBOARD_LED_PIN, !digitalRead(ONBOARD_LED_PIN)); // atur output menjadi kebalikan dari kondisi output pin
}

