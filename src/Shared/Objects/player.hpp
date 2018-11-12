#pragma once

#include "../Objects/netIdObject.hpp"
#include "world.hpp"
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
        Position position;  //!< Position and rotation of the player
        Scale scale;        //!< Scaling of the player
        PlayerTalents talents;  //!< Talents of the player (sneak, picklock, etc.)
        PlayerAttributes attributes; //!< Attributes of the player (str, dex, etc.)
        PlayerSkills skills;    //!< Skills (1h, 2h, bow, etc.)
        PlayerVisual visual;    //!< Visual of the player (head, body, textures, etc.)
        PlayerMovement movement;//!< Movement state (Forward, Left, TurnLeft, etc.)
    };
}
