#pragma once

#include <string>
#include <BitStream.h>
#include <RakNetTypes.h>
#include <ostream>

namespace OpenGMP
{
    /**
     * @brief The String component
     */
    class String
    {
    public:
        String();
        String(const std::string &value);
        String(const char *value);

        operator std::string() { return text; }
        String &operator<< (float arg);
        String &operator<< (const String &arg);
        std::string text;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

//Support shifting in ostream (used in logger impl.)
std::ostream & operator<< (std::ostream &out, const OpenGMP::String &t);
