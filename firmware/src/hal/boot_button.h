#pragma once
#include <Arduino.h>

// Tombol BOOT (GPIO 0, aktif LOW). wasPressed() bernilai true satu kali per penekanan.
class BootButton {
 public:
  explicit BootButton(uint8_t pin, uint16_t debounceMs = 50) : pin_(pin), debounce_(debounceMs) {}
  void init();
  bool wasPressed();

 private:
  uint8_t pin_;
  uint16_t debounce_;
  bool lastRaw_ = HIGH;
  bool stable_ = HIGH;
  unsigned long lastChange_ = 0;
};
