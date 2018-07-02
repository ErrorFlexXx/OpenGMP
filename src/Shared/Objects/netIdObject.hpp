#pragma once

#include "idObject.hpp"
#include "../Components/id.hpp"
#include "../Components/netId.hpp"
#include <RakNetTypes.h>

namespace OpenGMP
{
    namespace Objects
    {
        /**
         * @defgroup scriptObject
         * @brief ScriptObjects Elements exposed to scripts
         */

        /**
         * @brief The NetIdObject object
         * @ingroup scriptObject
         */
        class NetIdObject : public IdObject
        {
        public:
            Components::NetId netId; //!< (available script attribute) the RakNet GUID

            Components::NetId GetNetId() const;
            void SetNetId(const Components::NetId &value);

        protected:
            NetIdObject() {} //Abstract
        };
    }
}
