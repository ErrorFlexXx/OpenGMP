#include "dynamicCollection.hpp"
#include "../WorldObjects/baseVob.hpp"

template <class T>
DynamicCollection<T>::DynamicCollection(unsigned int maximum)
    : Collection<T>(maximum)
{
}

template <class T>
bool DynamicCollection<T>::Add(T *obj, int &id)
{
    if(id != -1) //Check if obj is unstored
    {
        return false;
    }
    if(0 < m_freeIDs.size()) //If there is a hole in collection
    {
        int holeToFill = m_freeIDs.back();  //The index of the hole
        this->m_colItems[holeToFill] = obj;       //Store the object
        m_freeIDs.pop_back();               //And remove the id from freeIDs pool
        return true;                        //Element successfully added to the collection
    }
    else //No hole in collection. Add a new element on the back.
    {
        if(this->m_maxUsedId < this->m_maximum - 1) //Check for place in the collection
        {
            this->m_colItems.push_back(obj); //Add to the collection
            id = this->m_colItems.size() - 1; //Write the object ID.
            this->m_maxUsedId++;
            return true; //Successfully added obj to collection.
        }
        else
        {
            //Collection full!
            return false;
        }
    }
}

template <class T>
void DynamicCollection<T>::Remove(int &id)
{
    if(0 <= id &&
       id < m_maxUsedId) //Valid id ?
    {
        this->m_colItems[id] = nullptr; //Remove pointer to object from storage
        m_freeIDs.push_back(id);  //Add id to freeIDs list
        id = -1; //Flag id as unstored
    }
    else
    {
        ; //Error - Wants to delete unassigned id.
    }
}

template <class T>
void DynamicCollection<T>::ForEach(std::function<void (const T &)> func)
{
    for(auto &item : this->m_colItems) //For all items in the collection.
    {
        if(item != NULL)    //If there is an object stored
            func(*item);    //Execute given function
    }
}

template <class T>
int DynamicCollection<T>::Count()
{
    return this->m_maxUsedId - this->m_freeIDs.size();
}

template <class T>
int DynamicCollection<T>::Size()
{
    return this->m_colItems.size();
}

template class DynamicCollection<BaseVob>; //Dear compiler: Please compile template for BaseVob Objects.
