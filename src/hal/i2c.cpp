#include "i2c.h"

void I2C::init(){
    if (!isInitialized) {
        Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
        isInitialized = true;
    }    
}