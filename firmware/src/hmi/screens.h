#pragma once
#include <Adafruit_ST7735.h>
#include "core/ping_runner.h"

// Layout untuk TFT landscape 160 x 128 (setRotation(1)), font bawaan 6x8 px
constexpr int SCR_W        = 160;
constexpr int ROW_Y0       = 28;
constexpr int ROW_H        = 10;
constexpr int ROWS_VISIBLE = 8;

// Layar lama (stub)
void drawBootup(Adafruit_ST7735 &tft);
void drawLED_ON(Adafruit_ST7735 &tft);
void drawLED_OFF(Adafruit_ST7735 &tft);
void drawColorBars(Adafruit_ST7735 &tft);

// Layar LinkWatch
void drawBootup(Adafruit_ST7735 &tft, bool w5500Ok, bool linkUp);
void drawIdle(Adafruit_ST7735 &tft);
void drawRunningFrame(Adafruit_ST7735 &tft);
void drawRunningProgress(Adafruit_ST7735 &tft, uint8_t done, uint8_t total, uint8_t secLeft, uint8_t pct);
void drawResultFrame(Adafruit_ST7735 &tft, uint32_t runId);
void drawResultRows(Adafruit_ST7735 &tft, const HostResult *res, size_t first);
void drawResultFooter(Adafruit_ST7735 &tft, size_t first);
