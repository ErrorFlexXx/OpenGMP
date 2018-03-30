#pragma once

#include "collection.cpp"
#include "idObject.hpp"
#include <functional>
#include <vector>

/**
 * @brief The StaticCollection class
 * Stores objects at a requested storage place ID
 */
template <class T>
class StaticCollection : public Collection<T>
{
public:
    StaticCollection<T>(unsigned int maximum = IDObject::MaxId);

    /**
     * @brief Add
     *  Adds a new element to the collection
     * @param obj Pointer to object to store in this collection
     * @param id Reference to ID to store the storage position in
     */
    bool Add(T *obj);

    /**
     * @brief Remove
     *  Removed an element in the collection
     * @param id
     * @return Success/Fail (true/false)
     */
    void Remove(T *obj);

    /**
     * @brief TryGet
     * @param id Requested index
     * @param ret Returned object pointer
     * @return True on success
     */
    bool TryGet(int id, T *ret);

    /**
     * @brief TryGet<TSPECIFIC>
     * @param id Requested index
     * @param ret Returned typecasted object
     * @return True on success
     */
    template <class TSPECIFIC>
    bool TryGetSpecific(int id, TSPECIFIC *ret);

    /**
     * @brief ContainsID
     * @param id Requested ID
     * @return True if true
     */
    bool ContainsID(int id) const;

private:
    //std::vector<T*> colItems; //Inherited vector from Collection
    void Insert(T *obj, int id); //Internal procedure to insert an item
    //int maximum; //Inherited maximum from Collection
};
