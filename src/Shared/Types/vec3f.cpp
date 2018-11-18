#include "vec3f.hpp"
#include <math.h>

using namespace OpenGMP;

Vec3f::Vec3f()
    : Vec3f(0.f, 0.f, 0.f)
{
}

Vec3f::Vec3f(float data[])
    : Vec3f(data[0], data[1], data[2])
{
}

Vec3f::Vec3f(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
{
}

Vec3f::Vec3f(const Vec3f& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vec3f::Vec3f(RakNet::BitStream &stream)
{
    ReadStream(stream);
}

void Vec3f::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(x);
    stream.Write(y);
    stream.Write(z);
}

bool Vec3f::ReadStream(RakNet::BitStream &stream)
{
    bool success;

                success = stream.Read(x);
    if(success) success = stream.Read(y);
    if(success) success = stream.Read(z);

    return success;
}

void Vec3f::Reset()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

void Vec3f::Set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vec3f::GetLength() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

Vec3f Vec3f::Normalise() const
{
    float length = GetLength();
    if(length != 0)
    {
        Vec3f ret(x / length, y / length, z / length);
        return ret;
    }
    return *this;
}

float Vec3f::GetDistance(const Vec3f &value) const
{
    return (*this - value).GetLength();
}

float Vec3f::GetDistancePlanar(const Vec3f &value) const
{
    return (float)sqrt((x - value.x) * (x - value.x) + (z - value.z) * (z - value.z));
}

Vec3f Vec3f::Cross(const Vec3f &value) const
{
    Vec3f ret( y * value.z - z * value.y,
               z * value.x - x * value.z,
               x * value.y - y * value.x);
    return ret;
}

bool Vec3f::IsNull() const
{
    if(x < NULL_LIMIT && x > -NULL_LIMIT &&
       y < NULL_LIMIT && y > -NULL_LIMIT &&
       z < NULL_LIMIT && z > -NULL_LIMIT)
        return true;
    else
        return false;
}

float Vec3f::ClampToWorldLimits(float correct)
{
    if(correct < - GOTHIC_POS_LIMIT)
        correct = -GOTHIC_POS_LIMIT;
    else if(correct > GOTHIC_POS_LIMIT)
        correct = GOTHIC_POS_LIMIT;
    else if(correct == 0.f)
        correct = NULL_LIMIT;
    return correct;
}

Vec3f Vec3f::ClampToWorldLimits() const
{
    Vec3f ret(x, y, z);
    ret.x = Vec3f::ClampToWorldLimits(ret.x);
    ret.y = Vec3f::ClampToWorldLimits(ret.y);
    ret.z = Vec3f::ClampToWorldLimits(ret.z);
    return ret;
}

Vec3f Vec3f::CorrectDirection() const
{
    if(this->IsNull())
    {
        Vec3f ret(0, 0, 1);
        return ret;
    }
    Vec3f ret = this->Normalise();
    return ret;
}

/***************/
/** Operators **/
/***************/

float Vec3f::operator [](int x) const
{
    if(x == 0)
        return this->x;
    else if(x == 1)
        return this->y;
    else if(x ==2)
        return this->z;
    return 0.0f;
}

Vec3f Vec3f::operator +(const Vec3f& rhs) const
{
    return Vec3f(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3f Vec3f::operator -(const Vec3f& rhs) const
{
    return Vec3f(x - rhs.x, y - rhs.y, z - rhs.z);
}

float Vec3f::operator *(const Vec3f& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vec3f Vec3f::operator *(const float factor) const
{
    return Vec3f(x * factor, y * factor, z * factor);
}

Vec3f Vec3f::operator /(const float factor) const
{
    return Vec3f(x / factor, y / factor, z / factor);
}

bool Vec3f::operator ==(const Vec3f& rhs) const
{
    return ((*this) - rhs).IsNull();
}

bool Vec3f::operator !=(const Vec3f& rhs) const
{
    return !((*this) == rhs);
}

bool Vec3f::operator ==(const float b) const
{
    return this->GetLength() == b;
}

bool Vec3f::operator !=(const float b) const
{
    return this->GetLength() != b;
}
