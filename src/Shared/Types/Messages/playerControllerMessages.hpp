#pragma once

#include "networkSystemMessages.hpp"

namespace OpenGMP
{
    enum PlayerControllerMessages : unsigned char
    {
        ADD_PLAYER,     //Send, if a player gets added to the world.
        REMOVE_PLAYER,  //Send, if a player gets removed from the world.
        CONTROL_PLAYER, //Send, if I shall take over control for a player.
        MOVEMENT_CHANGE,//Send, if a player control changes.
        DELTA_UPDATE    //Send, if a player position/rot gets an update.
    };
}