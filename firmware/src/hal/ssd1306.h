#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

enum Screen {
    BOOTUP,
    LED_ON,
    LED_OFF
};

class OLED{
    public:
        void init();
        void clear();
        void setScreen(Screen screen);
};