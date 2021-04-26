#ifndef ENV_H
#define ENV_H

#include <Arduino.h>

const char *WIFI_SSID     = "ssid";
const char *WIFI_PASSWORD = "password";
const char *WIFI_DNAME    = "ipmi_esp8266";

const int   HTTP_PORT     = 1111;
const int   HTTPS_PORT    = 2222;

const char *HTTP_URL      = "http://domain.com:1111/";
const char *HTTPS_URL     = "https://domain.com:2222/";

static const char HTTPS_CERT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
INSERT CERTIFICATE HERE
-----END CERTIFICATE-----
)EOF";

static const char HTTPS_KEY[] PROGMEM = R"EOF(
-----BEGIN PRIVATE KEY-----
INSERT PRIVATE KEY HERE
-----END PRIVATE KEY-----
)EOF";

#endif