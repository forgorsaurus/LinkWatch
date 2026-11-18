#include "spi_bus.h"

SPIBus::SPIBus(SPIClass &spiBus, int8_t sclk_pin, int8_t miso_pin, int8_t mosi_pin, int8_t cs_pin) : bus(spiBus), sclk(sclk_pin), miso(miso_pin), mosi(mosi_pin), cs(cs_pin){

}

void SPIBus::init(){
    if (!isInitialized){
        bus.begin(sclk, miso, mosi, cs);
        isInitialized = true;
    }
}

SPIClass &SPIBus::getBus(){
    return bus;
}
