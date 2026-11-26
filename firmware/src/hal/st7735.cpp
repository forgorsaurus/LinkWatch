#include "st7735.h"
#include "hmi/screens.h"

TFTLCD::TFTLCD(SPIClass &spiBus, int16_t cs_pin, int16_t a0_pin, int16_t rst_pin) : tft(&spiBus, cs_pin, a0_pin, rst_pin) {
}

void TFTLCD::init(){
    if (!isInitialized)
    {
        tft.initR(INITR_BLACKTAB);
        isInitialized = true;
    }
}

Adafruit_ST7735& TFTLCD::gfx(){
    return tft;
}

