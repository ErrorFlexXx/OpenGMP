#pragma once

#include <Shared/WorldObjects/world.hpp>
#include <string>

class ServerWorld : public World
{
public:
    ServerWorld(const std::string worldName, const std::string worldFilename);

};
