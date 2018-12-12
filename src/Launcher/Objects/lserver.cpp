#include "lserver.hpp"

using namespace OpenGMP;

LServer::LServer()
    : isOnline(false)
    , treeItem(nullptr)
{
    qRegisterMetaType<LServer>();
}
