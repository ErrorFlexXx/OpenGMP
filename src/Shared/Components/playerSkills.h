#pragma once

#include "../Objects/iStreamObject.hpp"

class PlayerSkills : public IStreamObject
{
public:
    PlayerSkills();

    int skill_1h;
    int skill_2h;
    int skill_bow;
    int skill_cbow;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};
