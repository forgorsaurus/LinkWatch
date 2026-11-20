#include "screens.h"

void drawBootup(Adafruit_ST7735 &tft) {
}

void drawLED_ON(Adafruit_ST7735 &tft) {
}

void drawLED_OFF(Adafruit_ST7735 &tft) {
}

void drawColorBars(Adafruit_ST7735 &tft) {
  uint16_t colors[] = {
    ST77XX_WHITE,
    ST77XX_YELLOW,
    ST77XX_CYAN,
    ST77XX_GREEN,
    ST77XX_MAGENTA,
    ST77XX_RED,
    ST77XX_BLUE,
    ST77XX_BLACK
  };
  int barWidth = tft.width() / 8;
  int height = tft.height();
  for (int i = 0; i < 8; i++) {
    tft.fillRect(i * barWidth, 0, barWidth, height, colors[i]);
  }
}


