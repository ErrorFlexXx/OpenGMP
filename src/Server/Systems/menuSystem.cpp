#include "menuSystem.hpp"
#include <Shared/Components/notificationText.hpp>

using namespace RakNet;
using namespace OpenGMP;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Components;

MenuSystem::MenuSystem(GameServer &gameServer)
    : gameServer(gameServer)
{}

void MenuSystem::Process(Packet *packet)
{
    ;
}
