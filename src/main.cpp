#include <Arduino.h>
#include "hal/onboard_led.h"
#include "hal/ssd1306.h"
#include "hal/i2c.h"

unsigned long time_last = 0; // untuk millis, time_last diinisialisasi 0
I2C i2c;
OnboardLED led;
OLED oled;

void setup() {
  Serial.begin(115200);
  Serial.println("halo");
  i2c.init();

  led.init();
  led.off(); // mattin led

  oled.init();

  oled.setScreen(BOOTUP);
  delay(3000);
  time_last = millis();
  
}

void loop() {
  // ingat! 3000ms = 3 detik
  // jika saat cek waktu (millis) ternyata selisihnya dengan waktu terakhir adalah 3 detik
  if (millis()-time_last >= 3000) // iterasi pertama saat millis = 3000 dan time_last = 0
  {
    led.toggle();
    Serial.print("LED status: ");
    Serial.println(led.status());
    if (led.status() == HIGH)
    {
      oled.setScreen(LED_ON);
    } else oled.setScreen(LED_OFF);
    
    time_last = millis();// update time_last jadi waktu baru, dalam hal ini 3000
  }
  
}
