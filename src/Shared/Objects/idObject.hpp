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
        bool operator==(const IdObject &rhs) const { return id == rhs.id; }
        bool operator!=(const IdObject &rhs) const { return id != rhs.id; }

    protected:
        IdObject()
            : id() {} //Abstract
    };
}
