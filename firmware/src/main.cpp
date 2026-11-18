#include <Arduino.h>
#include "hal/onboard_led.h"
#include "hal/st7735.h"
#include "hal/i2c.h"
#include "hal/rot_enc.h"

unsigned long time_last = 0; // untuk millis, time_last diinisialisasi 0
RotaryEncoder rotenc = RotaryEncoder(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_SW_PIN, 50);

void setup() {
  Serial.begin(115200);
  Serial.println("halo");
  rotenc.init();
}

void loop() {
  if (millis() - time_last >= 100)
  {
    Serial.print("pos: ");
    Serial.print(rotenc.getPosition());
    Serial.print(" | dir: ");
    Serial.print(rotenc.getDirection());
    Serial.print(" | btn: ");
    Serial.println(rotenc.getButtonState());
    time_last = millis();
  }
  
  
}
