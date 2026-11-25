#include "core/sim_probe.h"
#include <Arduino.h>

struct SimProfile {
  uint8_t    replyPct;  // peluang satu ping dibalas (0-100)
  uint16_t   baseRtt;   // ms
  uint8_t    jitter;    // ms, ditambah acak 0..jitter
  PortStatus port;      // hasil "SNMP"
  bool       snmpOk;    // false -> N/A
};

// Urutan HARUS sama dengan TARGETS[]
static const SimProfile PROFILES[] = {
  // replyPct baseRtt jitter port              snmpOk
  {100,  1, 1,  PortStatus::UP,   true },   // Router 1 Gi0/0  normal
  {100,  1, 1,  PortStatus::UP,   true },   // Switch 1 Fa0/1  normal
  {100,  2, 2,  PortStatus::UP,   true },   // PC-Lab1         normal
  { 60,  3, 4,  PortStatus::UP,   true },   // PC-Lab2         tidak stabil
  {  0,  0, 0,  PortStatus::DOWN, true },   // AP-1            link putus
  {100,  5, 3,  PortStatus::UP,   true },   // Router 2 Gi0/0  normal
  {  0,  0, 0,  PortStatus::DOWN, true },   // Router 2 Gi0/1  link putus
  {100,  6, 3,  PortStatus::UP,   true },   // Switch 2 Fa0/1  normal
  {100,  7, 3,  PortStatus::UP,   true },   // Switch 2 Fa0/2  normal
  {  0,  0, 0,  PortStatus::UP,   true },   // Srv-DB          port hidup, tidak membalas
  { 85, 45, 20, PortStatus::UP,   true },   // Srv-Web         lambat
  {100, 12, 5,  PortStatus::UP,   false},   // CCTV-1          SNMP tidak menjawab
};
static_assert(sizeof(PROFILES) / sizeof(PROFILES[0]) == TARGET_COUNT,
              "PROFILES harus sama jumlahnya dengan TARGETS");

bool SimProbe::pingOnce(size_t idx, uint16_t& rttMs) {
  const SimProfile& p = PROFILES[idx];
  if (random(100) >= p.replyPct) return false;
  rttMs = p.baseRtt + (p.jitter ? (uint16_t)random(p.jitter + 1) : 0);
  return true;
}

PortStatus SimProbe::readPortStatus(size_t idx) {
  const SimProfile& p = PROFILES[idx];
  return p.snmpOk ? p.port : PortStatus::NA;
}
