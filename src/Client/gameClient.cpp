#include "gameClient.hpp"
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"
#include <Shared/Types/constants.hpp>
#include <Client/Gothic/cGameManager.hpp>
#include <libintl.h>
#include <locale>
#include <iostream>

using namespace std;
using namespace OpenGMP;

HINSTANCE GameClient::dllInstance = nullptr;

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
    , webStatusSystem(*this)
    , hookGame(*this)
{}

void GameClient::Startup(HINSTANCE inst)
{
    if (!inited && IsGothic2exe()) //If no instance created yet and we are in a gothic process
    {
        std::string localePath = ReadEnvironmentVariable(localeEnvVarName);
        setlocale(LC_ALL, "");
        bindtextdomain("OpenGMP", localePath.c_str());
        textdomain("OpenGMP");
        OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
        hookGame.Startup(); //Hook Game Loops (Menu & Ingame)
        inited = true;
        dllInstance = inst;
    }
}

void GameClient::Stop()
{
    networkSystem.Shutdown();
    exit(0);
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

std::string GameClient::ReadEnvironmentVariable(const char *varName)
{
    char* buf = nullptr;
    size_t sz = 0;

    if (_dupenv_s(&buf, &sz, varName) == 0 && buf != nullptr)
    {
        std::string ret = buf;
        free(buf);
        return ret;
    }
    return "";
}
