#pragma once

#define NULL_LIMIT          0.0000001f
#define GOTHIC_POS_LIMIT    838860.8f

class Vec3f
{
public:
    Vec3f();
    Vec3f(float data[]);
    Vec3f(float x, float y, float z);
    Vec3f(const Vec3f& vec);

    float m_x;
    float m_y;
    float m_z;

    /* Methods */
    void reset();
    void set(float x, float y, float z);
    float getLength();
    Vec3f normalise();
    float getDistance(Vec3f& value);
    float getDistancePlanar(Vec3f& value);
    Vec3f cross(Vec3f& value);
    bool isNull();
    void correctPositionPart(float& correct, float toCorrect);
    Vec3f clampToWorldLimits();
    Vec3f correctDirection();

    /* Operators */
    float operator[] (int x);
    Vec3f operator+ (const Vec3f& rhs);
    Vec3f operator- (const Vec3f& rhs);
    float operator* (const Vec3f& rhs);
    Vec3f operator* (const float factor);
    Vec3f operator/ (const float factor);
    bool operator== (const Vec3f& rhs);
    bool operator!= (const Vec3f& rhs);
    bool operator== (const float b);
    bool operator!= (const float b);
};
