#include "vec3f.hpp"
#include <math.h>

Vec3f::Vec3f()
    : Vec3f(0.f, 0.f, 0.f)
{
}

Vec3f::Vec3f(float data[])
{
    m_x = data[0];
    m_y = data[1];
    m_z = data[2];
}

Vec3f::Vec3f(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

Vec3f::Vec3f(const Vec3f& vec)
{
    m_x = vec.m_x;
    m_y = vec.m_y;
    m_z = vec.m_z;
}

void Vec3f::reset()
{
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
}

void Vec3f::set(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

float Vec3f::getLength()
{
    return (float)sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vec3f Vec3f::normalise()
{
    float length = getLength();
    if(length != 0)
    {
        Vec3f ret(m_x / length, m_y / length, m_z / length);
        return ret;
    }
    return *this;
}

float Vec3f::getDistance(Vec3f &value)
{
    return (*this - value).getLength();
}

float Vec3f::getDistancePlanar(Vec3f &value)
{
    return (float)sqrt((m_x - value.m_x) * (m_x - value.m_x) + (m_z - value.m_z) * (m_z - value.m_z));
}

Vec3f Vec3f::cross(Vec3f &value)
{
    Vec3f ret( m_y * value.m_z - m_z * value.m_y,
               m_z * value.m_x - m_x * value.m_z,
               m_x * value.m_y - m_y * value.m_x);
    return ret;
}

bool Vec3f::isNull()
{
    if(m_x < NULL_LIMIT && m_x > -NULL_LIMIT &&
       m_y < NULL_LIMIT && m_y > -NULL_LIMIT &&
       m_z < NULL_LIMIT && m_z > -NULL_LIMIT)
        return true;
    else
        return false;
}

void Vec3f::correctPositionPart(float& correct, float toCorrect)
{
    if(toCorrect < - GOTHIC_POS_LIMIT)
        correct = -GOTHIC_POS_LIMIT;
    else if(toCorrect > GOTHIC_POS_LIMIT)
        correct = GOTHIC_POS_LIMIT;
    else
        correct = toCorrect;
}

Vec3f Vec3f::clampToWorldLimits()
{
    float x, y, z;
    correctPositionPart(x, m_x);
    correctPositionPart(y, m_y);
    correctPositionPart(z, m_z);
    Vec3f ret(x, y, z);
    return ret;
}

Vec3f Vec3f::correctDirection()
{
    if(this->isNull())
    {
        Vec3f ret(0, 0, 1);
        return ret;
    }
    Vec3f ret = this->normalise();
    return ret;
}

/* Operators */

float Vec3f::operator [](int x)
{
    if(x == 0)
        return m_x;
    else if(x == 1)
        return m_y;
    else if(x ==2)
        return m_z;
    return 0.0f;
}

Vec3f Vec3f::operator +(const Vec3f& rhs)
{
    Vec3f ret(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z);
    return ret;
}

Vec3f Vec3f::operator -(const Vec3f& rhs)
{
    Vec3f ret(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z);
    return ret;
}

float Vec3f::operator *(const Vec3f& rhs)
{
    return m_x * rhs.m_x + m_y * rhs.m_y + m_z * rhs.m_z;
}

Vec3f Vec3f::operator *(const float factor)
{
    Vec3f ret(m_x * factor, m_y * factor, m_z * factor);
    return ret;
}

Vec3f Vec3f::operator /(const float factor)
{
    Vec3f ret(m_x / factor, m_y / factor, m_z / factor);
    return ret;
}

bool Vec3f::operator ==(const Vec3f& rhs)
{
    return ((*this) - rhs).isNull();
}

bool Vec3f::operator !=(const Vec3f& rhs)
{
    return !((*this) == rhs);
}

bool Vec3f::operator ==(const float b)
{
    return this->getLength() == b;
}

bool Vec3f::operator !=(const float b)
{
    return this->getLength() != b;
}
