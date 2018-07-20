#include "serverClient.hpp"
#include <Shared/Components/authData.hpp>
#include <utils/logger.h>

using namespace RakNet;
using namespace OpenGMP::Objects;
using namespace OpenGMP::Components;

ServerClient::ServerClient()
{
}

ServerClient::~ServerClient()
{
}

AuthData &ServerClient::GetAuthData()
{
    return authData;
}

void ServerClient::SetAuthData(AuthData authData)
{
    this->authData = authData;
}


