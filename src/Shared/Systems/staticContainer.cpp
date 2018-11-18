#include "staticContainer.hpp"
#ifndef OPENGMPCLIENT
#include <Server/Objects/serverWorld.hpp>
#else
#include <Client/Objects/clientWorld.hpp>
#include <Client/Objects/clientPlayer.hpp>
#endif
#include <iostream>

using namespace OpenGMP;

template <class T>
StaticContainer<T>::StaticContainer(const size_t &capacity)
    : capacity(capacity)
{
    container.reserve(capacity); //Reserve memory block
}

template <class T>
T &StaticContainer<T>::Get(size_t id)
{
    CheckSpace(id);
    container[id].id = id;
    return container[id];
}

template <class T>
void StaticContainer<T>::CheckSpace(size_t index)
{
    while(index >= container.size())
        container.push_back(T());
}

template <class T>
bool StaticContainer<T>::Remove(size_t id)
{
    if(0 <= id && id < container.size())
    {
        container[id] = T();
        return true;
    }
    return false;
}

//Compile for specific classes, please:
#ifndef OPENGMPCLIENT
template class StaticContainer<ServerWorld>;
#else
template class StaticContainer<ClientWorld>;
template class StaticContainer<ClientPlayer>;
#endif

