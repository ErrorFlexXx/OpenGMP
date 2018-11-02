#include "dynamicContainer.hpp"
#include <Server/Objects/serverWorld.hpp>

using namespace OpenGMP;

template <class T>
DynamicContainer<T>::DynamicContainer(const size_t &capacity)
    : capacity(capacity)
{
    currentIndex.id = 0;
    container.reserve(capacity); //Reserve memory block
}

template <class T>
T &DynamicContainer<T>::CreateEntity(Id &id)
{
    Id freeId = GetFreeId();
    CheckSpace(freeId.id);
    T &obj = container[freeId.id];

    obj.id = freeId;
    id = freeId;
    return obj;
}

template <class T>
void DynamicContainer<T>::CheckSpace(int index)
{
    if(container.size() <= index)
        container.insert(container.end(), 1 + index - container.size(), T());
}

template <class T>
T &DynamicContainer<T>::Get(const Id &id, bool &success)
{
    if(0 <= id.id)
    {
        success = true;
        return container[id.id];
    }
    success = false;
    return failDummy;
}

template <class T>
bool DynamicContainer<T>::Remove(const Id &id)
{
    if(0 <= id.id && id.id < currentIndex.id)
    {
        container[id.id].id.id = -1; //Flag id as unset.
        freeGapIds.push_back(id);
        return true;
    }
    return false;
}

template <class T>
int DynamicContainer<T>::Count()
{
    return currentIndex.id - freeGapIds.size();
}

template <class T>
bool DynamicContainer<T>::IsFreeId(const Id &id)
{
    IdObject &obj = dynamic_cast<IdObject&>(container[id.id]);
    return obj.id.id == -1;
    return false;
}

template <class T>
Id DynamicContainer<T>::GetFreeId()
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
#ifndef OPENGMPCLIENT

#else

#endif
