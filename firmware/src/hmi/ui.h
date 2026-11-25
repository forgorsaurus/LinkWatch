#pragma once
#include <Adafruit_ST7735.h>
#include "core/ping_runner.h"

class Ui {
 public:
  explicit Ui(Adafruit_ST7735 &tft) : tft_(tft) {}
  void begin();
  void showBoot(bool w5500Ok, bool linkUp);
  void update(const PingRunner &runner, int encoderPos);   // panggil tiap loop()

 private:
  enum class Mode : uint8_t { NONE, IDLE, RUNNING, RESULT };

  Adafruit_ST7735 &tft_;
  Mode mode_     = Mode::NONE;
  int  lastPos_  = 0;
  int  scroll_   = 0;
  int  lastDone_ = -1;
  int  lastSec_  = -1;
  int  lastPct_  = -1;
};
