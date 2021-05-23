#pragma once

#include <Arduino.h>

#include "logger/Logger.h"

class SystemManager
{
    public:
        Logger logger;
        
        void begin();

        void requestRestart(int timeout_seconds = 10000);
};