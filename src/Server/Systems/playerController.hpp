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
        ServerPlayer &GetNewPlayer(const ServerClient &client);

        /**
         * @brief RemoveClientPlayer removes all player that belongs to a client
         * @param client that belongs to the player that are going to be removed.
         */
        void RemoveClientPlayer(ServerClient &client);

        /**
         * @brief RemovePlayer removes a player entirely from the server.
         * @param player to be deleted.
         */
        void RemovePlayer(ServerPlayer &player);

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
        void SpawnPlayer(ServerPlayer &player, const ServerWorld &world);

        /**
         * @brief DespawnPlayer removes a player from a world
         * @param player to be removed
         */
        void DespawnPlayer(ServerPlayer &player);

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
        void ControlPlayer(const ServerClient &client, ServerPlayer &player);

        /**
         * @brief StopControl stops this client from controlling a player.
         * @param client that should no longer control a player
         */
        void StopControl(const ServerClient &client);

        /**
         * @brief SendPlayerControllerMessage
         * @param dest destination address of the packet.
         * @param bsOut the bitstream of the message.
         */
        void SendPlayerControllerMessage(const RakNet::RakNetGUID &dest, const RakNet::BitStream &bsOut);

    private:
        GameServer &gameServer;

        /**
         * @brief BuildAddPlayerPacket Insert data for an add player packet to a bitstream.
         * @param bs to be prepared
         * @param player to be added.
         */
        void BuildAddPlayerPacket(RakNet::BitStream &bs, const ServerPlayer &player);
    };
}
