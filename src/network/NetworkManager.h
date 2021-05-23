#pragma once

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include "config.h"
#include "system/SystemManager.h"
#include "logger/Logger.h"

class NetworkManager
{
    public:
        SystemManager sys;
        Logger logger;

        void begin(SystemManager &sys);

        bool connect();
        void setupNTP();
        void setupOTA();

        void loop();
};