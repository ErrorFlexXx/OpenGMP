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
T &StaticContainer<T>::Get(int id)
{
    CheckSpace(id);
    return container[id];
}

template <class T>
void StaticContainer<T>::CheckSpace(int index)
{
    if (container.size() <= index)
        for (size_t i = container.size(); i < 1 + index - container.size(); i++)
            container.push_back(T());
}

template <class T>
bool StaticContainer<T>::Remove(int id)
{
    if(0 <= id && id < container.size())
    {
        container[id].id = -1; //Flag id as unset.
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

