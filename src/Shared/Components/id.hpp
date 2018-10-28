#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    /**
     * @defgroup scriptObject
     * @brief ScriptObjects Elements exposed to scripts
     */

    /**
     * @brief The Id component
     * @ingroup scriptObject
     */
    class Id : public IStreamObject
    {
    public:
        Id();

        int id; //!< (available script attribute) an ID

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}
