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
#include "../Components/playerMovement.hpp"

namespace OpenGMP
{
    /**
     * @describe The Player class
     *   A player covers a NPC that can be controlled
     */
    class Player : public NetIdObject
    {
    public:
        Player() {}
        Position position;
        Scale scale;
        PlayerTalents talents;
        PlayerAttributes attributes;
        PlayerSkills skills;
        PlayerVisual visual;
        PlayerMovement movement;
    };
}
