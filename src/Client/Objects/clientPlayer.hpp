#pragma once

#include <Shared/Objects/player.hpp>
#include <Client/Gothic/Objects/oCNpc.hpp>

namespace OpenGMP
{
    class ClientPlayer : public Player
    {
    public:
        ClientPlayer();
        ClientPlayer(oCNpc *gothicPlayer);

        oCNpc *gothicPlayer;
    };
}