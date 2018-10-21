#include "hGame.hpp"
#include <Shared/Components/GameTime.hpp>
#include <Client/Objects/CDetour.h>
#include "../Gothic/cGameManager.hpp"
#include "../Gothic/Objects/oCGame.hpp"
#include "../Gothic/Classes/zCRenderer.hpp"
#include "../Gothic/Classes/zCView.hpp"
#include "../Systems/inputSystem.hpp"
#include "../Systems/menuSystem.hpp"
#include "../Systems/windowSystem.hpp"
#include "../GUI/menu.hpp"
#include "../gameClient.hpp"

using namespace OpenGMP;
using namespace OpenGMP::Hooks;
using namespace OpenGMP::GUI;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Components;

extern GameClient gameClient;

typedef void (*SysEventPtr)();
SysEventPtr sysEvent = (SysEventPtr)(0x5053E0); //Get address of detour method.

typedef void (CGameManager::*tMenu)(int savegame);
tMenu pCGameManagerGMPMenu = &CGameManager::GMP_Menu;

typedef void (oCGame::*tRender)();
tRender poCGameGMPRender = &oCGame::GMP_Render;

HGame::HGame(GameClient &gameClient)
    : gameClient(gameClient)
    , outgameStarted(false)
    , blankColor(0, 0, 0, 0)
    , menuDetour(CGameManager::Addresses::Menu, 7, DETOUR_CAST pCGameManagerGMPMenu)
    , renderDetour(oCGame::Addresses::Render, 7, DETOUR_CAST poCGameGMPRender)
{
}

void CGameManager::GMP_Menu(int savegame)
{
    GameTime::Update();
    unsigned long long now = GameTime::GetTicks();
    gameClient.inputSystem.Update();
    if (!gameClient.hookGame.outgameStarted)
    {
        gameClient.hookGame.StartOutgame();
        gameClient.hookGame.outgameStarted = true;
    }
    gameClient.menuSystem.UpdateMenus(now);
    gameClient.networkSystem.Update();

    //Rendering:
    sysEvent();
    zCRenderer *renderer = zCRenderer::GetRenderer();
    renderer->Vid_Clear(gameClient.hookGame.blankColor, 3);
    renderer->BeginFrame();
    zCView::GetScreen()->Render();
    renderer->EndFrame();
    renderer->Vid_Blit(1, 0, 0);
}

void oCGame::GMP_Render()
{

}

void HGame::Startup()
{
    renderDetour.Activate();
    menuDetour.Activate();
}

void HGame::Shutdown()
{
}

void HGame::StartOutgame()
{
    WindowSystem::SetWindowTitle("OpenGMP");
    WindowSystem::UpdateWindowIcon();
    gameClient.menuSystem.menuMain.Open();
    gameClient.networkSystem.Startup();
}
