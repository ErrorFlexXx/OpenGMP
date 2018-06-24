#pragma once

#include "../Objects/iStreamObject.hpp"

class PlayerTalents : public IStreamObject
{
public:
    typedef enum EnumTalents
    {
        Sneaking,
        Thief,
        OpeningLocks,
        SloshBlades,
        CreatingRunes,
        Alchemy,
        CollectingTrophies,
        Acrobatics
    } EnumTalents;

    PlayerTalents();
    int HasTalent(EnumTalents talent);
    void SetTalent(EnumTalents talent);
    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;

    int talents;
};
