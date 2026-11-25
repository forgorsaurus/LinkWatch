#pragma once
#include <stddef.h>
#include <stdint.h>
#include "core/targets.h"

// Antarmuka "sumber data" jaringan. Sekarang diisi SimProbe (dummy),
// nanti diganti probe sungguhan (ICMP + SNMP lewat W5500) tanpa mengubah kode lain.
class INetProbe {
 public:
  virtual ~INetProbe() {}
  virtual bool pingOnce(size_t idx, uint16_t& rttMs) = 0;   // true = ada balasan
  virtual PortStatus readPortStatus(size_t idx) = 0;        // SNMP: UP / DOWN / NA
  virtual bool isSimulated(size_t idx) const = 0;
};
