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

    class PlayerController
    {
    public:
        PlayerController(GameServer &gameServer);

        /**
         * @brief Gets a new player object, assigns an free id and the client.
         * @return The reference of the new player.
         */
        ServerPlayer &GetNewPlayer(ServerClient &client);

        /**
         * @brief SpawnPlayer spawns a player in a world.
         * @param player player object to spawn.
         * @param world world to spawn player in.
         */
        void SpawnPlayer(ServerPlayer &player, ServerWorld &world);

        /**
         * @brief ClientEnteringWorld called from worldSystem, if a client loads a world
         * @param client the client, which is entering the world.
         */
        void ClientEnteringWorld(ServerClient &client);

        /**
         * @brief ControlPlayer lets a client control a player.
         * @param client that shall control the player.
         * @param player that shall be controlled by the player.
         */
        void ControlPlayer(const ServerClient &client, const ServerPlayer &player);

        /**
         * @brief SendPlayerControllerMessage
         * @param dest destination address of the packet.
         * @param bsOut the bitstream of the message.
         */
        void SendPlayerControllerMessage(const RakNet::RakNetGUID &dest, const RakNet::BitStream &bsOut);

    private:
        GameServer &gameServer;
    };
}
