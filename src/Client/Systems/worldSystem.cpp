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
    unsigned char command;
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
            int i = 0;
            std::cout << i++ << std::endl;
            gameClient.menuSystem.CloseActiveMenus();
            std::cout << i++ << std::endl;
            oCGame *game = CGameManager::GetInstance()->GetGame();
            std::cout << i++ << std::endl;
            game->OpenLoadscreen(!gameClient.hookGame.gameStarted, newWorld.worldName.text);
            std::cout << i++ << std::endl;
            gameClient.hookGame.gameStarted = true;
            std::cout << i++ << std::endl;
            zCViewProgressBar *progress = game->GetProgressBar();
            std::cout << i++ << std::endl;
            if (progress) progress->SetPercent(0, "");
            std::cout << i++ << std::endl;  
            game->ClearGameState();
            std::cout << i++ << std::endl;
            if (progress) progress->SetRange(0, 92);
            std::cout << i++ << std::endl;
            game->LoadWorld(true, newWorld.worldName.text);
            std::cout << i++ << std::endl;
            if (progress) progress->ResetRange();
            std::cout << i++ << std::endl;
            if (progress) progress->SetRange(92, 100);
            std::cout << i++ << std::endl;
            game->EnterWorld(nullptr, true, "");
            std::cout << i++ << std::endl;
            //Clock
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