#pragma once
#include <Adafruit_ST7735.h>
#include "core/ping_runner.h"

// Layout untuk TFT landscape 160 x 128 (setRotation(1)), font bawaan 6x8 px
constexpr int SCR_W        = 160;
constexpr int ROW_Y0       = 28;
constexpr int ROW_H        = 10;
constexpr int ROWS_VISIBLE = 8;

// State untuk layar Konfigurasi IP
constexpr uint8_t IP_CFG_FIELD_COUNT = 4;
constexpr uint8_t IP_CFG_ITEM_COUNT  = 5;  // 4 field + tombol Confirm

struct IpField {
  int16_t octets[4];  // -1 = belum diisi ("___"), 0..255 = nilai oktet

  bool isComplete() const {
    return octets[0] >= 0 && octets[1] >= 0 && octets[2] >= 0 && octets[3] >= 0;
  }
};

struct IpConfigState {
  IpField fields[IP_CFG_FIELD_COUNT];
  uint8_t selectedItem = 0;   // 0=IP, 1=DNS, 2=Default Gateway, 3=Subnet Mask, 4=Confirm
  int8_t  editingOctet = -1;  // -1 = pilih section, 0..3 = edit oktet ke-n
};

// Layar lama (stub)
void drawBootup(Adafruit_ST7735 &tft);
void drawLED_ON(Adafruit_ST7735 &tft);
void drawLED_OFF(Adafruit_ST7735 &tft);
void drawColorBars(Adafruit_ST7735 &tft);

// Layar LinkWatch
void drawBootup(Adafruit_ST7735 &tft, bool w5500Ok, bool linkUp);
void drawIpConfigScreen(Adafruit_ST7735 &tft, const IpConfigState &st);
void drawIpConfigItem(Adafruit_ST7735 &tft, const IpConfigState &st, uint8_t itemIdx);
void drawIpConfigOctets(Adafruit_ST7735 &tft, const IpConfigState &st, uint8_t fieldIdx);
void drawIdle(Adafruit_ST7735 &tft);
void drawRunningFrame(Adafruit_ST7735 &tft);
void drawRunningProgress(Adafruit_ST7735 &tft, uint8_t done, uint8_t total, uint8_t secLeft, uint8_t pct);
void drawResultFrame(Adafruit_ST7735 &tft, uint32_t runId);
void drawResultRows(Adafruit_ST7735 &tft, const HostResult *res, size_t first);
void drawResultFooter(Adafruit_ST7735 &tft, size_t first);
