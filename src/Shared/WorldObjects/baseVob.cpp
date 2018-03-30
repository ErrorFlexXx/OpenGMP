#include "baseVob.hpp"
#include "world.hpp"

BaseVob::BaseVob()
{
    m_pos = Vec3f(0.f, 0.f, 0.f);
    m_ang = Angles(0.f, 0.f, 0.f);
}

void BaseVob::Spawn(World *world)
{
    Spawn(world, m_pos, m_ang);
}

void BaseVob::Spawn(World *world, Vec3f position)
{
    Spawn(world, position, m_ang);
}

void BaseVob::Spawn(World *world, Vec3f position, Angles angles)
{
    if(world == nullptr) //Can't spawn an object nowhere!
    {
        return;
    }
    if(m_isCreated) //Can't spawn a spawned object!
    {
        return;
    }
    m_pos = position.clampToWorldLimits();
    m_ang = angles.clamp();
    m_world->AddVob(this);
    m_world = world;
    m_isCreated = true;
}

void BaseVob::Despawn()
{
    if(!m_isCreated) //Can't despawn object that isn't spawned!
    {
        return;
    }
    m_isCreated = false;
    m_world->RemoveVob(this);
    m_world = nullptr;
}

void BaseVob::WriteStream(RakNet::BitStream &writeStream)
{
    IDObject::WriteStream(writeStream);
    writeStream.Write(m_pos);
    writeStream.Write(m_ang);
}

void BaseVob::ReadStream(RakNet::BitStream &readStream)
{
    IDObject::ReadStream(readStream);
    readStream.Read(m_pos);
    readStream.Read(m_ang);
}

bool BaseVob::IsSpawned() const
{
    return m_isCreated;
}

Vec3f BaseVob::GetPosition() const
{
    return m_pos;
}
