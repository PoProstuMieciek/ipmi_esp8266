#include "BaseServer.h"

template<>
BaseServer<ESP8266WebServer>::BaseServer(SystemManager &sys, FilesystemManager &fs, uint16_t port)
{
    this->sys = sys;
    this->fs = fs;
    server.begin(port);
}
template<>
BaseServer<ESP8266WebServerSecure>::BaseServer(SystemManager &sys, FilesystemManager &fs, uint16_t port)
{
    this->sys = sys;
    this->fs = fs;
    server.begin(port);
}

template<>
void BaseServer<ESP8266WebServer>::loop()
{
    server.handleClient();
}
template <>
void BaseServer<ESP8266WebServerSecure>::loop()
{
    server.handleClient();
}

template<typename ServerType>
void BaseServer<ServerType>::setupRoutes() {}