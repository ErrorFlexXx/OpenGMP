#include "hGame.hpp"
#include <Shared/Components/GameTime.hpp>
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

HGame *HGame::instance = nullptr; //Instance to get the object from (hooked) non member function.
bool HGame::outgameStarted = false;
zCOLOR HGame::blankColor = zCOLOR(0, 0, 0, 0);

typedef void (*SysEventPtr)();
SysEventPtr sysEvent = (SysEventPtr)(0x5053E0); //Get address of detour method.

HGame::HGame(GameClient &gameClient)
    : gameClient(gameClient)
    , m_hookOutgame(false, (DWORD)oCGame::Addresses::Menu, (DWORD)&RunOutgame)
    , m_hookIngame(false, (DWORD)oCGame::Addresses::Render, (DWORD)&RunIngame)
{
    instance = this;
}

void HGame::RunOutgame()
{
        GameTime::Update();
        unsigned long long now = GameTime::GetTicks();
        instance->gameClient.inputSystem.Update();
        if (!HGame::outgameStarted)
        {
            instance->StartOutgame();
            HGame::outgameStarted = true;
        }
        instance->gameClient.menuSystem.UpdateMenus(now);
        instance->gameClient.networkSystem.Update();
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

void HGame::Startup()
{
    m_hookIngame.DoHook();
    m_hookOutgame.DoHook();
}

void HGame::Shutdown()
{
    m_hookIngame.UndoHook();
    m_hookOutgame.UndoHook();
}

void HGame::StartOutgame()
{
    WindowSystem::SetWindowTitle("OpenGMP");
    WindowSystem::UpdateWindowIcon();
    gameClient.menuSystem.OpenMainMenu();
    gameClient.networkSystem.Startup();
}
