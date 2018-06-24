#pragma once

#include "../Objects/iStreamObject.hpp"

class PlayerAttributes : public IStreamObject
{
public:
    PlayerAttributes();

    int level;
    int learn_points;
    int experience;
    int experience_next_level;
    int magic_level;
    int health;
    int max_health;
    int mana;
    int max_mana;
    int strength;
    int dexterity;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};
