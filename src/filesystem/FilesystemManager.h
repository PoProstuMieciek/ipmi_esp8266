#pragma once

#include <Arduino.h>
#include <LittleFS.h>
#include <vector>

#include "system/SystemManager.h"
#include "logger/Logger.h"

class FilesystemManager
{
    public:
        SystemManager sys;
        Logger logger;

        void begin(SystemManager &sys);

        String getFileContent(String path);
        std::vector<String> listDirectory(String dir_path);
};