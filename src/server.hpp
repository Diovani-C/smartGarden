#include <Arduino.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

bool verifyLogin(AsyncWebServerRequest *request);
void serveStaticFiles(fs::FS &fs, AsyncWebServer &server, String &username, String &password);