#include <Arduino.h>
#include "hw_config.h"
#include "hal/onboard_led.h"
#include "hal/st7735.h"
#include "hal/spi_bus.h"
#include "hal/rot_enc.h"
#include "hal/w5500.h"

unsigned long time_last = 0; // untuk millis, time_last diinisialisasi 0
RotaryEncoder rotenc = RotaryEncoder(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_SW_PIN, 50);

SPIClass hspi(HSPI);

SPIBus spiTFT(hspi, TFT_SCLK, -1, TFT_MOSI, TFT_CS);
SPIBus spiEth(SPI, W5500_SCLK, W5500_MISO, W5500_MOSI, W5500_CS);

TFTLCD tft(spiTFT.getBus(), TFT_CS, TFT_A0, TFT_RST);
EthModule eth(W5500_CS, W5500_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("halo");
  rotenc.init();
  spiTFT.init();
  tft.init();
  tft.setScreen(COLORBAR);

  spiEth.init();
  if (eth.init()) {
    Serial.print("Ethernet DHCP IP: ");
    Serial.println(eth.getLocalIP());
  } else {
    Serial.println("Ethernet DHCP gagal / kabel belum terpasang");
  }
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
