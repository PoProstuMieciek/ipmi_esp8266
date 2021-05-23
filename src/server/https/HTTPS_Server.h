#pragma once

#include "server/base/BaseServer.h"

class HTTPS_Server : public BaseServer<ESP8266WebServerSecure>
{
    protected:        
        void setupSSL();
        bool authenticate();

        void home();
        void files();
        void rst_press();
        void pwr_press();
        void setupRoutes();

    public:
        HTTPS_Server(SystemManager &sys, FilesystemManager &fs);
};