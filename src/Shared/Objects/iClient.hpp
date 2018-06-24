#pragma once

#include <string>

#include "../Components/version.h"
#include "../Components/authData.h"
#include <BitStream.h>

class IPlayer;

/**
 * @describe The IClient class
 *   This class covers a network client.
 */
class IClient
{
public:
    //Server constructor
    IClient(RakNet::BitStream &stream)
        : player(nullptr)
        , version(stream)
        , authData(stream) {}

    //Client constructor
    IClient(const Version &version, const AuthData &authData)
        : player(nullptr)
        , version(version)
        , authData(authData) {}

    //Attributes
    IPlayer *player;        //!< Client controlled player.
    Version version;        //!< Client version
    AuthData authData;    //!< Auth data of the client.
};
