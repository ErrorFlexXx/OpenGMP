#pragma once

#include "gameObject.hpp"
#include <BitStream.h>

class IDObject : public GameObject
{
public:
    virtual int GetID() const;
    virtual void SetID(const int id);
    virtual bool GetStatic() const;
    virtual void SetStatic(const bool isStatic);
    virtual void WriteStream(RakNet::BitStream &writeStream);
    virtual void ReadStream(RakNet::BitStream &readStream);
    //Constants
    static const int MaxId; //!< Constant of biggeste possible id.

protected:
    virtual void CanChangeNow();
    bool m_isCreated = false;
    int m_collID = -1;
    int m_dynID = -1;

private:
    int m_id = -1;
    bool m_isStatic = false;
};
