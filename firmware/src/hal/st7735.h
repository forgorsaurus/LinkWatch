#pragma once
#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

enum Screen {
    BOOTUP,
    LED_ON,
    LED_OFF,
    COLORBAR
};

class TFTLCD{
    private:
        Adafruit_ST7735 tft;
        bool isInitialized = false;
    public:
        TFTLCD(SPIClass &spiBus, int16_t cs_pin, int16_t a0_pin, int16_t rst_pin);
        void init();
        void clear();
        void setScreen(Screen screen);
        Adafruit_ST7735& gfx() {return tft; }
};