#pragma once

#include "networkSystemMessages.hpp"
#include <Shared/Types/angles.hpp>

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

    struct AddPlayerMessage
    {
        static inline void Pack(RakNet::BitStream &bsOut, const Player &player)
        {
            bsOut.Write((NetMessage)NetworkSystemMessages::PlayerController);
            bsOut.Write((NetMessage)PlayerControllerMessages::ADD_PLAYER);
            player.id.WriteStream(bsOut);

            player.position.WriteStream(bsOut);
            player.rotation.WriteStream(bsOut);
            player.scale.WriteStream(bsOut);
            player.skills.WriteStream(bsOut);
            player.talents.WriteStream(bsOut);
            player.visual.WriteStream(bsOut);
            player.attributes.WriteStream(bsOut);
        }

        static inline bool Unpack(RakNet::BitStream &bsIn, Player &player)
        {
            bool success;
            success = player.position.ReadStream(bsIn);
            if(success) success = player.rotation.ReadStream(bsIn);
            if(success) success = player.scale.ReadStream(bsIn);
            if(success) success = player.skills.ReadStream(bsIn);
            if(success) success = player.talents.ReadStream(bsIn);
            if(success) success = player.visual.ReadStream(bsIn);
            if(success) success = player.attributes.ReadStream(bsIn);
            return success;
        }
    };

    struct PositionUpdateMessage
    {
        static inline void Pack(RakNet::BitStream &bsOut, const Player &player)
        {
            Pack(bsOut, player.id, player.position, player.rotation);
        }

        static inline void Pack(RakNet::BitStream &bsOut, const Id &id, const Vec3f &position, const Vec3f &rotation)
        {
            bsOut.Write((NetMessage)NetworkSystemMessages::PlayerController);
            bsOut.Write((NetMessage)PlayerControllerMessages::POSITION_UPDATE);
            id.WriteStream(bsOut);

            position.WriteStream(bsOut);
            bsOut.Write(rotation.GetYawFromAtVector());
        }

        static inline bool Unpack(RakNet::BitStream &bsIn, Player &player)
        {
            bool success;
            float yaw;
            success = player.position.ReadStream(bsIn);
            if (success) success = bsIn.Read(yaw);
            player.rotation.GetAtVectorFromYaw(yaw);
            return success;
        }
    };

    struct MovementChangeMessage
    {
        static inline void Pack(RakNet::BitStream &bsOut, const Player &player)
        {
            bsOut.Write((NetMessage)NetworkSystemMessages::PlayerController);
            bsOut.Write((NetMessage)PlayerControllerMessages::MOVEMENT_CHANGE);
            player.id.WriteStream(bsOut);

            player.movement.WriteStream(bsOut);
        }

        static inline bool Unpack(RakNet::BitStream &bsIn, Player &player)
        {
            bool success;
            success = player.movement.ReadStream(bsIn);
            return success;
        }
    };
}
