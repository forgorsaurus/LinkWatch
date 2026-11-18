#pragma once
#include <Arduino.h>
#include <SPI.h>

class SPIBus{
    private:
        SPIClass &bus;
        int8_t sclk;
        int8_t miso;
        int8_t mosi;
        int8_t cs;
        bool isInitialized = false;
    public:
        SPIBus(SPIClass &spiBus, int8_t sclk_pin, int8_t miso_pin, int8_t mosi_pin, int8_t cs_pin);
        void init();
        SPIClass& getBus();
};