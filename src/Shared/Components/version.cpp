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

void Version::ReadStream(BitStream &stream)
{
    stream.Read(version);
}
