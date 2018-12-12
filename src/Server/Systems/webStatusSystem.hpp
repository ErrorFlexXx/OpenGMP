#pragma once

#include <httplib.h>

namespace OpenGMP
{
    class GameServer;

    class WebStatusSystem
    {
    public:
        WebStatusSystem(GameServer &gameServer, int port);

        bool Startup();

        void Shutdown();

        GameServer &gameServer;
        httplib::Server webServer;
        int port;

    private:
        std::string GetStatus() const;
        std::string GetVersion() const;
        std::string GetConnect() const;
        bool setupDone;
    };
}
