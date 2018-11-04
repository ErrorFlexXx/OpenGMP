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
     * @brief The NetDynamicContainer class
     *   Stores objects, which are NetIdObjects with Id and RakNetGuid.
     *   The RakNetGuid allows the lookup of the network client
     *   behind the stored conatiner object. New objects are always created
     *   for the next free ID. The ID is never choosable.
     */
    template<class T>
    class NetDynamicContainer
    {
    public:
        NetDynamicContainer<T>(const size_t &capacity);

        /**
         * @brief CreateEntity returns a new object reference
         * @param id (out) of the new object.
         * @param rakGuid (in), which gets registered for the new object.
         * @return reference to the new object.
         */
        T &CreateEntity(Id &id, const RakNet::RakNetGUID &rakGuid);

        /**
         * @brief CheckSpace creates new elements in the container if necessary.
         * @param index
         */
        void CheckSpace(int index);


        /**
         * @brief Get returns the stored object with given id
         * @param id (in) id of the stored item
         * @param success true if the slot contains an valid item.
         * @return reference to the stored object.
         */
        T &Get(const Id &id, bool &success);

        /**
         * @brief Get returns the stored object with given rak ID
         * @param rakId raknet id of the stored object.
         * @param success true, if the slot contains an valid item.
         * @return reference to the stored object.
         */
        T &Get(const RakNet::RakNetGUID &rakId, bool &success);

        /**
         * @brief Remove marks the slot as free
         * @param id (in) to be freed.
         * @return true, if the slot was a valid id
         */
        bool Remove(const Id &id);

        /**
         * @brief Remove marks the slot as free
         * @param rakId (in) to be freed.
         * @return true, if the slot was a valid id
         */
        bool Remove(const RakNet::RakNetGUID &rakId);

        /**
         * @brief Count returns the currently stored elements.
         * @return the currently stored elements.
         */
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
