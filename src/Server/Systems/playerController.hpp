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

    /**
     * @brief The PlayerController class
     *   Responsible for streaming player and it's controls to clients.
     */
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
         * @brief Process processes RakNet messages reagarding PlayerController messages.
         * @param packet the inbound RakNet::Packet to process.
         */
        void Process(RakNet::Packet *packet);

        /**
         * @brief SpawnPlayer spawns a player in a world.
         *   Adds a player to a world and notifies all clients in a world about it.
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

        void BuildAddPlayerPacket(RakNet::BitStream &bs, const ServerPlayer &player);
    };
}
