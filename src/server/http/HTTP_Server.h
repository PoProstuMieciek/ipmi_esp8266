#pragma once

#include "server/base/BaseServer.h"

class HTTP_Server : public BaseServer<ESP8266WebServer>
{
    protected:
        void secureRedirect();
        void shortPress();
        void setupRoutes();

    public:
        HTTP_Server(SystemManager &sys, FilesystemManager &fs);
};