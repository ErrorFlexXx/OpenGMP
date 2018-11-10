#include "gameClient.hpp"
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"
#include <Shared/Types/constants.hpp>
#include <libintl.h>
#include <locale>
#include <iostream>

using namespace std;
using namespace OpenGMP;

HINSTANCE GameClient::dllInstance = nullptr;
string GameClient::serverName = "localhost";
unsigned short GameClient::serverPort = 1760;

GameClient::GameClient()
    : worldContainer(10)
    , playerContainer(100)
    , inited(false)
    , networkSystem(*this)
    , loginSystem(*this)
    , inputSystem(*this)
    , menuSystem(*this)
    , worldSystem(*this)
    , playerController(*this)
    , hookGame(*this)
{}

void GameClient::Startup(HINSTANCE inst)
{
    if (!inited && IsGothic2exe()) //If no instance created yet and we are in a gothic process
    {
        setlocale(LC_ALL, "");
        bindtextdomain("OpenGMP", "locale");
        textdomain("OpenGMP");
        OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
        hookGame.Startup(); //Hook Game Loops (Menu & Ingame)
        inited = true;
        dllInstance = inst;
    }
}

void GameClient::Stop()
{
    ;
}

bool GameClient::IsGothic2exe()
{
    const int filenameLength = 100;
    char filename[filenameLength] = {};
    std::locale loc;
    std::string gothicFilename = "gothic2.exe";
    
    GetModuleFileName(GetModuleHandle(NULL), filename, filenameLength);
    std::string filenameStr(filename);
    for (size_t i = 0; i < filenameStr.length(); i++)
    {
        filenameStr[i] = std::tolower(filenameStr[i], loc);
    }
    return (filenameStr.find(gothicFilename) != string::npos);
}

void GameClient::ReadEnvironmentConnectData()
{
    //Read connect data from environment variables
    char* buf = nullptr;
    size_t sz = 0;
    
    if (_dupenv_s(&buf, &sz, hostnameEnvVarName) == 0 && buf != nullptr)
    {
        GameClient::serverName = buf;
        free(buf);
        buf = nullptr;
        sz = 0;
    }

    if (_dupenv_s(&buf, &sz, portEnvVarName) == 0 && buf != nullptr)
    {
        GameClient::serverPort = atoi(buf);
        free(buf);
        buf = nullptr;
        sz = 0;
    }
}
