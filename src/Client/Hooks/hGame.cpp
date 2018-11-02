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

extern GameClient gameClient;

typedef void (*SysEventPtr)();
SysEventPtr sysEvent = (SysEventPtr)(0x5053E0);

HGame::HGame(GameClient &gameClient)
    : gameClient(gameClient)
    , outgameStarted(false)
    , gameStarted(false)
    , blankColor(0, 0, 0, 0)
{
    DWORD funcAddress;
    
    //FIXME: Can't find a way of getting the member func ptr as DWORD in an expression
    //       to obtain it in an initializer list. Would be nice to create hooks in an
    //       initializer list.
    GetMemberFuncPtr(funcAddress, CGameManager::GMP_Menu);
    menuDetour = new CDetour(CGameManager::Addresses::Menu, 7, funcAddress);
    GetMemberFuncPtr(funcAddress, oCGame::GMP_Render);
    renderDetour = new CDetour(oCGame::Addresses::Render, 7, funcAddress);
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
    gameClient.menuSystem.UpdateNotification(now);
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
    renderDetour->Activate();
    menuDetour->Activate();
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
