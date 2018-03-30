#include "collection.hpp"
#include "../WorldObjects/baseVob.hpp"

template <class T>
Collection<T>::Collection(unsigned int maximum)
{
    m_maximum = maximum; //Store maximum for this collection
}

template class Collection<BaseVob>; //Dear compiler: Please compile template for BaseVob Objects.
