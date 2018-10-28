#pragma once
#include <BitStream.h>
#include <RakNetTypes.h>

namespace OpenGMP
{
    /**
     * @defgroup scriptObject
     * @brief ScriptObjects Elements exposed to scripts
     */

    /**
     * @brief The NetId component
     * @ingroup scriptObject
     */
    class NetId
    {
    public:
        RakNet::RakNetGUID rakNetId;  //!< (available script attribute) the RakNet guid

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}
