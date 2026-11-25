#pragma once
#include "core/probe.h"

class SimProbe : public INetProbe {
 public:
  bool pingOnce(size_t idx, uint16_t& rttMs) override;
  PortStatus readPortStatus(size_t idx) override;
  bool isSimulated(size_t) const override { return true; }
};
