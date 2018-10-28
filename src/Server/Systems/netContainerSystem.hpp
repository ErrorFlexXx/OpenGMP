#pragma once

#include <Shared/Components/id.hpp>
#include <Shared/Objects/netIdObject.hpp>
#include <RakNetTypes.h>
#include <vector>
#include <list>
#include <unordered_map>

namespace OpenGMP
{
    /**
     * @brief The NetContainerSystem class
     *   Stores objects, which are NetIdObjects with Id and RakNetGuid.
     */
    template<class T>
    class NetContainerSystem
    {
    public:
        NetContainerSystem<T>(const size_t &capacity);

        T &CreateEntity(bool &success, Id &id, const RakNet::RakNetGUID &rakGuid);
        T &Get(const Id &id, bool &success);
        T &Get(const RakNet::RakNetGUID &rakId, bool &success);
        int Remove(const Id &id);
        int Remove(const RakNet::RakNetGUID &rakId);
        int Count();

        size_t capacity;

    private:
        /**
         * @brief GetFreeId
         * @return the next free Id in the container.
         */
        Id GetFreeId();

        /**
         * @brief IsFreeId checks if the slot is really free
         * @param id to check
         * @return true if free, false otherwise
         */
        bool IsFreeId(const Id &id);

        T failDummy;                    //<! Failure dummy for crash reference returning.
        Id currentIndex;    //<! Current index, without attention to gaps.
        std::list<Id> freeGapIds;       //<! Gap list with free IDs between 0 and currentIndex.
        std::vector<T> container;
        std::unordered_map<unsigned int, Id> rakIdMap;
    };
}
