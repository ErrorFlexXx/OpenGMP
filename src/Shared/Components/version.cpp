#include "version.hpp"
#ifndef LAUNCHER
#include <BitStream.h>
using namespace RakNet;
#endif

using namespace OpenGMP;

Version::Version()
    : version(0)
{}

Version::Version(uint32_t version)
    : version(version)
{
}

#ifndef LAUNCHER
void Version::WriteStream(BitStream &stream) const
{
    stream.Write(version);
}

bool Version::ReadStream(BitStream &stream)
{
    bool success;

    success = stream.Read(version);

    return success;
}
#endif
