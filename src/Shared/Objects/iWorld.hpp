#pragma once

#include <string>
#include "../Systems/containerSystem.hpp"

namespace OpenGMP
{
    namespace Objects
    {
        class Player;

        class IWorld
        {
        public:
            std::string worldName;
            Systems::ContainerSystem<Player> player;
        };
    }
}
