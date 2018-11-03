#pragma once

#include <string>

namespace RakNet
{
    struct Packet;
    class BitStream;
    struct RakNetGUID;
}

namespace OpenGMP
{
    class GameServer;
    class ServerClient;
    class ServerPlayer;
    class ServerWorld;
    class Id;

    class WorldSystem
    {
    public:
        WorldSystem(GameServer &gameServer);

        /**
         * @brief AddWorld adds a world to the gameserver
         * @param id (in) the id the world can be addressed with
         * @param worldName the name of the world.
         * @return The reference of the new world.
         */
        ServerWorld &AddWorld(int id, std::string &worldName);

        /**
         * @brief GetStoredWorld returns a loaded world object from container
         * @param index of the world
         * @return a ServerWorld reference
         */
        ServerWorld &GetStoredWorld(int index);

        /**
         * @brief LoadWorld let a client load a world.
         * @param client that shall load the world now.
         * @param world the world, that should be loaded.
         */
        void LoadWorld(ServerClient &client, ServerWorld &world);

        /**
         * @brief SendWorldSystemMessage
         * @param dest destination address of the packet.
         * @param bsOut the bitstream of the message.
         */
        void SendWorldSystemMessage(const RakNet::RakNetGUID &dest, const RakNet::BitStream &bsOut);

    private:
        GameServer &gameServer;
    };
}
