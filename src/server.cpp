#include "server.hpp"

String cookie = "j4e37fwBex5R6wbzyXVF";

bool exists(fs::FS &fs, String path)
{
  bool yes = false;
  File file = fs.open(path, "r");
  if (!file.isDirectory())
  {
    yes = true;
  }
  file.close();
  return yes;
}

void serveStaticFiles(fs::FS &fs, AsyncWebServer &server, String &username, String &password)
{
  server.serveStatic("/login/", fs, "/login/index.html");
  server.serveStatic("/manifest.json", fs, "/manifest.json");
  server.serveStatic("/maskable_icon_x512.png", fs, "/maskable_icon_x512.png");
  server.serveStatic("/android-chrome-192x192.png", fs, "/android-chrome-192x192.png");
  server.serveStatic("/android-chrome-512x512.png", fs, "/android-chrome-512x512.png");

  server.on("/authenticate", HTTP_POST, [&fs, &username, &password](AsyncWebServerRequest *request)
            {
  String user;
  String pass;

  if (request->hasParam("username", true))
    user = request->getParam("username", true)->value();

  if (request->hasParam("password", true))
    pass = request->getParam("password", true)->value();

  if (user == username && pass == password)
  {
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");
    response->addHeader("Set-Cookie", "garden=" + cookie);
    request->send(response);
  }
  else
  {
    request->send(401, "text/plain", "Unauthorized");
  } });

  server.onNotFound([&fs](AsyncWebServerRequest *request)
                    {
    String path = request->url();
    String pathWithGz = path + ".gz";

    if (path.endsWith("/")) {
      path += "index.html";
    }
    if (exists(fs, pathWithGz)) {
      path += ".gz";
    }

  //Verify if file exists
    if(!exists(fs, path)){
      request->send(404, "text/plain", "Not Found");
      return;
    }
    
    // Verify if the cookie match
    if (verifyLogin(request))
      request->send(fs, path);
    else
      request->redirect("/login/"); });
}

bool verifyLogin(AsyncWebServerRequest *request)
{
  String cookieValue;
  if (request->hasHeader("Cookie"))
    cookieValue = request->getHeader("Cookie")->value();

  // Verify if the cookie match
  if (cookieValue.indexOf(cookie) != -1)
    return true;
  else
    return false;
}
