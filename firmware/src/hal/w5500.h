#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

class EthModule {
    private:
        byte mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
        bool hasReset = false;
        bool isInitialized = false;
        int16_t cs_pin;
        int16_t rst_pin;
        void hardReset();

    public:
        EthModule(int16_t cs_pin, int16_t rst_pin = -1);
        void setMac(const byte new_mac[6]);
        void probe();                                                     // Deteksi chip & link sebelum set IP
        bool init();                                                      // DHCP
        void init(IPAddress ip, IPAddress dns, IPAddress gw, IPAddress subnet); // Static IP
        bool isHardwareConnected();
        bool isLinkUp();
        IPAddress getLocalIP();
        void maintain();
};
