#include "hGame.hpp"
#include <Shared/GameTime.hpp>
#include "../Gothic/Objects/oCGame.hpp"
#include "../Core/inputHandler.hpp"

HGame *HGame::instance = nullptr;

HGame::HGame()
    : m_hookOutgame(false, (DWORD)oCGame::Addresses::Menu, (DWORD)&RunOutgame)
    , m_hookIngame(false, (DWORD)oCGame::Addresses::Render, (DWORD)&RunIngame)
{
}

HGame *HGame::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new HGame();
    }
    return instance;
}

void HGame::RunOutgame()
{
    GameTime::Update();
    InputHandler::Update();
}

void HGame::RunIngame()
{

}

void HGame::DoHook()
{

}

void HGame::UndoHook()
{

}
