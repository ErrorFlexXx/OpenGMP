#include "version.hpp"

using namespace RakNet;
using namespace OpenGMP::Components;

Version::Version()
    : version(0)
{}

Version::Version(uint32_t version)
    : version(version)
{
}

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
