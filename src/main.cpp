#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>

const char *WIFI_SSID     = "ssid";
const char *WIFI_PASSWORD = "password";
const char *WIFI_DNAME    = "ipmi_esp8266";
const int   HTTP_PORT     = 4080;
const int   HTTPS_PORT    = 4443;
const char *HTTP_URL      = "http://ipmi.mieciuu.live:4080/";
const char *HTTPS_URL     = "https://ipmi.mieciuu.live:4443/";

ESP8266WebServer                http_server(HTTP_PORT);
BearSSL::ESP8266WebServerSecure https_server(HTTPS_PORT);

static const char https_cert[] PROGMEM =
#include "cert.h"
"";

static const char https_key[] PROGMEM = 
#include "key.h"
"";

bool connectToWifi()
{
    Serial.printf("[Network] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int timeout_ms = 15000;
    int delay_ms = 200;
    while (timeout_ms > 0)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("\n[Network] Connected to network");
            Serial.printf("[Network] IP: %s\n", WiFi.localIP().toString().c_str());

            if (MDNS.begin(WIFI_DNAME))
            {
                Serial.printf("[Network] DNAME: %s.local\n", WIFI_DNAME);
            }

            return true;
        }

        delay(delay_ms);
        timeout_ms -= delay_ms;

        Serial.print(".");
    }

    Serial.println("\n[Network] Failed to connect");
    Serial.println("\n[Network] Restarting in 10 seconds");
    return false;
}

void secureRedirect()
{
    http_server.sendHeader("Location", HTTPS_URL, true);
    http_server.send(301, "text/plain", "");
}

void showWebpage()
{
    time_t now = time(nullptr);
    String timestamp = ctime(&now);

    https_server.send(200, "text/html", "<!DOCTYPE html><html><head><title>ipmi_esp8266</title></head><body><h1>Hello from HTTPS!!! <br>" + timestamp + "</h1></body></html>");
}

void setup()
{
    Serial.begin(115200);
    Serial.print("\n\n\n");

    if(!connectToWifi())
    {
        delay(10000);
        ESP.restart();
        return;
    }
    Serial.println("[Network] Connected");

    configTime(2*3600, 0, "pool.ntp.org", "time.nist.gov");

    http_server.on("/", secureRedirect);
    http_server.begin();

    https_server.getServer().setRSACert(
        new BearSSL::X509List(https_cert),
        new BearSSL::PrivateKey(https_key)
    );
    https_server.on("/", showWebpage);
    https_server.begin();

    Serial.println("[Webserver] Ready");
}

void loop()
{
    http_server.handleClient();
    https_server.handleClient();
    MDNS.update();
}