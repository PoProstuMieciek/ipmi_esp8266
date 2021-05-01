#pragma once

#include "server/base/BaseServer.h"

class HTTPS_Server : public BaseServer<ESP8266WebServerSecure>
{
    protected:        
        void setupSSL();

        void home();
        void files();
        void setupRoutes();

    public:
        HTTPS_Server(SystemManager &sys, FilesystemManager &fs);
};