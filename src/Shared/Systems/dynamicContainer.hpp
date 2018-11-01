#pragma once

#include <Shared/Objects/idObject.hpp>
#include <vector>
#include <list>

namespace OpenGMP
{
    /**
     * @brief The DynamicContainer class
     *   Stores objects and assigns the next free id.
     *   The id is never choosable.
     */
    template<class T>
    class DynamicContainer
    {
    public:
        DynamicContainer<T>(const size_t &capacity);

        /**
         * @brief CreateEntity returns a new object reference
         * @param id (out) id of the new stored element.
         * @return a reference to the stored object.
         */
        T &CreateEntity(Id &id);

        /**
         * @brief Get returns a reference to an stored object
         * @param id of the stored element.
         * @param success true, if the id points to a stored element.
         * @return a reference to the stored object.
         */
        T &Get(const Id &id, bool &success);

        /**
         * @brief Remove marks a slot as free.
         * @param id (in) of the slot to free.
         * @return true, if the slot was used before.
         */
        bool Remove(const Id &id);

        /**
         * @brief Count Returns the currently stored elements in the container.
         * @return the count of stored elements.
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

        T failDummy;                //<! Failure dummy for crash reference returning.
        Id currentIndex;            //<! Current index, without attention to gaps.
        std::list<Id> freeGapIds;   //<! Gap list with free IDs between 0 and currentIndex.
        std::vector<T> container;   //<! The actual container.
    };
}
