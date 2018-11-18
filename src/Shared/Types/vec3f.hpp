#pragma once

#include <BitStream.h>

#define NULL_LIMIT          0.0000001f
#define GOTHIC_POS_LIMIT    838860.8f

namespace OpenGMP
{
    class Vec3f
    {
    public:
        /**
         * @brief Vec3f constructs a zero initialized vector.
         */
        Vec3f();

        /**
         * @brief Vec3f constructs a vector initialized by an float array.
         * @param data float array with init values.
         */
        Vec3f(float data[]);

        /**
         * @brief Vec3f constructs a vector from three floats.
         * @param x x component.
         * @param y y component.
         * @param z z component.
         */
        Vec3f(float x, float y, float z);

        /**
         * @brief Vec3f Copy constructor for a vector.
         * @param vec vector to copy.
         */
        Vec3f(const Vec3f& vec);

        /**
         * @brief Vec3f constructs a vector from a stream.
         * @param stream to read the vector from.
         */
        Vec3f(RakNet::BitStream &stream);

        /**
         * @brief WriteStream writes the vector to a stream.
         * @param stream the stream, to write the vector to.
         */
        void WriteStream(RakNet::BitStream &stream) const;

        /**
         * @brief ReadStream reads a vector from a stream.
         * @param stream the stream, to read the vector from.
         * @return true, if all components could be read successfully.
         */
        bool ReadStream(RakNet::BitStream &stream);

        float x; //!< The x component of the vector.
        float y; //!< The y component of the vector.
        float z; //!< The z component of the vector.

        /**
         * @brief Reset Resets all vector components to zero.
         */
        void Reset();

        /**
         * @brief Set sets the components of the vector to x, y and z.
         * @param x x component to set.
         * @param y y component to set.
         * @param z z component to set.
         */
        void Set(float x, float y, float z);

        /**
         * @brief GetLength Returns the length of the vector.
         * @return the length of the vector.
         */
        float GetLength() const;

        /**
         * @brief Normalise returns the normalised vector.
         * @return the normalised version of this vector.
         */
        Vec3f Normalise() const;

        /**
         * @brief GetDistance returns the distance between to vectors.
         * @param value the vector to compare with.
         * @return the distance.
         */
        float GetDistance(const Vec3f& value) const;

        /**
         * @brief GetDistancePlanar returns the planar distance between to vectors.
         * @param value the vector to compare with.
         * @return the planar distance.
         */
        float GetDistancePlanar(const Vec3f& value) const;

        /**
         * @brief Cross return a cross product of two vectors.
         * @param value the vector to multiply with.
         * @return the resulting vector.
         */
        Vec3f Cross(const Vec3f& value) const;

        /**
         * @brief IsNull checks if the vector is null (within gothic limits)
         * @return true if null, false otherwise.
         */
        bool IsNull() const;

        /**
         * @brief ClampToWorldLimits clamps a float to gothic world limits.
         * @param correct float to correct
         * @return clamped version of the float.
         */
        static float ClampToWorldLimits(float correct);

        /**
         * @brief ClampToWorldLimits returns a clamped to G world limits vector.
         * @return clamped version of this vector.
         */
        Vec3f ClampToWorldLimits() const;

        /**
         * @brief CorrectDirection returns a normalised vector with z=1 if the vec. was zero.
         * @return a normalised vector with z=1 if vec. was zero.
         */
        Vec3f CorrectDirection() const;

        /***************/
        /** Operators **/
        /***************/

        /**
         * @brief operator [] array operator
         * @param x index to access
         * @return the requested component of the vector or 0.f if out of scope.
         */
        float operator[] (int x) const;

        /**
         * @brief operator + the add operator.
         * @param rhs the vector to add.
         * @return the addition result vector.
         */
        Vec3f operator+ (const Vec3f& rhs) const;

        /**
         * @brief operator - the subtract operator.
         * @param rhs the vector to subtract.
         * @return the subtraction result vector.
         */
        Vec3f operator- (const Vec3f& rhs) const;

        /**
         * @brief operator * the multiply with vector operator.
         * @param rhs the vector to multiply with.
         * @return the multiplication result vector.
         */
        float operator* (const Vec3f& rhs) const;

        /**
         * @brief operator * the multiply with float operator.
         * @param factor the float to multiply all components with.
         * @return the multiplicaton result vector.
         */
        Vec3f operator* (const float factor) const;

        /**
         * @brief operator / the division operator.
         * @param factor the float to divide all components with.
         * @return the division result vector.
         */
        Vec3f operator/ (const float factor) const;

        /**
         * @brief operator == the equal operator.
         * @param rhs the vector to compare with.
         * @return true if equal in gothic limits, false otherwise.
         */
        bool operator== (const Vec3f& rhs) const;

        /**
         * @brief operator != the unequal operator
         * @param rhs the vector to compare with.
         * @return true if not equal in gothic limit, false otherwise.
         */
        bool operator!= (const Vec3f& rhs) const;

        /**
         * @brief operator == the equal length operator.
         * @param b the length to compare with.
         * @return true if the length is equal, false otherwise.
         */
        bool operator== (const float b) const;

        /**
         * @brief operator !=the unqual length operator.
         * @param b the length to compare with.
         * @return true if the length is not equal, false otherwise.
         */
        bool operator!= (const float b) const;
    };
}
