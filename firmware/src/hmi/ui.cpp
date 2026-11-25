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
