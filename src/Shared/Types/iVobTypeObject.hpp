#pragma once

#include "vobTypes.hpp"

/**
 * @brief The IVobTypeObject class
 *  Interface for Vobs of all kinds
 */
class IVobTypeObject
{
public:
    IVobTypeObject() {}
    virtual Types::VobTypes VobType() const { return m_vobType; }

protected:
    Types::VobTypes m_vobType;
};
