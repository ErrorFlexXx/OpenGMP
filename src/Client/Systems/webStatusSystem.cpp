#include "webStatusSystem.hpp"
#include <Client/gameClient.hpp>
#include <Shared/Types/constants.hpp>
#include <Shared/Objects/server.hpp>
#include <cpp-httplib\httplib.h>

using namespace OpenGMP;
using namespace httplib;
using namespace std;

WebStatusSystem::WebStatusSystem(GameClient &gameClient)
    : gameClient(gameClient)
    , webStatusClient(nullptr)
{}

WebStatusSystem::~WebStatusSystem()
{
    if (webStatusClient)
        delete webStatusClient;
}

bool WebStatusSystem::Startup(OpenGMP::Server &server)
{
    string hostname = gameClient.ReadEnvironmentVariable(hostnameEnvVarName);
    string webPort = gameClient.ReadEnvironmentVariable(webStatusPortVarName);

    if (hostname.length() == 0 || webPort.length() == 0)
        return false;

    server.hostname = hostname;
    server.webPort = atoi(webPort.c_str());
    webStatusClient = new httplib::Client(server.hostname.c_str(), server.webPort);
    return true;
}

void WebStatusSystem::Shutdown()
{
    delete webStatusClient;
    webStatusClient = nullptr;
}

bool WebStatusSystem::GetConnectData(OpenGMP::Server &server)
{
    auto res = webStatusClient->Get("/connect");
    if (res && res->status == 200)
    {
        server.FromJson(res->body);
        return true;
    }
    return false;
}
