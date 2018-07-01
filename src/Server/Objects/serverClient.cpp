#include "serverClient.hpp"
#include <Shared/Components/authData.hpp>

using namespace RakNet;
using namespace OpenGMP::Objects;
using namespace OpenGMP::Components;

ServerClient::ServerClient()
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


