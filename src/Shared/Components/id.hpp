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
        Id(int value);
        Id(RakNet::BitStream &stream);

        operator int() const { return id; }
        bool operator==(const Id &rhs) const { return id == rhs.id; }
        bool operator!=(const Id &rhs) const { return id != rhs.id; }

        int32_t id; //!< (available script attribute) an ID

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}
