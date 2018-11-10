#include "worldSystem.hpp"
#include <Client/gameClient.hpp>
#include <Client/Objects/clientWorld.hpp>
#include <Client/Systems/menuSystem.hpp>
#include <Client/Systems/playerController.hpp>
#include <Client/Gothic/cGameManager.hpp>
#include <Client/Gothic/Classes/zCViewProgressBar.hpp>
#include <Client/Gothic/Objects/oCGame.hpp>
#include <Shared/Types/Messages/worldSystemMessages.hpp>
#include <Shared/Components/id.hpp>
#include <BitStream.h>
#include <libintl.h>
#include <iostream>
#define _(string) gettext (string)

using namespace OpenGMP;
using namespace RakNet;

WorldSystem::WorldSystem(GameClient &gameClient)
    : gameClient(gameClient)
{}


void WorldSystem::Process(RakNet::Packet *packet)
{
    NetMessage command;
    BitStream bsIn(packet->data, packet->length, false);
    bsIn.IgnoreBytes(1); //WorldSystem
    bsIn.Read(command); //Read command

    switch (command)
    {
        case worldSystemMessages::LOAD_WORLD:
        {
            Id id;
            id.ReadStream(bsIn);
            ClientWorld &newWorld = gameClient.worldContainer.Get(id);
            newWorld.worldName.ReadStream(bsIn);

            gameClient.menuSystem.CloseActiveMenus();
            
            oCGame *game = CGameManager::GetInstance()->GetGame();
            
            game->OpenLoadscreen(!gameClient.hookGame.gameStarted, "");            
            gameClient.hookGame.gameStarted = true;            
            zCViewProgressBar *progress = game->GetProgressBar();
            progress->SetPercent(0, "");                            
            game->ClearGameState();
            progress->SetRange(0, 92);
            game->LoadWorld(-2, newWorld.worldName.text);
            progress->ResetRange();
            progress->SetRange(92, 100);
            game->EnterWorld(nullptr, true, "XARDAS");
            game->SetTime(1, 12, 00);
            gameClient.playerController.ControlCurrentPlayer(); //Test
            break;
        }
        default:
        {
#ifdef DBG_NETWORK
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("WorldSystem RakNet Message not handled! ID is")).append(": ").append(std::to_string((int)command)).append("!"),
                Color(255, 0, 0, 255),
                10
            );
#endif
        }
    }
}