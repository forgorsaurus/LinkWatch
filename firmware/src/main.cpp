#include <Arduino.h>
#include "hw_config.h"
#include "app_config.h"
#include "hal/onboard_led.h"
#include "hal/st7735.h"
#include "hal/spi_bus.h"
#include "hal/rot_enc.h"
#include "hal/w5500.h"
#include "hal/boot_button.h"
#include "core/sim_probe.h"
#include "core/ping_runner.h"
#include "core/result_json.h"
#include "hmi/ui.h"

RotaryEncoder rotenc = RotaryEncoder(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_SW_PIN, 50);
SPIClass hspi(HSPI);
SPIBus spiTFT(hspi, TFT_SCLK, -1, TFT_MOSI, TFT_CS);
SPIBus spiEth(SPI, W5500_SCLK, W5500_MISO, W5500_MOSI, W5500_CS);
TFTLCD tft(spiTFT.getBus(), TFT_CS, TFT_A0, TFT_RST);
EthModule eth(W5500_CS, W5500_RST);
OnboardLED led;
BootButton bootBtn(BOOT_BTN_PIN);

SimProbe probe;            // nanti diganti probe sungguhan (W5500 + SNMP)
PingRunner runner(probe);
Ui ui(tft.gfx());

void setup() {
  Serial.begin(115200);
  Serial.println("LinkWatch: simulasi Test Ping (data dummy)");

  led.init();
  rotenc.init();
  bootBtn.init();

  spiTFT.init();
  tft.init();
  ui.begin();

  // Deteksi hardware & link W5500 untuk layar bootup
  spiEth.init();
  eth.probe();
  delay(1500);   // beri waktu PHY auto-negotiation sebelum cek link
  bool w5500Ok = eth.isHardwareConnected();
  bool linkUp  = eth.isLinkUp();
  Serial.printf("W5500: %s | Kabel: %s\n", w5500Ok ? "OK" : "TIDAK ADA", linkUp ? "TERSAMBUNG" : "BELUM ADA");

  ui.showBoot(w5500Ok, linkUp);
  delay(2000);

  // Layar Konfigurasi IP (setelah bootup)
  NetConfig userCfg = ui.promptIpConfig(rotenc);

  // Nilai default sebelum eth.init() bila ada field yang kosong / tidak dikonfigurasi user
  const IPAddress defaultIp(DEFAULT_IP[0], DEFAULT_IP[1], DEFAULT_IP[2], DEFAULT_IP[3]);
  const IPAddress defaultDns(DEFAULT_DNS[0], DEFAULT_DNS[1], DEFAULT_DNS[2], DEFAULT_DNS[3]);
  const IPAddress defaultGateway(DEFAULT_GATEWAY[0], DEFAULT_GATEWAY[1], DEFAULT_GATEWAY[2], DEFAULT_GATEWAY[3]);
  const IPAddress defaultSubnet(DEFAULT_SUBNET[0], DEFAULT_SUBNET[1], DEFAULT_SUBNET[2], DEFAULT_SUBNET[3]);

  IPAddress ip     = userCfg.ipSet      ? userCfg.ip      : defaultIp;
  IPAddress dns    = userCfg.dnsSet     ? userCfg.dns     : defaultDns;
  IPAddress gw     = userCfg.gatewaySet ? userCfg.gateway : defaultGateway;
  IPAddress subnet = userCfg.subnetSet  ? userCfg.subnet  : defaultSubnet;

  eth.init(ip, dns, gw, subnet);
  Serial.printf("Net Konfig -> IP: %s | DNS: %s | GW: %s | Mask: %s\n",
                ip.toString().c_str(), dns.toString().c_str(),
                gw.toString().c_str(), subnet.toString().c_str());
}

void loop() {
  // 1) Tombol BOOT = pengganti tombol "Test Ping" di aplikasi
  if (bootBtn.wasPressed() && runner.start()) {
    led.on();
    Serial.printf("[run %u] mulai: %u target, %ux percobaan, jeda %u ms\n",
                  (unsigned)runner.runId(), (unsigned)TARGET_COUNT,
                  (unsigned)PING_ATTEMPTS, (unsigned)PING_INTERVAL_MS);
  }

  // 2) Jalankan scheduler percobaan
  static uint8_t lastAttempt = 0;
  runner.update();
  if (runner.state() != RunState::IDLE && runner.attemptsDone() != lastAttempt) {
    lastAttempt = runner.attemptsDone();
    Serial.printf("[run %u] percobaan %u/%u selesai\n",
                  (unsigned)runner.runId(), (unsigned)lastAttempt, (unsigned)PING_ATTEMPTS);
  }

  // 3) Hasil akhir: tampil di TFT (lewat ui.update) + cetak JSON (nanti jadi payload MQTT)
  if (runner.consumeDone()) {
    led.off();
    Serial.println(resultsToJson(runner, millis() / 1000));
  }

  // 4) Update layar (putar encoder = scroll tabel hasil)
  ui.update(runner, rotenc.getPosition());
  Serial.printf("dir: %d, pos: %d", rotenc.getDirection(), rotenc.getPosition());
}
