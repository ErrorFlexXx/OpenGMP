#pragma once

#include <string>
#include "../Objects/netIdObject.hpp"
#include "../Systems/containerSystem.hpp"

namespace OpenGMP
{
    class World : public NetIdObject
    {
    public:
        std::string worldName;
    };
}
