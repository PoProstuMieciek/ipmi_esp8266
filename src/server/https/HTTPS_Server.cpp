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

bool HTTPS_Server::authenticate()
{
    if (!server.authenticate(PANEL_USERNAME, PANEL_PASSWORD))
    {
        server.requestAuthentication();
        return false;
    }
    return true;
}

// ROUTES
void HTTPS_Server::home()
{
    if (!authenticate()) return;
    
    time_t now = time(NULL);
    auto timestamp = ctime(&now);

    server.send(200, "text/plain", timestamp);
}

void HTTPS_Server::files()
{
    if (!authenticate()) return;
    
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

void HTTPS_Server::pwr_press()
{
    if (!authenticate()) return;
    
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, LOW);
    delay(1000);
    digitalWrite(PWR_PIN, HIGH);

    server.send(200, "text/plain", "done");
}

void HTTPS_Server::rst_press()
{
    if (!authenticate()) return;
    
    pinMode(RST_PIN, OUTPUT);
    digitalWrite(RST_PIN, LOW);
    delay(1000);
    digitalWrite(RST_PIN, HIGH);
    
    server.send(200, "text/plain", "done");
}

void HTTPS_Server::setupRoutes()
{
    server.on("/", route(home));
    // server.on("/files", route(files));

    server.on("/press/power", route(pwr_press));
    server.on("/press/reset", route(rst_press));
}