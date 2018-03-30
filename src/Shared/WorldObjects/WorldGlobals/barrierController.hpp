#pragma once

#include "skyController.hpp"
#include <BitStream.h>

class World;

class BarrierController : public SkyController
{
public:
    BarrierController(World *world);
};

