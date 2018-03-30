#pragma once

#include "collection.hpp"
#include "idObject.hpp"
#include <functional>
#include <vector>

/**
 * @brief The DynamicCollection class
 * The dynamic collection stores objects and assigns a free ID to the object.
 * It delivers a method to run a function for every stored object.
 */
template <class T>
class DynamicCollection : public Collection<T>
{
public:
    DynamicCollection<T>(unsigned int maximum = IDObject::MaxId);

    /**
     * @brief Add
     *  Adds a new element to the collection
     * @param obj Pointer to object to store in this collection
     * @param id Reference to ID to store the storage position in
     */
    bool Add(T *obj, int &id);

    /**
     * @brief Remove
     *  Removed an element in the collection
     * @param id
     * @return Success/Fail (true/false)
     */
    void Remove(int &id);

    /**
     * @brief ForEach
     *  Executes a function for each element stored in the collection
     * @param action Action to execute
     */
    void ForEach(std::function<void (const T&)> func);

    /**
     * @brief Count
     * @return Number of stored objects in the collection
     */
    int Count();

    /**
     * @brief Size
     * @return Current used entries of the collection vector
     */
    int Size();

private:
    std::vector<int> m_freeIDs;                 //!< Container to save unsused ids
    int m_maxUsedId;                            //!< Tracks the highest id, registered in the col.
    void Insert(T *obj, int &id, int newID);    //!< Internal procedure to insert an item
};


