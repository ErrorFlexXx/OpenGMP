#include "hGame.hpp"
#include <Shared/GameTime.hpp>
#include "../Gothic/Objects/oCGame.hpp"
#include "../Gothic/Classes/zCRenderer.hpp"
#include "../Gothic/Classes/zCView.hpp"
#include "../Core/inputHandler.hpp"
#include "../GUI/menu.hpp"

using namespace OpenGMP;
using namespace OpenGMP::Hooks;
using namespace OpenGMP::GUI;

HGame *HGame::instance = nullptr;
bool HGame::outgameStarted = false;
OpenGMP::Menus::OGMPMainMenu *HGame::mainMenu = nullptr;
zCOLOR HGame::blankColor = zCOLOR(0, 0, 0, 0);

typedef void (*SysEventPtr)();
SysEventPtr sysEvent = (SysEventPtr)(0x5053E0); //Get address of detour method.

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
        unsigned long long now = GameTime::GetTicks();
        InputHandler::Update();
        if (!HGame::outgameStarted)
        {
            HGame::StartOutgame();
            HGame::outgameStarted = true;
        }
        Menu::UpdateMenus(now);
        //Rendering:
        sysEvent();
        zCRenderer *renderer = zCRenderer::GetRenderer();
        renderer->Vid_Clear(blankColor, 3);
        renderer->BeginFrame();
        zCView::GetScreen()->Render();
        renderer->EndFrame();
        renderer->Vid_Blit(1, 0, 0);
}

void HGame::RunIngame()
{

}

void HGame::DoHook()
{
    m_hookIngame.DoHook();
    m_hookOutgame.DoHook();
}

void HGame::UndoHook()
{
    m_hookIngame.UndoHook();
    m_hookOutgame.UndoHook();
}

void HGame::StartOutgame()
{
    HGame::mainMenu = new OpenGMP::Menus::OGMPMainMenu();
    mainMenu->Open();
}
