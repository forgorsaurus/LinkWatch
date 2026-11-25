#pragma once
#include <stddef.h>
#include <stdint.h>
#include "core/probe.h"
#include "core/targets.h"

enum class RunState : uint8_t { IDLE, RUNNING, DONE };

struct HostResult {
  PortStatus portStatus = PortStatus::NA;
  bool       reply      = false;   // true jika minimal 1 dari N percobaan dibalas
  uint8_t    sent       = 0;
  uint8_t    received   = 0;
  uint16_t   rttMs      = 0;       // rata-rata RTT percobaan yang berhasil
  bool       simulated  = true;
};

class PingRunner {
 public:
  explicit PingRunner(INetProbe& probe) : probe_(probe) {}

  bool start();                 // false jika sedang RUNNING
  void update();                // panggil terus di loop()
  bool consumeDone();           // true satu kali setelah run selesai

  RunState          state() const         { return state_; }
  uint8_t           attemptsDone() const  { return attemptsDone_; }
  uint32_t          runId() const         { return runId_; }
  const HostResult* results() const       { return results_; }
  uint32_t          msToNextAttempt() const;
  uint8_t           progressPct() const;

 private:
  void doAttempt();
  void finalize();

  INetProbe& probe_;
  RunState   state_         = RunState::IDLE;
  uint8_t    attemptsDone_  = 0;
  uint32_t   nextAttemptAt_ = 0;
  uint32_t   startedAt_     = 0;
  uint32_t   runId_         = 0;
  bool       doneFlag_      = false;
  HostResult results_[TARGET_COUNT];
  uint32_t   rttSum_[TARGET_COUNT];
};