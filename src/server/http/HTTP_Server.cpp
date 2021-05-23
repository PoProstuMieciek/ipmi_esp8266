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

void HTTP_Server::setupRoutes()
{
    server.on("/", route(secureRedirect));
}