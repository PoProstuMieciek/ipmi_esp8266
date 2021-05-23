#include "SystemManager.h"

void SystemManager::begin()
{
    Serial.begin(115200);

    logger.begin();
    logger.printf_raw("\n\n\n");
}

void SystemManager::requestRestart(int timeout_ms)
{
    logger.printf("Restarting in %i seconds\n", FATAL, timeout_ms / 1000);
    delay(timeout_ms);
    ESP.restart();
}