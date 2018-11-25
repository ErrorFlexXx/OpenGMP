#pragma once

#include <Shared/Types/string.hpp>
#include <BitStream.h>
#include <RakNetTypes.h>

namespace OpenGMP
{
    /**
     * @defgroup scriptObject
     * @brief ScriptObjects Elements exposed to scripts
     */

    /**
     * @brief The AuthData component
     * @ingroup scriptObject
     */
    class LoginData
    {
    public:
        String loginname;          //!< (available script attribute) the loginname
        String password;           //!< (available script attribute) the cleartext password

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}
