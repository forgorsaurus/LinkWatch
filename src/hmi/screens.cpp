#include "screens.h"

void drawBootup(Adafruit_SSD1306 &display) {
    display.clearDisplay();
    // string 1
    display.setTextColor(1);
    display.setTextWrap(false);
    display.setCursor(17, 4);
    display.print("A Project by ARC");
    // string 2
    display.setFont(&FreeSerifItalic12pt7b);
    display.setCursor(12, 34);
    display.print("LinkWatch");
    // string 3
    display.setFont();
    display.setCursor(92, 36);
    display.print("V1.0");
    // string 4
    display.setCursor(2, 49);
    display.print("Remote Network Tester");
    display.display();
}


void drawLED_ON(Adafruit_SSD1306 &display) {
    display.clearDisplay();
    // string 1
    display.setTextColor(1);
    display.setTextWrap(false);
    display.setCursor(32, 4);
    display.print("LED Testing");
    // string 2
    display.setFont(&FreeSerifItalic12pt7b);
    display.setCursor(23, 37);
    display.print("LED ON");
    // string 3
    display.setFont();
    display.setCursor(53, 46);
    display.print("Yay!");
    display.display();
}

void drawLED_OFF(Adafruit_SSD1306 &display) {
    display.clearDisplay();
    // string 2
    display.setTextColor(1);
    display.setTextWrap(false);
    display.setFont(&FreeSerifItalic12pt7b);
    display.setCursor(17, 37);
    display.print("LED OFF");
    // string 3
    display.setFont();
    display.setCursor(47, 46);
    display.print("NOO!!!");
    // string 1
    display.setCursor(32, 4);
    display.print("LED Testing");
    display.display();
}


