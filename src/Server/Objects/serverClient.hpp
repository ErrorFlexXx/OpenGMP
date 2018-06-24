#pragma once

#include <Shared/Objects/iClient.hpp>

class ServerClient : public IClient
{
public:
    ServerClient(RakNet::BitStream &stream);

};
