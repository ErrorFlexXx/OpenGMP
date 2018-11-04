#include "worldSystem.hpp"
#include <Client/gameClient.hpp>
#include <Client/Objects/clientWorld.hpp>
#include <Client/Systems/menuSystem.hpp>
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
            if (!id.ReadStream(bsIn)) { std::cout << "Error reading id!" << std::endl; break; }
            ClientWorld newWorld;
            //ClientWorld &newWorld = gameClient.worldContainer.Get(id);
            if (!newWorld.worldName.ReadStream(bsIn)) { std::cout << "Error reading worldname!" << std::endl; break; }
            std::cout << "ID: " << id.id << " World Name: " << newWorld.worldName.text;

            gameClient.menuSystem.CloseActiveMenus();
            
            oCGame *game = CGameManager::GetInstance()->GetGame();
            
            game->OpenLoadscreen(!gameClient.hookGame.gameStarted, "");
            
            gameClient.hookGame.gameStarted = true;
            
            zCViewProgressBar *progress = game->GetProgressBar();
            
            if (progress) progress->SetPercent(0, "");
            
            game->ClearGameState();
            
            if (progress) progress->SetRange(0, 92);
            
            game->LoadWorld(true, newWorld.worldName.text);
            
            if (progress) progress->ResetRange();
            
            if (progress) progress->SetRange(92, 100);
            
            game->EnterWorld(nullptr, true, "");
            
            game->SetTime(1, 12, 00);
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