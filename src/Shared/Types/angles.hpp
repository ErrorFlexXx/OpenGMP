#pragma once

namespace OpenGMP
{
    namespace Types
    {
        class Vec3f; //Forward declaration of Vec3f class.

        /**
         * @brief The Angles class holds all three common angles.
         *  holds all three common angles and covers basic calculations.
         */
        class Angles
        {
        public:
            /* Static Methods */
            static Angles Null();
            static float Deg2Rad(float degrees);
            static float Rad2Deg(float radians);
            static float ClampTo360(float degrees);
            static float ClampTo2Pi(float radians);
            static float ClampTo180(float degrees);
            static float ClampToPi(float radians);
            static float getYawFromAtVector(Vec3f at);
            static Angles fromAtVector(Vec3f at);

            /* Constructors and Methods */
            Angles();
            Angles(float data[]);
            Angles(double pitch, double yaw, double roll);
            Angles(float pitch, float yaw, float roll);
            Angles clamp();
            void reset();
            void set(float pitch, float yaw, float roll);
            void setByAtVector(Vec3f at);
            Vec3f toRightVector();
            Vec3f toUpVector();
            Vec3f toAtVector();

            /* Operators */
            //To Do: Mark operators as friend and implement operators as non member functions!
            float operator[] (int x);
            Angles operator+ (const Angles& rhs);
            float operator* (const Angles& rhs);
            Angles operator* (float factor);
            Angles operator- (const Angles& rhs);
            Angles operator/ (float factor);

            float m_pitch;
            float m_yaw;
            float m_roll;

            static const float Pi;     //!< The Pi constant.
            static const float TwoPi;  //!< Two Pi constant.
        };
    }
}
