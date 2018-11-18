#pragma once

#include <string>
#include <Shared/Types/string.hpp>
#include "../Objects/netIdObject.hpp"

namespace OpenGMP
{
    class World : public IdObject
    {
    public:
        World() : IdObject() {}
        String worldName;
    };
}
