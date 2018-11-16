#pragma once

#include "networkSystemMessages.hpp"

namespace OpenGMP
{
    enum PlayerControllerMessages : unsigned char
    {
        ADD_PLAYER,     //Sent, if a player gets added to the world.
        REMOVE_PLAYER,  //Sent, if a player gets removed from the world.
        CONTROL_PLAYER, //Sent, if I shall take over control for a player.
        STOP_CONTROL,   //Sent, if the player control shall be stopped.
        MOVEMENT_CHANGE,//Sent, if a player control changes.
        POSITION_UPDATE,   //Sent, if a player position/rot gets an update.
        ENTERED_WORLD   //Sent, if the player finished entering the world (loading)
    };
}