#pragma once

#include "../Objects/netIdObject.hpp"
#include "world.hpp"
#include "../Types/vec3f.hpp"
#include "../Components/color.hpp"
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
        Vec3f position;  //!< Position and rotation of the player
        Vec3f rotation;  //!< Position and rotation of the player
        Vec3f scale;        //!< Scaling of the player
        PlayerTalents talents;  //!< Talents of the player (sneak, picklock, etc.)
        PlayerAttributes attributes; //!< Attributes of the player (str, dex, etc.)
        PlayerSkills skills;    //!< Skills (1h, 2h, bow, etc.)
        PlayerVisual visual;    //!< Visual of the player (head, body, textures, etc.)
        PlayerMovement movement;//!< Movement state (Forward, Left, TurnLeft, etc.)
    };
}
