#include "staticCollection.hpp"
#include "idObject.hpp"
#include "../WorldObjects/baseVob.hpp"

using namespace std;

template <class T>
StaticCollection<T>::StaticCollection(unsigned int maximum)
    : Collection<T>(maximum)
{
}

template <class T>
bool StaticCollection<T>::Add(T *obj)
{
    //Is there a pointer non NULL pointer given ?
    if(obj == nullptr)
    {
        //Insert object thats null :(
        return false;
    }

    //And a valid id ?
    int id = ((IDObject*)obj)->GetID();
    if(id < 0 ||            //Id smaller than 0
       this->m_maximum <= id) //or greather equal maximum size ?
    {
        //Insert object with out of range id :(
        return false;
    }

    //Then create space if necessary
    if(static_cast<int>(this->m_colItems.size()) <= id)
        this->m_colItems.resize(id + 1, nullptr); //Resize and fill unused slots with NULL
    else if(this->m_colItems[id] == nullptr) //Or check if storage place is occopied
    {
        //Insert object with already registered id :(
        return false;
    }

    //Finally write it to the static collection
    this->m_colItems[id] = obj;
    return true;
}

template <class T>
void StaticCollection<T>::Remove(T *obj)
{
    if(obj == nullptr)
    {
        //Remove an object thats null :(
        return;
    }

    int id = ((IDObject*)obj)->GetID();
    this->m_colItems[id] = nullptr;
}

template <class T>
bool StaticCollection<T>::TryGet(int id, T *ret)
{
    if(id < 0 ||
       static_cast<int>(this->m_colItems.size()) <= id)
    {
        return false;
    }
    ret = this->m_colItems[id];
    return ret != nullptr;
}

template <class T>
template <class TSPECIFIC>
bool StaticCollection<T>::TryGetSpecific(int id, TSPECIFIC *ret)
{
    if(id < 0 ||
       this->m_colItems.size() <= id)
    {
        return false;
    }
    try
    {
        TSPECIFIC *castedPtr = dynamic_cast<TSPECIFIC*>(this->m_colItems[id]);
        ret = castedPtr;
        return ret != nullptr;
    }
    catch(exception &exp)
    {
        //Bad cast :(
        ret = nullptr;
        return false;
    }
    return false;
}

template <class T>
bool StaticCollection<T>::ContainsID(int id) const
{
    if(0 <= id && id < static_cast<int>(this->m_colItems.size()))
        return this->m_colItems[id] != nullptr;
    return false;
}

template class StaticCollection<BaseVob>; //Dear compiler: Please compile template for BaseVob Objects.
