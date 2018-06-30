#pragma once

#include "../Components/id.hpp"

namespace OpenGMP
{
    namespace Objects
    {
        class IdObject
        {
        public:
            Components::Id id;

        protected:
            IdObject() {} //Abstract
        };
    }
}
