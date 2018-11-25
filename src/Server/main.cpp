#include <iostream>
#include <csignal>
#include <utils/logger.h>
#include "Utils/cli.h"
#include "gameServer.hpp"
#include "Systems/networkSystem.hpp"

namespace Flags
{
    Cli::Flag help("h", "help", 0, "Prints this message");
    Cli::Flag gameport("gp", "game-port", 1, "Network listening port", {"1760"}, "Serversettings");
    Cli::Flag webport("wp", "web-port", 1, "Webserver listening port", {"1761"}, "Serversettings");
    Cli::Flag gameSlots("s", "slots", 1, "Player slots", {"200"}, "Gamesettings");
    Cli::Flag scriptDirectory("sd", "script-dir", 1, "Script directory", {"scripts"}, "Serversettings");
    Cli::Flag genKeys("gk", "generate-keys", 0, "Generates encryption keys.");
    Cli::Flag keyDir("kd", "key-dir", 1, "Encryption key directory.", {"."}, "Serversettings");
    Cli::Flag pubKeyFilename("pubk", "public-key", 1, "Filename of public key.", {"public_key.bin"}, "Serversettings");
    Cli::Flag privKeyFilename("privk", "private-key", 1, "Filename of private key.", {"private_key.bin"}, "Serversettings");
}

using namespace OpenGMP;

void exitHandler(int signum)
{
    if(signum == SIGINT  ||
       signum == SIGABRT ||
       signum == SIGTERM)
    {
        if(GameServer::gameServer)
        {
            if(signum == SIGINT) //Shutdown by user signal (e.g. ctrl+c keystroke)
            {
                LogInfo() << "GameServer is going to halt now.";
            }
            else //Emergency shutdown - some thread may have crashed.
            {
                LogInfo() << "GameServer Emergency shutdown!";
            }
            GameServer::gameServer->Shutdown();     //Trigger shutdown
            if(GameServer::gameServer->IAmOwner())  //If I am the owner
                delete GameServer::gameServer;      //delete the gameserver now.
                                                    //otherwise the main function will exit the main thread now.
        }
        exit(0);
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

    // Check if the user just wants to see the list of commands
    if (Flags::help.isSet())
    {
        Cli::printHelp();
        return 0;
    }

    //Check if the user wants to build new encryption keys
    if(Flags::genKeys.isSet())
    {
        NetworkSystem::GenKeys(Flags::keyDir.getParam(0),
                               Flags::pubKeyFilename.getParam(0),
                               Flags::privKeyFilename.getParam(0));
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
                                                std::stoi(Flags::webport.getParam(0).c_str()),
                                                std::stoi(Flags::gameSlots.getParam(0).c_str()),
                                                Flags::scriptDirectory.getParam(0),
                                                Flags::keyDir.getParam(0),
                                                Flags::pubKeyFilename.getParam(0),
                                                Flags::privKeyFilename.getParam(0));
        LogInfo() << "Starting the server...";
        if(!GameServer::gameServer->Startup())
            return 1;

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
