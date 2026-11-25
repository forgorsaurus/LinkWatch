#include "hmi/screens.h"
#include <stdio.h>
#include <string.h>
#include "hmi/colors.h"
#include "app_config.h"

// ---------- helper ----------
static void txt(Adafruit_ST7735 &tft, int x, int y, uint16_t fg, uint16_t bg,
                const char *s, uint8_t size = 1) {
  tft.setTextSize(size);
  tft.setTextColor(fg, bg);
  tft.setCursor(x, y);
  tft.print(s);
}

static void header(Adafruit_ST7735 &tft, const char *right) {
  tft.fillRect(0, 0, SCR_W, 14, Color::PINK);
  txt(tft, 4, 3, Color::WHITE, Color::PINK, "LinkWatch");
  int w = (int)strlen(right) * 6;
  txt(tft, SCR_W - 4 - w, 3, Color::WHITE, Color::PINK, right);
}

// ---------- layar lama (stub) ----------
void drawBootup(Adafruit_ST7735 &tft) {}
void drawLED_ON(Adafruit_ST7735 &tft) {}
void drawLED_OFF(Adafruit_ST7735 &tft) {}
void drawColorBars(Adafruit_ST7735 &tft) {
  uint16_t colors[] = { ST77XX_WHITE, ST77XX_YELLOW, ST77XX_CYAN, ST77XX_GREEN,
                        ST77XX_MAGENTA, ST77XX_RED, ST77XX_BLUE, ST77XX_BLACK };
  int barWidth = tft.width() / 8;
  int height = tft.height();
  for (int i = 0; i < 8; i++) {
    tft.fillRect(i * barWidth, 0, barWidth, height, colors[i]);
  }
}

// ---------- boot ----------
void drawBootup(Adafruit_ST7735 &tft, bool w5500Ok, bool linkUp) {
  tft.fillScreen(Color::BG);
  txt(tft, 26, 22, Color::PINK, Color::BG, "LinkWatch", 2);
  txt(tft, 8, 48, Color::GRAY, Color::BG, "Network Monitoring Probe");
  txt(tft, 8, 76, Color::WHITE, Color::BG, "W5500 :");
  txt(tft, 64, 76, w5500Ok ? Color::GREEN : Color::RED, Color::BG, w5500Ok ? "OK" : "TIDAK ADA");
  txt(tft, 8, 90, Color::WHITE, Color::BG, "Kabel :");
  txt(tft, 64, 90, linkUp ? Color::GREEN : Color::YELLOW, Color::BG, linkUp ? "TERSAMBUNG" : "BELUM ADA");
}

// ---------- idle ----------
void drawIdle(Adafruit_ST7735 &tft) {
  tft.fillScreen(Color::BG);
  header(tft, "SIAP");
  txt(tft, 20, 40, Color::WHITE, Color::BG, "Tekan BOOT", 2);
  txt(tft, 35, 62, Color::GRAY, Color::BG, "untuk Test Ping");
  char b[32];
  snprintf(b, sizeof b, "%u target | %ux | jeda %us",
           (unsigned)TARGET_COUNT, (unsigned)PING_ATTEMPTS, (unsigned)(PING_INTERVAL_MS / 1000));
  int w = (int)strlen(b) * 6;
  txt(tft, (SCR_W - w) / 2, 96, Color::LIGHT, Color::BG, b);
}

// ---------- running ----------
void drawRunningFrame(Adafruit_ST7735 &tft) {
  tft.fillScreen(Color::BG);
  header(tft, "RUN");
  txt(tft, 26, 24, Color::PINK, Color::BG, "Test Ping", 2);
  txt(tft, 35, 44, Color::GRAY, Color::BG, "sedang berjalan");
  tft.drawRect(10, 92, 140, 10, Color::GRAY);
  txt(tft, 8, 110, Color::GRAY, Color::BG, "SNMP: percobaan terakhir");
}

void drawRunningProgress(Adafruit_ST7735 &tft, uint8_t done, uint8_t total, uint8_t secLeft, uint8_t pct) {
  char b[28];
  snprintf(b, sizeof b, "Selesai    : %u/%u  ", (unsigned)done, (unsigned)total);
  txt(tft, 8, 62, Color::WHITE, Color::BG, b);
  snprintf(b, sizeof b, "Berikutnya : %u dtk ", (unsigned)secLeft);
  txt(tft, 8, 74, Color::WHITE, Color::BG, b);
  tft.fillRect(11, 93, 138, 8, Color::BG);
  tft.fillRect(11, 93, 138 * pct / 100, 8, Color::PINK);
}

// ---------- hasil ----------
void drawResultFrame(Adafruit_ST7735 &tft, uint32_t runId) {
  tft.fillScreen(Color::BG);
  char r[12];
  snprintf(r, sizeof r, "Run #%u", (unsigned)runId);
  header(tft, r);
  txt(tft, 6,   17, Color::GRAY, Color::BG, "NAMA");
  txt(tft, 60,  17, Color::GRAY, Color::BG, "PORT");
  txt(tft, 96,  17, Color::GRAY, Color::BG, "STAT");
  txt(tft, 126, 17, Color::GRAY, Color::BG, "PING");
  tft.drawFastHLine(0, 26, SCR_W, Color::GRAY);
}

void drawResultRows(Adafruit_ST7735 &tft, const HostResult *res, size_t first) {
  for (int line = 0; line < ROWS_VISIBLE; line++) {
    int y = ROW_Y0 + line * ROW_H;
    tft.fillRect(0, y, SCR_W, ROW_H, Color::BG);
    size_t i = first + line;
    if (i >= TARGET_COUNT) continue;

    const HostTarget &t = TARGETS[i];
    const HostResult &r = res[i];

    txt(tft, 0,  y + 1, Color::GRAY,  Color::BG, r.simulated ? "*" : " ");
    txt(tft, 6,  y + 1, Color::WHITE, Color::BG, t.name);
    txt(tft, 60, y + 1, Color::LIGHT, Color::BG, t.port);

    uint16_t sc = r.portStatus == PortStatus::UP ? Color::GREEN
                : (r.portStatus == PortStatus::DOWN ? Color::RED : Color::GRAY);
    txt(tft, 96, y + 1, sc, Color::BG, portStatusText(r.portStatus));

    char b[8];
    uint16_t pc;
    if (r.received == 0) {
      strcpy(b, "NoRep");
      pc = Color::RED;
    } else {
      unsigned ms = r.rttMs > 999 ? 999 : r.rttMs;
      snprintf(b, sizeof b, "%ums", ms);
      pc = (r.received == r.sent) ? Color::GREEN : Color::YELLOW;   // kuning = kadang tidak membalas
    }
    txt(tft, 126, y + 1, pc, Color::BG, b);
  }
}

void drawResultFooter(Adafruit_ST7735 &tft, size_t first) {
  tft.drawFastHLine(0, 113, SCR_W, Color::GRAY);
  tft.fillRect(0, 114, SCR_W, 14, Color::BG);
  txt(tft, 2, 117, Color::GRAY, Color::BG, "BOOT:ulang *=SIM");
  size_t last = first + ROWS_VISIBLE;
  if (last > TARGET_COUNT) last = TARGET_COUNT;
  char b[12];
  snprintf(b, sizeof b, "%u-%u/%u", (unsigned)(first + 1), (unsigned)last, (unsigned)TARGET_COUNT);
  txt(tft, SCR_W - 2 - (int)strlen(b) * 6, 117, Color::WHITE, Color::BG, b);
}
