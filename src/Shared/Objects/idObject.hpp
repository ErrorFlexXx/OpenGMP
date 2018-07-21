#pragma once

#include "../Components/id.hpp"

namespace OpenGMP
{
    namespace Objects
    {
        /**
         * @defgroup scriptObject
         * @brief ScriptObjects Elements exposed to scripts
         */

        /**
         * @brief The IdObject object
         * @ingroup scriptObject
         */
        class IdObject
        {
        public:
            Components::Id id; //!< (available script attribute) the ID

        protected:
            IdObject() {} //Abstract
        };
    }
}
