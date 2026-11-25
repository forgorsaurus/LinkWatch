#include "core/ping_runner.h"
#include <Arduino.h>
#include "app_config.h"

bool PingRunner::start() {
  if (state_ == RunState::RUNNING) return false;
  runId_++;
  attemptsDone_ = 0;
  for (size_t i = 0; i < TARGET_COUNT; i++) {
    results_[i] = HostResult();
    results_[i].simulated = probe_.isSimulated(i);
    rttSum_[i] = 0;
  }
  startedAt_ = millis();
  nextAttemptAt_ = startedAt_;            // percobaan 1 langsung jalan
  state_ = RunState::RUNNING;
  return true;
}

void PingRunner::update() {
  if (state_ != RunState::RUNNING) return;
  if ((int32_t)(millis() - nextAttemptAt_) >= 0) doAttempt();
}

void PingRunner::doAttempt() {
  for (size_t i = 0; i < TARGET_COUNT; i++) {
    uint16_t rtt = 0;
    results_[i].sent++;
    if (probe_.pingOnce(i, rtt)) {
      results_[i].received++;
      rttSum_[i] += rtt;
    }
  }
  attemptsDone_++;

  if (attemptsDone_ >= PING_ATTEMPTS) {
    // SNMP dibaca sekali, bersamaan dengan percobaan terakhir
    for (size_t i = 0; i < TARGET_COUNT; i++) results_[i].portStatus = probe_.readPortStatus(i);
    finalize();
  } else {
    nextAttemptAt_ += PING_INTERVAL_MS;
  }
}

void PingRunner::finalize() {
  for (size_t i = 0; i < TARGET_COUNT; i++) {
    HostResult& r = results_[i];
    r.reply = r.received > 0;
    r.rttMs = r.received ? (uint16_t)((rttSum_[i] + r.received / 2) / r.received) : 0;
  }
  state_ = RunState::DONE;
  doneFlag_ = true;
}

bool PingRunner::consumeDone() {
  bool d = doneFlag_;
  doneFlag_ = false;
  return d;
}

uint32_t PingRunner::msToNextAttempt() const {
  if (state_ != RunState::RUNNING) return 0;
  int32_t d = (int32_t)(nextAttemptAt_ - millis());
  return d > 0 ? (uint32_t)d : 0;
}

uint8_t PingRunner::progressPct() const {
  if (state_ == RunState::IDLE) return 0;
  if (state_ == RunState::DONE) return 100;
  uint32_t total = (uint32_t)(PING_ATTEMPTS - 1) * PING_INTERVAL_MS;
  if (total == 0) return 100;
  uint32_t pct = (millis() - startedAt_) * 100UL / total;
  return pct > 100 ? 100 : (uint8_t)pct;
}
