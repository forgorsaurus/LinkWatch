#include "w5500.h"
#include <cstring>
#include <esp_system.h>

EthModule::EthModule(int16_t cs_pin, int16_t rst_pin)
    : cs_pin(cs_pin), rst_pin(rst_pin) {
    // Gunakan MAC address bawaan ESP32 (Ethernet base MAC) secara default
    esp_read_mac(this->mac, ESP_MAC_ETH);
}

void EthModule::setMac(const byte new_mac[6]) {
    memcpy(this->mac, new_mac, 6);
}

void EthModule::hardReset() {
    if (rst_pin >= 0) {
        pinMode(rst_pin, OUTPUT);
        digitalWrite(rst_pin, LOW);
        delay(50);
        digitalWrite(rst_pin, HIGH);
        delay(200);
    }
}

bool EthModule::init() {
    if (!isInitialized) {
        hardReset();
        Ethernet.init(cs_pin);
        if (Ethernet.begin(mac) == 0) {
            return false;
        }
        isInitialized = true;
    }
    return true;
}

void EthModule::init(IPAddress ip, IPAddress dns, IPAddress gw, IPAddress subnet) {
    if (!isInitialized) {
        hardReset();
        Ethernet.init(cs_pin);
        Ethernet.begin(mac, ip, dns, gw, subnet);
        isInitialized = true;
    }
}

bool EthModule::isHardwareConnected() {
    return Ethernet.hardwareStatus() == EthernetW5500;
}

bool EthModule::isLinkUp() {
    return Ethernet.linkStatus() == LinkON;
}

IPAddress EthModule::getLocalIP() {
    return Ethernet.localIP();
}

void EthModule::maintain() {
    Ethernet.maintain();
}
