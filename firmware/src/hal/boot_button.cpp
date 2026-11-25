#include "hal/boot_button.h"

void BootButton::init() {
  pinMode(pin_, INPUT_PULLUP);
}

bool BootButton::wasPressed() {
  bool raw = digitalRead(pin_);
  if (raw != lastRaw_) {
    lastRaw_ = raw;
    lastChange_ = millis();
  }
  if (millis() - lastChange_ >= debounce_ && raw != stable_) {
    stable_ = raw;
    if (stable_ == LOW) return true;
  }
  return false;
}
