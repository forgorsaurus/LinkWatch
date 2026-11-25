#include "core/result_json.h"

String resultsToJson(const PingRunner& runner, uint32_t uptimeSec) {
  const HostResult* res = runner.results();
  String s;
  s.reserve(170 * TARGET_COUNT + 80);
  s += "{\"runId\":\"r";     s += (unsigned)runner.runId();
  s += "\",\"uptimeSec\":";  s += (unsigned)uptimeSec;
  s += ",\"results\":[";
  for (size_t i = 0; i < TARGET_COUNT; i++) {
    const HostTarget& t = TARGETS[i];
    const HostResult& r = res[i];
    if (i) s += ',';
    s += "{\"device\":\"";   s += t.name;
    s += "\",\"port\":\"";   s += t.port;
    s += "\",\"ip\":\"";     s += t.ip;
    s += "\",\"portStatus\":\""; s += portStatusText(r.portStatus);
    s += "\",\"ping\":{\"reply\":"; s += r.reply ? "true" : "false";
    s += ",\"rttMs\":";      s += (unsigned)r.rttMs;
    s += ",\"sent\":";       s += (unsigned)r.sent;
    s += ",\"received\":";   s += (unsigned)r.received;
    s += "},\"simulated\":"; s += r.simulated ? "true" : "false";
    s += '}';
  }
  s += "]}";
  return s;
}
