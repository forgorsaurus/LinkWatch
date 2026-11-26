#include "hmi/ui.h"
#include "hmi/screens.h"
#include "app_config.h"

void Ui::begin() {
  tft_.setRotation(1);          // landscape 160 x 128
  tft_.setTextWrap(false);
  tft_.fillScreen(0x0000);
}

void Ui::showBoot(bool w5500Ok, bool linkUp) {
  drawBootup(tft_, w5500Ok, linkUp);
}

static IPAddress fieldToIp(const IpField &f) {
  return IPAddress((uint8_t)f.octets[0], (uint8_t)f.octets[1],
                   (uint8_t)f.octets[2], (uint8_t)f.octets[3]);
}

NetConfig Ui::promptIpConfig(RotaryEncoder &rotenc) {
  IpConfigState st;
  // IP, DNS, Default Gateway awalnya ___.___.___.___
  for (uint8_t i = 0; i < 3; i++) {
    st.fields[i] = {{-1, -1, -1, -1}};
  }
  // Subnet Mask awalnya 255.255.255.___
  st.fields[3] = {{255, 255, 255, -1}};
  st.selectedItem = 0;
  st.editingOctet = -1;

  drawIpConfigScreen(tft_, st);

  // Sinkronkan posisi awal & bersihkan event klik sisa sebelum mulai interaksi
  int lastPos = rotenc.getPosition();
  (void)rotenc.getButtonState();

  while (true) {
    int pos = rotenc.getPosition();
    int d = (pos - lastPos) * SCROLL_DIR;
    if (d != 0) {
      lastPos = pos;
      if (st.editingOctet < 0) {
        // Mode pilih section (0..4)
        int nextItem = constrain((int)st.selectedItem + d, 0, (int)IP_CFG_ITEM_COUNT - 1);
        if (nextItem != (int)st.selectedItem) {
          uint8_t prevItem = st.selectedItem;
          st.selectedItem = (uint8_t)nextItem;
          drawIpConfigItem(tft_, st, prevItem);
          drawIpConfigItem(tft_, st, st.selectedItem);
        }
      } else {
        // Mode edit oktet (wrap-around 0..255)
        IpField &f = st.fields[st.selectedItem];
        int val = ((int)f.octets[st.editingOctet] + d) % 256;
        if (val < 0) val += 256;
        f.octets[st.editingOctet] = (int16_t)val;
        drawIpConfigOctets(tft_, st, st.selectedItem);
      }
    }

    if (rotenc.getButtonState()) {
      if (st.editingOctet < 0) {
        if (st.selectedItem == IP_CFG_FIELD_COUNT) {
          // Tombol | Confirm | ditekan -> selesai konfigurasi
          break;
        }
        // Masuk mode edit oktet pertama (0)
        st.editingOctet = 0;
        if (st.fields[st.selectedItem].octets[0] < 0) {
          st.fields[st.selectedItem].octets[0] = 0;
        }
        drawIpConfigItem(tft_, st, st.selectedItem);
      } else {
        // Lanjut ke oktet berikutnya, atau kembali ke mode pilih section setelah oktet ke-4
        if (st.editingOctet < 3) {
          st.editingOctet++;
          if (st.fields[st.selectedItem].octets[st.editingOctet] < 0) {
            st.fields[st.selectedItem].octets[st.editingOctet] = 0;
          }
          drawIpConfigOctets(tft_, st, st.selectedItem);
        } else {
          st.editingOctet = -1;
          drawIpConfigItem(tft_, st, st.selectedItem);
        }
      }
    }

    delay(5);
  }

  NetConfig out;
  if (st.fields[0].isComplete()) {
    out.ipSet = true;
    out.ip = fieldToIp(st.fields[0]);
  }
  if (st.fields[1].isComplete()) {
    out.dnsSet = true;
    out.dns = fieldToIp(st.fields[1]);
  }
  if (st.fields[2].isComplete()) {
    out.gatewaySet = true;
    out.gateway = fieldToIp(st.fields[2]);
  }
  if (st.fields[3].isComplete()) {
    out.subnetSet = true;
    out.subnet = fieldToIp(st.fields[3]);
  }
  return out;
}

void Ui::update(const PingRunner &r, int pos) {
  Mode want = Mode::IDLE;
  if (r.state() == RunState::RUNNING)   want = Mode::RUNNING;
  else if (r.state() == RunState::DONE) want = Mode::RESULT;

  // ganti layar -> gambar ulang penuh
  if (want != mode_) {
    mode_ = want;
    lastDone_ = lastSec_ = lastPct_ = -1;
    scroll_ = 0;
    lastPos_ = pos;
    switch (mode_) {
      case Mode::IDLE:    drawIdle(tft_); break;
      case Mode::RUNNING: drawRunningFrame(tft_); break;
      case Mode::RESULT:
        drawResultFrame(tft_, r.runId());
        drawResultRows(tft_, r.results(), scroll_);
        drawResultFooter(tft_, scroll_);
        break;
      default: break;
    }
  }

  if (mode_ == Mode::RUNNING) {
    int done = r.attemptsDone();
    int sec  = (int)((r.msToNextAttempt() + 999) / 1000);
    int pct  = r.progressPct();
    if (done != lastDone_ || sec != lastSec_ || pct != lastPct_) {
      drawRunningProgress(tft_, done, PING_ATTEMPTS, sec, pct);
      lastDone_ = done; lastSec_ = sec; lastPct_ = pct;
    }
  } else if (mode_ == Mode::RESULT) {
    int d = (pos - lastPos_) * SCROLL_DIR;
    if (d != 0) {
      lastPos_ = pos;
      int maxScroll = (int)TARGET_COUNT - ROWS_VISIBLE;
      if (maxScroll < 0) maxScroll = 0;
      int ns = constrain(scroll_ + d, 0, maxScroll);
      if (ns != scroll_) {
        scroll_ = ns;
        drawResultRows(tft_, r.results(), scroll_);
        drawResultFooter(tft_, scroll_);
      }
    }
  }
}
