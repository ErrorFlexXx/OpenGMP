#pragma once

#include "../Components/color.h"
#include "../Components/position.h"
#include "../Components/scale.h"
#include "../Components/id.h"
#include "../Components/playerTalents.h"
#include "../Components/playerAttributes.h"
#include "../Components/playerSkills.h"
#include "../Components/playerVisual.h"

/**
 * @describe The IPlayer class
 *   A player covers a NPC that can be controlled
 */
class IPlayer
{
public:
    virtual ~IPlayer() {}

private:
    IPlayer();  //Abstract class

protected:
    Id id;
    Position position;
    Scale scale;
    Color chatColor;
    PlayerTalents talents;
    PlayerAttributes attributes;
    PlayerSkills skills;
    PlayerVisual visual;
};
