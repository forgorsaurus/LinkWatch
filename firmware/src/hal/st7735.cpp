#include "st7735.h"
#include "hmi/screens.h"

TFTLCD::TFTLCD(SPIClass &spiBus, int16_t TFT_CS, int16_t TFT_A0, int16_t TFT_RST) : tft(&spiBus, TFT_CS, TFT_A0, TFT_RST) {
}

void TFTLCD::init(){
    tft.initR(INITR_GREENTAB);
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
    
    default:
        break;
    }
}

