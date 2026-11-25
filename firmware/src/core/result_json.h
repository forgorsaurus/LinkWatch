#pragma once
#include <Arduino.h>
#include "core/ping_runner.h"

// Format yang sama dengan payload MQTT topic linkwatch/{id}/result (nanti tinggal di-publish)
String resultsToJson(const PingRunner& runner, uint32_t uptimeSec);
