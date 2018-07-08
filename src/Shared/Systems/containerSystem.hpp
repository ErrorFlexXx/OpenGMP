#pragma once

#include <Shared/Components/id.hpp>
#include <vector>
#include <list>

namespace OpenGMP
{
    namespace Systems
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

            T &CreateEntity(bool &success, Components::Id &id);
            T &Get(const Components::Id &id, bool &success);
            int Remove(const Components::Id &id);
            int Count();

            size_t capacity;

        private:
            /**
             * @brief GetFreeId
             * @return the next free Id in the container.
             */
            Components::Id GetFreeId();

            /**
             * @brief IsFreeId checks if the slot is really free
             * @param id to check
             * @return true if free, false otherwise
             */
            bool IsFreeId(const Components::Id &id);

            T failDummy; //<! Failure dummy for crash reference returning.
            Components::Id currentIndex; //<! Current index, without attention to gaps.
            std::list<Components::Id> freeGapIds; //<! Gap list with free IDs between 0 and currentIndex.
            std::vector<T> container;
        };
    }
}
