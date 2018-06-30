#pragma once

#include <BitStream.h>

/* No pure virtual functions - Performance optimization
 * Just don't forget to implement Write and ReadStream
 * for each component.
 */

class IStreamObject
{
     void WriteStream(RakNet::BitStream &stream) {}
     void ReadStream(RakNet::BitStream &stream) {}
};
