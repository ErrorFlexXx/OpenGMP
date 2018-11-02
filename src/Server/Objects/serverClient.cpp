#include "serverClient.hpp"
#include <Shared/Components/authData.hpp>
#include <utils/logger.h>

using namespace RakNet;
using namespace OpenGMP;

ServerClient::ServerClient()
    : world(nullptr)
{
}

ServerClient::~ServerClient()
{
}
