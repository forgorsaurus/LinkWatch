#pragma once
#include <stdint.h>

// Parameter alur Test Ping (keputusan tim)
constexpr uint8_t  PING_ATTEMPTS    = 3;     // jumlah percobaan
constexpr uint32_t PING_INTERVAL_MS = 5000;  // jeda antar percobaan
constexpr int      SCROLL_DIR       = -1;    // ubah ke -1 kalau arah putar encoder terbalik

// Konfigurasi jaringan default (digunakan bila field pada layar Konfigurasi IP dikosongkan)
constexpr uint8_t DEFAULT_IP[4]      = {192, 168, 88, 50};
constexpr uint8_t DEFAULT_DNS[4]     = {8, 8, 8, 8};
constexpr uint8_t DEFAULT_GATEWAY[4] = {192, 168, 88, 1};
constexpr uint8_t DEFAULT_SUBNET[4]  = {255, 255, 255, 0};

