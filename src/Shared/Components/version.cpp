#include "version.h"

using namespace RakNet;

Version::Version(BitStream &stream)
{
    ReadStream(stream);
}

Version::Version(const uint32_t &version)
    : version(version)
{}

void Version::WriteStream(BitStream &stream)
{
    stream.Write(version);
}

void Version::ReadStream(BitStream &stream)
{
    stream.Read(version);
}
