#pragma once

#include <Shared/GameObjects/idObject.hpp>
#include <Shared/Types/iVobTypeObject.hpp>
#include <Shared/GameObjects/staticCollection.cpp>

class BaseVobInstance : public IDObject, public IVobTypeObject
{
public:
    static StaticCollection<BaseVobInstance*> idColl;
    int m_collTypeID = -1;
    int m_dynTypeID = -1;
protected:

};
