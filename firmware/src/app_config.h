#pragma once
#include <stdint.h>

// Parameter alur Test Ping (keputusan tim)
constexpr uint8_t  PING_ATTEMPTS    = 3;     // jumlah percobaan
constexpr uint32_t PING_INTERVAL_MS = 5000;  // jeda antar percobaan
constexpr int      SCROLL_DIR       = -1;     // ubah ke -1 kalau arah putar encoder terbalik
