// Copyright (C) 2021  Maciej Opaliński. All Rights Reserved.
// Version 1.0.0

#include <Arduino.h>

#include "system/SystemManager.h"
#include "filesystem/FilesystemManager.h"
#include "network/NetworkManager.h"

#include "server/http/HTTP_Server.h"
#include "server/https/HTTPS_Server.h"

SystemManager     sys;
FilesystemManager fs_manager;
NetworkManager    network_manager;

HTTP_Server       *http_server;
HTTPS_Server      *https_server;

void setup()
{
    sys.begin();
    fs_manager.begin(sys);
    network_manager.begin(sys);

    http_server  = new HTTP_Server(sys, fs_manager);
    https_server = new HTTPS_Server(sys, fs_manager);
}

void loop()
{
    network_manager.loop();

    http_server->loop();
    https_server->loop();
}