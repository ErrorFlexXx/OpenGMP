#pragma once

#include <string>
#include "../Components/string.hpp"
#include "../Objects/netIdObject.hpp"

namespace OpenGMP
{
    class World : public IdObject
    {
    public:
        String worldName;
    };
}
