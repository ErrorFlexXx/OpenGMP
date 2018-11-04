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
T &NetDynamicContainer<T>::CreateEntity(Id &id, const RakNet::RakNetGUID &rakGuid)
{
    Id freeId = GetFreeId();
    CheckSpace(freeId.id);
    T &obj = container[freeId.id];

    obj.netId.rakNetId = rakGuid;
    obj.id = freeId;
    rakIdMap[obj.netId.rakNetId.ToUint32(obj.netId.rakNetId)] = freeId;
    id = freeId;
    return obj;
}

template <class T>
void NetDynamicContainer<T>::CheckSpace(int index)
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
T &NetDynamicContainer<T>::Get(const RakNet::RakNetGUID &rakId, bool &success)
{
    RakNet::RakNetGUID rakIdKey = rakId;
    Id id = rakIdMap[rakIdKey.ToUint32(rakIdKey)];
    if(0 <= id.id)
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
        obj.id.id = -1; //Flag id as unset.
        rakIdMap.erase(obj.netId.rakNetId.ToUint32(obj.netId.rakNetId));
        freeGapIds.push_back(id);
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
int NetDynamicContainer<T>::Count()
{
    return currentIndex.id - freeGapIds.size();
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

//Compile for specific classes, please:
template class NetDynamicContainer<ServerClient>;
template class NetDynamicContainer<ServerPlayer>;
