#pragma once

#include <cmath>
#include "../GameObjects/idObject.hpp"
#include "../Types/iVobTypeObject.hpp"
#include "../Types/vec3f.hpp"
#include "../Types/angles.hpp"

//Forward declarations:
class World;

/**
 * @brief The Environment struct holds environment informations.
 */
struct Environment
{
    bool m_inAir;
    float m_waterLevel;
    float m_waterDepth;

    Environment()
        : Environment(true, 0.f, 0.f) {}

    Environment(bool inAir, float waterLevel, float waterDepth)
    {
        m_inAir = inAir;
        m_waterLevel = waterLevel;
        m_waterDepth = waterDepth;
    }

    bool operator ==(const Environment& rhs)
    {
        if(m_inAir == rhs.m_inAir &&
           fabs(m_waterLevel - rhs.m_waterLevel) <= 0.01f &&
           fabs(m_waterDepth - rhs.m_waterDepth) <= 0.01f)
            return true;
        else
            return false;
    }

    bool operator !=(const Environment& rhs)
    {
        return !(*this == rhs);
    }
};

/**
 * @brief The BaseVob class is a base class for a vob.
 */
class BaseVob : public IDObject, public IVobTypeObject
{
public:
    /**
     * @brief Spawn spawns the vob in a world with default pos and default angles.
     */
    virtual void Spawn(World *world);

    /**
     * @brief Spawn spawns the vob in a world with a pos and default angles.
     */
    virtual void Spawn(World *world, Vec3f position);

    /**
     * @brief Spawn spawns the vob in a world with a pos and angles.
     */
    virtual void Spawn(World *world, Vec3f position, Angles angles);

    /**
     * @brief Despawn despawns the vob from a world, it is currently in.
     */
    virtual void Despawn();

    /**
     * @brief OnTick has to be implemented by a child, called on tick update.
     */
    virtual void OnTick(unsigned long long now) = 0;

    /**
     * @brief WriteStream specifies how a base vob can be represented in a stream.
     */
    virtual void WriteStream(RakNet::BitStream &writeStream);

    /**
     * @brief ReadStream specifies how a base vob can be read from a stream.
     */
    virtual void ReadStream(RakNet::BitStream &readStream);

    /**
     * @brief IsSpawned returns wether the vob is currently spawned in a world or not.
     */
    bool IsSpawned() const;

    /**
     * @brief GetPosition returns the current position of this vob.
     */
    Vec3f GetPosition() const;

    /**
     * @brief GetAngles returns the current angles of this vob.
     */
    Angles GetAngles() const;

    /**
     * @brief GetAtVector returns the current at vector.
     */
    Vec3f GetAtVector() const;

    /**
     * @brief SetPosition sets the position of this vob.
     */
    void SetPosition(const Vec3f position);

    /**
     * @brief SetAngles sets new angles for this vob.
     */
    void SetAngles(const Angles angles);

    /**
     * @brief SetAtVector sets the current at vector.
     */
    void SetAtVector(const Vec3f at);

    /**
     * @brief GetEnvironment returns a copy of the current environment.
     * @return
     */
    Environment GetEnvironment() const;

protected:
    BaseVob();      //Abstract class
    Vec3f m_pos;    //!< Position of this base vob.
    Angles m_ang;   //!< Angle of this base vob.
    Environment m_environment;  //!< Current environment of this base vob.
    World *m_world; //!< A pointer to the world the vob is currently in.
};
