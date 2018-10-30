#pragma once

#include <string>
#include <functional>
#include <map>

namespace OpenGMP
{
    class GameServer;

    class TerminalSystem
    {
    public:
        TerminalSystem(GameServer &gameServer);

        bool Startup();
        bool Update();
        void Shutdown();
        void AddCommand(const std::string &command, const std::string &description, const std::function<void()> action);
        std::string GetDescription(const std::string &command);
        void GetHelp();
    private:
        GameServer &gameServer;
        bool commandReady;
        std::string inputLine;
        std::map<std::string, std::function<void()>> actions;
        std::map<std::string, std::string> descriptions;
    };
}
