#pragma once

#include "idObject.hpp"
#include "../Components/id.hpp"
#include <RakNetTypes.h>

namespace OpenGMP
{
    namespace Objects
    {
        class NetIdObject : public IdObject
        {
        public:
            RakNet::RakNetGUID guid;

        protected:
            NetIdObject() {} //Abstract
        };
    }
}
