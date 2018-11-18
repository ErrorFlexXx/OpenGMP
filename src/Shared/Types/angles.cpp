#include "angles.hpp"
#include "vec3f.hpp"
#include <math.h>

using namespace OpenGMP;

const float Angles::Pi = 3.1415926535897931f;
const float Angles::TwoPi = 6.2831853071795865f;

Angles::Angles()
    : pitch(0.f)
    , yaw(0.f)
    , roll(0.f)
{}

Angles::Angles(float data[])
    : pitch(data[0])
    , yaw(data[1])
    , roll(data[2])
{}

Angles::Angles(double pitch, double yaw, double roll)
    : pitch((float) pitch)
    , yaw((float) yaw)
    , roll((float) roll)
{}

Angles::Angles(float pitch, float yaw, float roll)
    : pitch(pitch)
    , yaw(yaw)
    , roll(roll)
{}

Angles Angles::Null()
{
    return Angles();
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
    degrees = fmodf(degrees, 360);
    if(degrees < 0)
        degrees += 360.f;
    return degrees;
}

float Angles::ClampTo2Pi(float radians)
{
    radians = fmodf(radians, TwoPi);
    if(radians < 0)
        radians += TwoPi;
    return radians;
}

float Angles::ClampTo180(float degrees)
{
    degrees = fmodf((degrees + 180), 360);
    if(degrees < 0)
        degrees += 360;
    return degrees - 180;
}

float Angles::ClampToPi(float radians)
{
    radians = fmodf((radians + Pi),(2 * Pi));
    if(radians < 0)
        radians += 2 * Pi;
    return radians - Pi;
}

float Angles::GetYawFromAtVector(const Vec3f &at)
{
    Vec3f tmp = at.Normalise();
    return (float)atan2(-tmp.x, tmp.z);
}

Vec3f Angles::GetAtVectorFromYaw(float yaw)
{
    Vec3f at;
    at.z = sin(yaw);
    at.x = cos(yaw);
    return at;
}

Angles Angles::FromAtVector(const Vec3f &at)
{
    Angles ret;
    ret.SetByAtVector(at);
    return ret;
}

Angles Angles::Clamp()
{
    return Angles(ClampToPi(pitch), ClampToPi(yaw), ClampToPi(roll));
}

void Angles::Reset()
{
    pitch = 0.f;
    yaw   = 0.f;
    roll  = 0.f;
}

void Angles::Set(float pitch, float yaw, float roll)
{
    this->pitch = pitch;
    this->yaw   = yaw;
    this->roll  = roll;
}

void Angles::SetByAtVector(const Vec3f &at)
{
    Vec3f tmp = at.Normalise();
    pitch     = -(float)acos(tmp.y) + Pi / 2;
    pitch     = ClampToPi(pitch);
    yaw       = (float)atan2(-tmp.x, tmp.z);
    roll      = 0.f;
}

Vec3f Angles::ToRightVector()
{
    float rollSin = (float)sin(roll);
    float rollCos = (float)cos(roll);
    float yawSin  = (float)sin(yaw);
    float yawCos  = (float)cos(yaw);

    return Vec3f(rollCos * yawCos, rollCos * yawSin, -rollSin);
}

Vec3f Angles::ToUpVector()
{
    float rollSin  = (float)sin(roll);
    float rollCos  = (float)cos(roll);
    float yawSin   = (float)sin(yaw);
    float yawCos   = (float)cos(yaw);
    float pitchSin = -(float)cos(pitch);
    float pitchCos = (float)sin(pitch);

    return Vec3f (pitchSin * rollSin * yawCos - pitchCos * yawSin,
                  pitchSin * rollSin * yawSin + pitchCos * yawCos,
                  pitchSin * rollCos);
}

Vec3f Angles::ToAtVector()
{
    float rollSin  =  (float)sin(roll);
    float rollCos  =  (float)cos(roll);
    float yawSin   =  (float)sin(yaw);
    float yawCos   =  (float)cos(yaw);
    float pitchSin = -(float)cos(pitch);
    float pitchCos =  (float)sin(pitch);

    return Vec3f (pitchCos * rollSin * yawCos + pitchSin * yawSin,
                  pitchCos * rollSin * yawSin - pitchSin * yawCos,
                  pitchCos * rollCos);
}

/***************
 * Operators   *
 ***************/

float Angles::operator [](int x) const
{
    if(x == 0)
        return pitch;
    else if(x == 1)
        return yaw;
    else if(x == 2)
        return roll;
    else
        return 0.0f;
}

Angles Angles::operator +(const Angles& rhs) const
{
    return Angles(pitch + rhs.pitch, yaw + rhs.yaw, roll + rhs.roll);
}

float Angles::operator *(const Angles& rhs) const
{
    return pitch * rhs.pitch + yaw * rhs.yaw + roll * rhs.roll;
}

Angles Angles::operator *(float factor) const
{
    return Angles(pitch * factor, yaw * factor, roll * factor);
}

Angles Angles::operator -(const Angles& rhs) const
{
    return Angles(pitch - rhs.pitch, yaw - rhs.yaw, roll - rhs.roll);
}

Angles Angles::operator /(float factor) const
{
    return Angles(pitch / factor, yaw / factor, roll / factor);
}
