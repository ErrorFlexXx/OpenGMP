#include "netDynamicContainer.hpp"
#include "../Objects/serverClient.hpp"
#include "../Objects/serverPlayer.hpp"
#include "../Objects/serverWorld.hpp"
#include <utils/logger.h>

using namespace OpenGMP;
using namespace RakNet;

template <class T>
NetDynamicContainer<T>::NetDynamicContainer(const size_t &capacity)
    : capacity(capacity)
{
    currentIndex.id = 0;
    container.reserve(capacity); //Reserve memory block
}

template <class T>
T &NetDynamicContainer<T>::CreateEntity(const RakNet::RakNetGUID &rakGuid)
{
    Id freeId = GetFreeId();
    CheckSpace((size_t)freeId.id);
    T &obj = container[freeId.id];

    obj.netId.rakNetId = rakGuid;
    obj.id = freeId;
    rakIdMap[obj.netId.rakNetId.ToUint32(obj.netId.rakNetId)] = freeId;
    return obj;
}

template <class T>
void NetDynamicContainer<T>::CheckSpace(size_t index)
{
    while (index >= container.size())
    {
        container.push_back(T());
        container.back().id = -1; //Mark as free
    }
}

template <class T>
T &NetDynamicContainer<T>::Get(const Id &id, bool &success)
{
    if(0 <= id)
    {
        success = true;
        return container[id.id];
    }
    success = false;
    LogError() << "Faulty ID given: " << id;
    return failDummy;
}

template <class T>
T &NetDynamicContainer<T>::Get(const RakNet::RakNetGUID &rakId, bool &success)
{
    RakNet::RakNetGUID rakIdKey = rakId;
    Id id = rakIdMap[rakIdKey.ToUint32(rakIdKey)];
    if(0 <= id)
        return Get(id, success);
    LogError() << "Faulty ID behind RakNet GUID: " << id.id;
    success = false;
    return failDummy;
}

template <class T>
bool NetDynamicContainer<T>::Remove(const Id &id)
{
    if(0 <= id.id && id.id < currentIndex.id)
    {
        NetIdObject &obj = dynamic_cast<NetIdObject&>(container[id.id]);
        rakIdMap.erase(obj.netId.rakNetId.ToUint32(obj.netId.rakNetId));
        freeGapIds.push_back(id);
        obj.id = -1; //Flag id as unset.
        return true; //Successfully freed
    }
    return false; //Invalid id!
}

template <class T>
bool NetDynamicContainer<T>::Remove(const RakNet::RakNetGUID &rakId)
{
    if(rakIdMap.find(rakId.ToUint32(rakId)) != rakIdMap.end()) //Id stored in map ?
    {
        Id id = rakIdMap[rakId.ToUint32(rakId)]; //Lookup id
        return Remove(id);
    }
    return false;
}

template <class T>
size_t NetDynamicContainer<T>::Count()
{
    return (size_t)currentIndex - freeGapIds.size();
}

template <class T>
bool NetDynamicContainer<T>::IsFreeId(const Id &id)
{
    NetIdObject &obj = dynamic_cast<NetIdObject&>(container[id.id]);
    return obj.id.id == -1;
}

template <class T>
Id NetDynamicContainer<T>::GetFreeId()
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

/*
 * Iterator class methods
 */
template <class T>
NetDynamicContainer<T>::Iterator::Iterator(NetDynamicContainer<T> *cont, int index)
    : cont(cont)
    , index(index)
{}

template <class T>
T &NetDynamicContainer<T>::Iterator::operator*()
{
    return cont->container[index];
}

template <class T>
typename NetDynamicContainer<T>::Iterator &NetDynamicContainer<T>::Iterator::operator++()
{
    do
    {
        index++;
    }
    while(index < (int)cont->currentIndex.id && (int)cont->container[index].id == -1);
    return *this;
}

template <class T>
bool NetDynamicContainer<T>::Iterator::operator !=(NetDynamicContainer<T>::Iterator &other)
{
    return index != other.index;
}

template <class T>
bool NetDynamicContainer<T>::Iterator::operator ==(NetDynamicContainer<T>::Iterator &other)
{
    return index == other.index;
}

//Compile for specific classes, please:
template class NetDynamicContainer<ServerClient>;
template class NetDynamicContainer<ServerPlayer>;
