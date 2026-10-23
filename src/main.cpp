#include <Arduino.h>
#include "hal/onboard_led.h"

unsigned long time_now, time_last = 0; // untuk millis, time_last diinisialisasi 0
OnboardLED led;

void setup() {
  led.init();
  led.off(); // mattin led
}

void loop() {
  // ingat! 3000ms = 3 detik
  // jika saat cek waktu (millis) ternyata selisihnya dengan waktu terakhir adalah 3 detik
  if (millis()-time_last >= 3000) // iterasi pertama saat millis = 3000 dan time_last = 0
  {
    OnboardLED().toggle();
    time_last = millis();// update time_last jadi waktu baru, dalam hal ini 3000
  }
  
}
