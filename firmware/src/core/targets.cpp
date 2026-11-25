#include "core/targets.h"

const HostTarget TARGETS[TARGET_COUNT] = {
  // name       port     ip               sameSubnet
  {"Router 1", "Gi0/0", "192.168.88.1",  true },
  {"Switch 1", "Fa0/1", "192.168.88.2",  true },
  {"PC-Lab1",  "Fa0/2", "192.168.88.10", true },
  {"PC-Lab2",  "Fa0/3", "192.168.88.11", true },
  {"AP-1",     "Fa0/4", "192.168.88.20", true },
  {"Router 2", "Gi0/0", "10.0.1.1",      false},
  {"Router 2", "Gi0/1", "10.0.2.1",      false},
  {"Switch 2", "Fa0/1", "10.0.1.2",      false},
  {"Switch 2", "Fa0/2", "10.0.1.3",      false},
  {"Srv-DB",   "Gi0/2", "10.0.2.10",     false},
  {"Srv-Web",  "Gi0/3", "10.0.2.11",     false},
  {"CCTV-1",   "Fa0/5", "10.0.3.20",     false},
};
