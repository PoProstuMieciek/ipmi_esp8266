#pragma once

// #define ASYNC_TCP_SSL_ENABLED 1
// #include <ESPAsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// typedef AsyncWebServerRequest Request;

#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#define route(handler) [this]() { handler(); }

#include "config.h"
#include "filesystem/FilesystemManager.h"
#include "network/NetworkManager.h"

template<typename ServerType>
class BaseServer
{
    protected:
        SystemManager sys;
        FilesystemManager fs;
        Logger logger;
        ServerType server;

        virtual void setupRoutes();

    public:
        BaseServer(SystemManager &sys, FilesystemManager &fs, uint16_t port);
        void loop();
};