#include "staticContainer.hpp"
#include <Server/Objects/serverWorld.hpp>
#include <Client/Objects/clientWorld.hpp>

using namespace OpenGMP;

template <class T>
StaticContainer<T>::StaticContainer(const size_t &capacity)
    : capacity(capacity)
{
    container.reserve(capacity); //Reserve memory block
}

template <class T>
T &StaticContainer<T>::Get(const Id &id)
{
    return container[id.id];
}

template <class T>
bool StaticContainer<T>::Remove(const Id &id)
{
    if(0 <= id.id && id.id < container.size())
    {
        container[id.id].id.id = -1; //Flag id as unset.
        return true;
    }
    return false;
}

//Compile for specific classes, please:
#ifndef OPENGMPCLIENT
template class StaticContainer<ServerWorld>;
#else
template class StaticContainer<ClientWorld>;
#endif

