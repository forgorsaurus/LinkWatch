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

void TFTLCD::setScreen(Screen screen){
    switch (screen)
    {
    case BOOTUP:
        drawBootup(tft);
        break;

    case LED_ON:
        drawLED_ON(tft);
        break;

    case LED_OFF:
        drawLED_OFF(tft);
        break;

    case COLORBAR:
        drawColorBars(tft);
    break;
    
    default:
        break;
    }
}

