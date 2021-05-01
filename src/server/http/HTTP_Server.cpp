#include "HTTP_Server.h"

HTTP_Server::HTTP_Server(SystemManager &sys, FilesystemManager &fs) :
BaseServer(sys, fs, HTTP_PORT)
{
    setupRoutes();

    logger.begin("[Network][HTTP]");
    logger.printf("Listening on port %i\n", INFO, HTTP_PORT);
}

// ROUTES
void HTTP_Server::secureRedirect()
{
    server.sendHeader("Location", HTTPS_URL);
    server.send(301, "text/plain", "");
}

void HTTP_Server::shortPress()
{
    server.send(200, "text/plain", "Blinking...");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    digitalWrite(LED_PIN, HIGH);

    pinMode(BTN_PIN, INPUT);
    digitalWrite(BTN_PIN, LOW);
    pinMode(BTN_PIN, OUTPUT);
    delay(1000);
    pinMode(BTN_PIN, INPUT);
}

void HTTP_Server::setupRoutes()
{
    server.on("/", route(secureRedirect));
    server.on("/short-press", route(shortPress));
}