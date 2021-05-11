#include "NetworkManager.h"

void NetworkManager::begin(SystemManager &sys)
{
    this->sys = sys;
    logger.begin("[Network]");

    if (!connect())
    {
        sys.requestRestart();
        return;
    }

    setupOTA();
    setupNTP();

    wifi_set_sleep_type(NONE_SLEEP_T);
    // wifi_set_sleep_type(LIGHT_SLEEP_T);
}

bool NetworkManager::connect()
{
    logger.printf("Connecting to %s ...\n", INFO, WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    if(WiFi.waitForConnectResult(15000) == WL_CONNECTED)
    {
        logger.printf("Connected\n", INFO);
        logger.printf("IP: %s\n", INFO, WiFi.localIP().toString().c_str());

        if (MDNS.begin(WIFI_DNAME))
        {
            logger.printf("DNAME: %s.local\n", INFO, WIFI_DNAME);
        }

        return true;
    }
    else
    {
        logger.println("Failed to connect", FATAL);
        return false;
    }
}

void NetworkManager::setupNTP()
{
    configTime(TIMEZONE * 3600, 0, "pool.ntp.org", "time.nist.gov");
}

void NetworkManager::setupOTA()
{
    ArduinoOTA.begin();
}

void NetworkManager::loop()
{
    ArduinoOTA.handle();
    MDNS.update();
}