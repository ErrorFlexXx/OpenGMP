#include "netContainerSystem.hpp"
#include "../Objects/serverClient.hpp"
#include "../Objects/serverPlayer.hpp"

using namespace OpenGMP::Systems;
using namespace OpenGMP::Objects;
using namespace OpenGMP::Components;
using namespace RakNet;

template <class T>
NetContainerSystem<T>::NetContainerSystem(const size_t &capacity)
{
    currentIndex.id = 0;
    container.reserve(capacity); //Reserve memory block
}

template <class T>
T &NetContainerSystem<T>::CreateEntity(bool &success, Components::Id &id, const RakNet::RakNetGUID &rakGuid)
{
    Id freeId = GetFreeId();
    T &obj = container[freeId.id];

    obj.guid = rakGuid;
    obj.id = freeId;
    rakIdMap[obj.guid.ToUint32(obj.guid)] = freeId;
    id = freeId;
    success = true;
    return obj;
}

template <class T>
T &NetContainerSystem<T>::Get(const Components::Id &id)
{
    return container[id.id];
}

template <class T>
T &NetContainerSystem<T>::Get(const RakNet::RakNetGUID &rakId)
{
    RakNet::RakNetGUID rakIdKey = rakId;
    return Get(rakIdMap[rakIdKey.ToUint32(rakIdKey)]);
}

template <class T>
int NetContainerSystem<T>::Remove(const Components::Id &id)
{
    if(0 <= id.id )
    {
        NetIdObject &obj = dynamic_cast<NetIdObject&>(container[id.id]);
        obj.id.id = -1; //Flag id as unset.
        rakIdMap.erase(obj.guid.ToUint32(obj.guid));
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
