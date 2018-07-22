#include "gameClient.hpp"
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"
#include <libintl.h>
#include <locale>
#include <iostream>

using namespace std;
using namespace OpenGMP;
using namespace OpenGMP::Hooks;
using namespace OpenGMP::Systems;

HINSTANCE GameClient::dllInstance = nullptr;
string GameClient::serverName = "";
unsigned short GameClient::serverPort = 1760;

/* Called from external created thread */
extern "C"
void __declspec(dllexport) SetConnectData(char *serverName)
{
    GameClient::serverName = serverName;
}

GameClient::GameClient()
    : inited(false)
    , networkSystem(*this)
    , loginSystem(*this)
    , inputSystem(*this)
    , menuSystem(*this)
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