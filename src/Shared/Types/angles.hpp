#pragma once

namespace OpenGMP
{
    class Vec3f;

    /**
     * @brief The Angles class holds all three common angles.
     *  holds all three common angles and covers basic calculations.
     */
    class Angles
    {
    public:
        static Angles Null();
        static float Deg2Rad(float degrees);
        static float Rad2Deg(float radians);
        static float ClampTo360(float degrees);
        static float ClampTo2Pi(float radians);
        static float ClampTo180(float degrees);
        static float ClampToPi(float radians);
        static float GetYawFromAtVector(const Vec3f &at);
        static Vec3f GetAtVectorFromYaw(float yaw);
        static Angles FromAtVector(const Vec3f &at);

        /* Constructors and Methods */
        Angles();
        Angles(float data[]);
        Angles(double pitch, double yaw, double roll);
        Angles(float pitch, float yaw, float roll);
        Angles Clamp();
        void Reset();
        void Set(float pitch, float yaw, float roll);
        void SetByAtVector(const Vec3f &at);
        Vec3f ToRightVector();
        Vec3f ToUpVector();
        Vec3f ToAtVector();

        /* Operators */
        float operator[] (int x) const;
        Angles operator+ (const Angles& rhs) const;
        float  operator* (const Angles& rhs) const;
        Angles operator* (float factor) const;
        Angles operator- (const Angles& rhs) const;
        Angles operator/ (float factor) const;

        float pitch;
        float yaw;
        float roll;

        static const float Pi;     //!< The Pi constant.
        static const float TwoPi;  //!< Two Pi constant.
    };
}
