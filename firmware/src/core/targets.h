#pragma once
#include <stddef.h>
#include <stdint.h>

enum class PortStatus : uint8_t { UP, DOWN, NA };

inline const char* portStatusText(PortStatus s) {
  return s == PortStatus::UP ? "UP" : (s == PortStatus::DOWN ? "DOWN" : "N/A");
}

struct HostTarget {
  const char* name;   // maks 8 karakter (muat di TFT)
  const char* port;   // maks 5 karakter
  const char* ip;     // IP perangkat yang terhubung di port itu
  bool sameSubnet;    // true: nanti diping sungguhan lewat W5500, false: tetap simulasi (subnet lain)
};

constexpr size_t TARGET_COUNT = 12;
extern const HostTarget TARGETS[TARGET_COUNT];
