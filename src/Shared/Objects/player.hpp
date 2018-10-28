#pragma once

#include "../Objects/netIdObject.hpp"
#include "../Components/color.hpp"
#include "../Components/position.hpp"
#include "../Components/scale.hpp"
#include "../Components/id.hpp"
#include "../Components/playerTalents.hpp"
#include "../Components/playerAttributes.hpp"
#include "../Components/playerSkills.hpp"
#include "../Components/playerVisual.hpp"

namespace OpenGMP
{
    namespace Objects
    {
        /**
         * @describe The Player class
         *   A player covers a NPC that can be controlled
         */
        class Player : public NetIdObject
        {
        public:
            Components::Position position;
            Components::Scale scale;
            Components::PlayerTalents talents;
            Components::PlayerAttributes attributes;
            Components::PlayerSkills skills;
            Components::PlayerVisual visual;
        };
    }
}
