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
    class StaticContainer
    {
    public:
        StaticContainer<T>(const size_t &capacity);
        
        /**
         * @brief Get returns a reference to an stored object
         * @param id of the stored element.
         * @param success true, if the id points to a stored element.
         * @return a reference to the stored object.
         */
        T &Get(const Id &id);

        /**
         * @brief Remove marks a slot as free.
         * @param id (in) of the slot to free.
         * @return true, if the slot was used before.
         */
        bool Remove(const Id &id);

        size_t capacity;

    private:
        /**
         * @brief CheckSpace enlarges the contrainer if needed
         * @param index of requested element
         */
        void CheckSpace(int index);

        std::vector<T> container;   //<! The actual container.
    };
}
