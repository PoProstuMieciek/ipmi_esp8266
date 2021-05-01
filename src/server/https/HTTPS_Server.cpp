#include "HTTPS_Server.h"

HTTPS_Server::HTTPS_Server(SystemManager &sys, FilesystemManager &fs) :
BaseServer(sys, fs, HTTPS_PORT)
{
    setupRoutes();
    setupSSL();

    logger.begin("[Network][HTTPS]");
    logger.printf("Listening on port %i\n", INFO, HTTPS_PORT);
}

void HTTPS_Server::setupSSL()
{
    auto https_cert = fs.getFileContent(CERT_PATH);
    auto https_key  = fs.getFileContent(KEY_PATH);

    if (https_cert.isEmpty() || https_key.isEmpty())
    {
        logger.println("SSL certificate or private key is empty", FATAL);
        sys.requestRestart();
        return;
    }

    server.getServer().setRSACert(
        new BearSSL::X509List(https_cert.c_str()),
        new BearSSL::PrivateKey(https_key.c_str())
    );
}

// ROUTES
void HTTPS_Server::home()
{
    if (!server.authenticate(PANEL_USERNAME, PANEL_PASSWORD)) return server.requestAuthentication();
    
    time_t now = time(NULL);
    auto timestamp = ctime(&now);

    // auto processor = [timestamp] (const String &var) -> String
    // {
    //     if (var == "TIME") return timestamp;
    //     return String();
    // };

    // server.send(LittleFS, "/public/index.html", String(), false, processor);

    server.send(200, "text/plain", timestamp);
}

void HTTPS_Server::files()
{
    if (!server.authenticate(PANEL_USERNAME, PANEL_PASSWORD)) return server.requestAuthentication();
    
    String output = "";
    auto files = fs.listDirectory("/");

    for (auto file_path : files)
    {
        String content = fs.getFileContent(file_path);
        output += file_path + "\n";
        output += content + "\n\n";
    }

    server.send(200, "text/plain", output);
}

void HTTPS_Server::setupRoutes()
{
    server.on("/", route(home));
    server.on("/files", route(files));
}