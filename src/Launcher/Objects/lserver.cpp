#include "lserver.hpp"

using namespace OpenGMP;

LServer::LServer()
    : treeItem(nullptr)
{
    qRegisterMetaType<LServer>();
}
