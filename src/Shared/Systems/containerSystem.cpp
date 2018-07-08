#include "containerSystem.hpp"
#include <utils/logger.h>

using namespace OpenGMP::Objects;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Components;

template <class T>
ContainerSystem<T>::ContainerSystem(const size_t &capacity)
    : capacity(capacity)
{
    currentIndex.id = 0;
    container.reserve(capacity); //Reserve memory block
}

template <class T>
T &ContainerSystem<T>::CreateEntity(bool &success, Id &id)
{
    Id freeId = GetFreeId();
    T &obj = container[freeId.id];

    obj.id = freeId;
    id = freeId;
    success = true;
    return obj;
}

template <class T>
T &ContainerSystem<T>::Get(const Id &id, bool &success)
{
    if(0 <= id.id)
    {
        success = true;
        return container[id.id];
    }
    success = false;
    LogError() << "Faulty ID given: " << id.id;
    return failDummy;
}

template <class T>
int ContainerSystem<T>::Remove(const Id &id)
{
    if(0 <= id.id )
    {
        container[id.id].id.id = -1; //Flag id as unset.
        freeGapIds.push_back(id);
        return true;
    }
    return false;
}

template <class T>
int ContainerSystem<T>::Count()
{
    return currentIndex.id - freeGapIds.size();
}

template <class T>
bool ContainerSystem<T>::IsFreeId(const Id &id)
{
    IdObject &obj = dynamic_cast<NetIdObject&>(container[id.id]);
    return obj.id.id == -1;
    return false;
}

template <class T>
Id ContainerSystem<T>::GetFreeId()
{
    //Take a gap if available.
    if(!freeGapIds.empty())
    {
        Id freeGapId = freeGapIds.front();
        freeGapIds.pop_front(); //Remove id from list.
        return freeGapId;
    }

    //Take a new id
    Id freeId = currentIndex;
    currentIndex.id++;
    return freeId;
}

//Compile for specific classes, please:
//template class NetContainerSystem<ServerClient>;

