#pragma once

#include "idObject.hpp"
#include <functional>
#include <vector>

/**
 * @brief The Collection class
 *  A class to store objects in a vector.
 */
template <class T>
class Collection
{
public:
    Collection<T>(unsigned int maximum = IDObject::MaxId);

protected:
    std::vector<T*> m_colItems; //!< Vector of stored items in the collection
    int m_maximum;              //!< Maximum allowed elements in this collection
};
