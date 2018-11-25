#include "webStatusSystem.hpp"
#include <Server/gameServer.hpp>
#include <utils/logger.h>
#include <string>
#include <thread>

using namespace OpenGMP;
using namespace httplib;
using namespace std;

WebStatusSystem::WebStatusSystem(GameServer &gameServer, int port)
    : gameServer(gameServer)
    , port(port)
    , setupDone(false)
{}

bool WebStatusSystem::Startup()
{
    if(!setupDone)
    {
        //I'm not using redirect for this, because redirecting is causing a 5 sec. lag for some reason.
        webServer.Get("/", [=](const Request &req, Response &res)
        {
            res.set_content(GetStatus(), "text/plain");
        });

        webServer.Get("/status", [=](const Request &req, Response &res)
        {
            res.set_content(GetStatus(), "text/plain");
        });

        webServer.Get("/connect", [=](const Request &req, Response &res)
        {
            res.set_content(GetConnect(), "text/plain");
        });

        setupDone = true;
    }

    std::thread([=]() {
        webServer.listen("0.0.0.0", port);
    }).detach();

    return true;
}

void WebStatusSystem::Shutdown()
{
    if(webServer.is_running())
    {
        webServer.stop();
        LogInfo() << "WebStatusSystem stopped!";
    }
}

std::string WebStatusSystem::GetStatus() const
{
    std::string output;
    output.append(to_string(gameServer.clientContainer.Count()))
          .append("/")
          .append(to_string(gameServer.clientContainer.capacity));
    return output;
}

std::string WebStatusSystem::GetConnect() const
{
    return gameServer.networkSystem.server.ToJson();
}
