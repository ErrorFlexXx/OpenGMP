#pragma once

#include <Shared/Objects/iStreamObject.hpp>
#include <string>
#include <BitStream.h>
#include <RakNetTypes.h>
#include <ostream>

namespace OpenGMP
{
    /**
     * @brief The String component
     */
    class String : public IStreamObject
    {
    public:
        String();
        String(const std::string &value);
        String(const char *value);

        operator std::string() { return text; }
        std::string text;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

//Support shifting in ostream (used in logger impl.)
std::ostream & operator<< (std::ostream &out, const OpenGMP::String &t);
