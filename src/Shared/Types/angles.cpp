#include "angles.hpp"
#include "vec3f.hpp"
#include <cmath>

const float Angles::Pi = 3.1415926535897931f;
const float Angles::TwoPi = 6.2831853071795865f;

Angles::Angles()
{
    m_pitch = 0.f;
    m_yaw = 0.f;
    m_roll = 0.f;
}

Angles Angles::Null()
{
    Angles ret;
    return ret;
}

float Angles::Deg2Rad(float degrees)
{
    return degrees * Pi / 180.f;
}

float Angles::Rad2Deg(float radians)
{
    return radians * 180.f / Pi;
}

float Angles::ClampTo360(float degrees)
{
    degrees = fmod(degrees, 360);
    if(degrees < 0)
        degrees += 360;
    return degrees;
}

float Angles::ClampTo2Pi(float radians)
{
    radians = fmod(radians, TwoPi);
    if(radians < 0)
        radians += TwoPi;
    return radians;
}

float Angles::ClampTo180(float degrees)
{
    degrees = fmod((degrees + 180), 360);
    if(degrees < 0)
        degrees += 360;
    return degrees - 180;
}

float Angles::ClampToPi(float radians)
{
    radians = fmod((radians + Pi),(2 * Pi));
    if(radians < 0)
        radians += 2 * Pi;
    return radians - Pi;
}

float Angles::getYawFromAtVector(Vec3f at)
{
    Vec3f tmp = at.normalise();
    return (float)atan2(-tmp.m_x, tmp.m_z);
}

Angles Angles::fromAtVector(Vec3f at)
{
    Angles ret = Angles::Null();
    ret.setByAtVector(at);
    return ret;
}

Angles::Angles(float data[])
{
    m_pitch = data[0];
    m_yaw   = data[1];
    m_roll  = data[2];
}

Angles::Angles(double pitch, double yaw, double roll)
{
    m_pitch = (float) pitch;
    m_yaw   = (float) yaw;
    m_roll  = (float) roll;
}

Angles::Angles(float pitch, float yaw, float roll)
{
    m_pitch = pitch;
    m_yaw   = yaw;
    m_roll  = roll;
}

Angles Angles::clamp()
{
    Angles ret(ClampToPi(m_pitch), ClampToPi(m_yaw), ClampToPi(m_roll));
    return ret;
}

void Angles::reset()
{
    m_pitch = 0.f;
    m_yaw   = 0.f;
    m_roll  = 0.f;
}

void Angles::set(float pitch, float yaw, float roll)
{
    m_pitch = pitch;
    m_yaw   = yaw;
    m_roll  = roll;
}

void Angles::setByAtVector(Vec3f at)
{
    Vec3f tmp = at.normalise();
    m_pitch = -(float)acos(tmp.m_y) + Pi / 2;
    m_pitch = ClampToPi(m_pitch);
    m_yaw = (float)atan2(-tmp.m_x, tmp.m_z);
    m_roll = 0.f;
}

Vec3f Angles::toRightVector()
{
    float rollSin = (float)sin(m_roll);
    float rollCos = (float)cos(m_roll);
    float yawSin = (float)sin(m_yaw);
    float yawCos = (float)cos(m_yaw);
    Vec3f ret(rollCos * yawCos, rollCos * yawSin, -rollSin);
    return ret;
}

Vec3f Angles::toUpVector()
{
    float rollSin = (float)sin(m_roll);
    float rollCos = (float)cos(m_roll);
    float yawSin = (float)sin(m_yaw);
    float yawCos = (float)cos(m_yaw);
    float pitchSin = -(float)cos(m_pitch);
    float pitchCos = (float)sin(m_pitch);
    Vec3f ret(pitchSin * rollSin * yawCos - pitchCos * yawSin,
              pitchSin * rollSin * yawSin + pitchCos * yawCos,
              pitchSin * rollCos);
    return ret;
}

Vec3f Angles::toAtVector()
{
    float rollSin = (float)sin(m_roll);
    float rollCos = (float)cos(m_roll);
    float yawSin = (float)sin(m_yaw);
    float yawCos = (float)cos(m_yaw);
    float pitchSin = -(float)cos(m_pitch);
    float pitchCos = (float)sin(m_pitch);
    Vec3f ret(pitchCos * rollSin * yawCos + pitchSin * yawSin,
              pitchCos * rollSin * yawSin - pitchSin * yawCos,
              pitchCos * rollCos);
    return ret;
}

/* Operators */

float Angles::operator [](int x)
{
    if(x == 0)
        return m_pitch;
    else if(x == 1)
        return m_yaw;
    else if(x == 2)
        return m_roll;
    else
        return 0.0f;
}

Angles Angles::operator +(const Angles& rhs)
{
    Angles ret(m_pitch + rhs.m_pitch, m_yaw + rhs.m_yaw, m_roll + rhs.m_roll);
    return ret;
}

float Angles::operator *(const Angles& rhs)
{
     return m_pitch * rhs.m_pitch + m_yaw * rhs.m_yaw + m_roll * rhs.m_roll;
}

Angles Angles::operator *(float factor)
{
    Angles ret(m_pitch * factor, m_yaw * factor, m_roll * factor);
    return ret;
}

Angles Angles::operator -(const Angles& rhs)
{
    Angles ret(m_pitch - rhs.m_pitch, m_yaw - rhs.m_yaw, m_roll - rhs.m_roll);
    return ret;
}

Angles Angles::operator /(float factor)
{
    Angles ret(m_pitch / factor, m_yaw / factor, m_roll / factor);
    return ret;
}
