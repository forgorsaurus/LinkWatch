#pragma once
#include <Arduino.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>

enum Screen {
    BOOTUP,
    LED_ON,
    LED_OFF
};

class TFTLCD{
    private:
        Adafruit_ST7735 tft;
    public:
        TFTLCD(SPIClass &spiBus, int16_t TFT_CS, int16_t TFT_A0, int16_t TFT_RST);
        void init();
        void clear();
        void setScreen(Screen screen);
};