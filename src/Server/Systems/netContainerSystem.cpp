#include "netContainerSystem.hpp"
#include "../Objects/serverClient.hpp"
#include "../Objects/serverPlayer.hpp"
#include <utils/logger.h>

using namespace OpenGMP::Systems;
using namespace OpenGMP::Objects;
using namespace OpenGMP::Components;
using namespace RakNet;

template <class T>
NetContainerSystem<T>::NetContainerSystem(const size_t &capacity)
    : capacity(capacity)
{
    currentIndex.id = 0;
    container.reserve(capacity); //Reserve memory block
}

template <class T>
T &NetContainerSystem<T>::CreateEntity(bool &success, Components::Id &id, const RakNet::RakNetGUID &rakGuid)
{
    Id freeId = GetFreeId();
    T &obj = container[freeId.id];

    obj.netId.rakNetId = rakGuid;
    obj.id = freeId;
    rakIdMap[obj.netId.rakNetId.ToUint32(obj.netId.rakNetId)] = freeId;
    id = freeId;
    success = true;
    return obj;
}

template <class T>
T &NetContainerSystem<T>::Get(const Components::Id &id, bool &success)
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
T &NetContainerSystem<T>::Get(const RakNet::RakNetGUID &rakId, bool &success)
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
int NetContainerSystem<T>::Remove(const Components::Id &id)
{
    if(0 <= id.id )
    {
        NetIdObject &obj = dynamic_cast<NetIdObject&>(container[id.id]);
        obj.id.id = -1; //Flag id as unset.
        rakIdMap.erase(obj.netId.rakNetId.ToUint32(obj.netId.rakNetId));
        freeGapIds.push_back(id);
        return true;
    }
    return false;
}

template <class T>
int NetContainerSystem<T>::Remove(const RakNet::RakNetGUID &rakId)
{
    Id id = rakIdMap[rakId.ToUint32(rakId)]; //Lookup id
    return Remove(id);
}

template <class T>
int NetContainerSystem<T>::Count()
{
    return currentIndex.id - freeGapIds.size();
}

template <class T>
bool NetContainerSystem<T>::IsFreeId(const Components::Id &id)
{
    NetIdObject &obj = container[id.id];
    return obj.id.id == -1;
    return false;
}

template <class T>
Id NetContainerSystem<T>::GetFreeId()
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
template class NetContainerSystem<ServerClient>;
template class NetContainerSystem<ServerPlayer>;
