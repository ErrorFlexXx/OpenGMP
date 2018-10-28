#pragma once

#include "idObject.hpp"
#include "../Components/id.hpp"
#include "../Components/netId.hpp"
#include <RakNetTypes.h>

namespace OpenGMP
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
        NetId netId; //!< (available script attribute) the RakNet GUID

    protected:
        NetIdObject() {} //Abstract
    };
}
