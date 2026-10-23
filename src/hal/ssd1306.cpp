#include "ssd1306.h"
#include "hw_config.h"
#include "hmi/screens.h"

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void OLED::init(){
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR, true, false)) {
        Serial.println("SSD1306 begin GAGAL");
    } else {
        Serial.println("SSD1306 OK");
    }
}

void OLED::clear(){
    display.clearDisplay();
}

void OLED::setScreen(Screen screen){
    switch (screen)
    {
    case BOOTUP:
        drawBootup(display);
        break;

    case LED_ON:
        drawLED_ON(display);
        break;

    case LED_OFF:
        drawLED_OFF(display);
        break;
    
    default:
        break;
    }
    
}