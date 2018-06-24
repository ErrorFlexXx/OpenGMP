#include <iostream>
#include <csignal>
#include <utils/logger.h>
#include "Utils/cli.h"
#include "gameServer.hpp"

namespace Flags
{
    Cli::Flag help("h", "help", 0, "Prints this message");
    Cli::Flag gameport("gp", "game-port", 1, "Network listening port", {"1760"}, "Serversettings");
    Cli::Flag gameSlots("s", "slots", 1, "Player slots", {"200"}, "Gamesettings");
    Cli::Flag scriptDirectory("sd", "script-dir", 1, "Script directory", {"scripts"}, "Serversettings");
}

void exitHandler(int signum)
{
    if(signum == SIGINT  ||
            signum == SIGABRT ||
            signum == SIGTERM)
    {
        if(GameServer::gameServer)
        {
            GameServer::gameServer->Shutdown();
            delete GameServer::gameServer;
        }
        exit(0); //Quit this programm
    }
}

/**
 * @brief main
 *        Main function -- Parameter parsing and gameserver start.
 * @param argc Number of given arguments
 * @param argv Vector of given arguments
 * @return Exitvalue -- 0 for success, error otherwise
 */
int main(int argc, char **argv)
{
    // Load config values for flags
    Cli::loadConfigFile();

    // Overwrite flags set from config using the commandline
    Cli::setCommandlineArgs(argc, argv);

    // Check if the user just wanted to see the list of commands
    if (Flags::help.isSet())
    {
        Cli::printHelp();
        return 0;
    }

    Cli::writeConfigFile(); //Write given options to config file.

    try
    {
        LogInfo() << "Initializing...";
        signal(SIGINT, exitHandler);    //Register exit handler
        signal(SIGTERM, exitHandler);   //to support clean Ctrl+C shutdown
        signal(SIGABRT, exitHandler);

        GameServer::gameServer = new GameServer(std::stoi(Flags::gameport.getParam(0).c_str()),
                                    std::stoi(Flags::gameSlots.getParam(0).c_str()),
                                    Flags::scriptDirectory.getParam(0));
        LogInfo() << "Starting the server...";
        GameServer::gameServer->Startup();
        GameServer::gameServer->Process();
        delete GameServer::gameServer;
    }
    catch(std::bad_alloc& ba) //Out of memory
    {
        LogError() << "Server stopped due to error(s)." << ba.what();
        return 1;
    }

    return 0;
}
