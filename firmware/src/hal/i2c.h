#pragma once
#include <Wire.h>
#include "hw_config.h"

class I2C{
    private:
        bool isInitialized = false;

    public:
        void init();
};