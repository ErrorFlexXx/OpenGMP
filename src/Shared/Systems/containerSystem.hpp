#pragma once

#include <Shared/Objects/netIdObject.hpp>
#include <vector>
#include <list>

namespace OpenGMP
{
    /**
     * @brief The ContainerSystem class
     *   Stores objects, which are NetIdObjects with Id.
     */
    template<class T>
    class ContainerSystem
    {
    public:
        ContainerSystem<T>(const size_t &capacity);

        T &CreateEntity(bool &success, Id &id);
        T &Get(const Id &id, bool &success);
        int Remove(const Id &id);
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

        T failDummy;                //<! Failure dummy for crash reference returning.
        Id currentIndex;            //<! Current index, without attention to gaps.
        std::list<Id> freeGapIds;   //<! Gap list with free IDs between 0 and currentIndex.
        std::vector<T> container;
    };
}
