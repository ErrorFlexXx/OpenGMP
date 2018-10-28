#pragma once

#include "../Components/id.hpp"

namespace OpenGMP
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
        Id id; //!< (available script attribute) the ID

    protected:
        IdObject() {} //Abstract
    };
}
