#include "idObject.hpp"
#include <Shared/Types/forbiddenException.hpp>

const int IDObject::MaxId = 65000;

int IDObject::GetID() const
{
    return m_id;
}

void IDObject::SetID(const int id)
{
    CanChangeNow();
    m_id = id;
}

bool IDObject::GetStatic() const
{
    return m_isStatic;
}

void IDObject::SetStatic(const bool isStatic)
{
    CanChangeNow();
    m_isStatic = isStatic;
}

void IDObject::WriteStream(RakNet::BitStream &writeStream)
{
    writeStream.Write(m_id);
}

void IDObject::ReadStream(RakNet::BitStream &readStream)
{
    readStream.Read(m_id);
}

void IDObject::CanChangeNow()
{
    if(m_isCreated)
        throw ForbiddenException("Can't modify object if it is currently spawned!");
}
