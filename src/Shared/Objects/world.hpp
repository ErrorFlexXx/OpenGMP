#pragma once

#include <string>
#include "../Objects/netIdObject.hpp"

namespace OpenGMP
{
    class World : public IdObject
    {
    public:
        std::string worldName;
    };
}
