#pragma once

#include "../xcall.h"

class zVEC3;

class zMAT3
{
public:
    float load[3 * 3]; //Guessed

    zMAT3(const zVEC3 &vec1, const zVEC3 &vec2, const zVEC3 &vec3)
    {
        XCALL(0x00513910);
    }
    
    zMAT3(float arg)
    {
        XCALL(0x00513960);
    }
        
    zMAT3(const zMAT3 &copy)
    {
        XCALL(0x005139B0);
    }

    /* Actions */
    zMAT3 Transpose() const
    {
        XCALL(0x00513BD0);
    }

    zMAT3 Inverse(float *floats)
    {
        XCALL(0x00513C60);
    }
        
    zMAT3 & Apply(float(__cdecl*func)(float))
    {
        XCALL(0x00513DA0);
    }
        
    void MakeOrthonormal()
    {
        XCALL(0x00517510);
    }
        
    void SetUpVector(const zVEC3 &vec)
    {
        XCALL(0x005176F0);
    }
        
    void SetRightVector(const zVEC3 &vec)
    {
        XCALL(0x00517710);
    }

    /* Operators: */
    zMAT3 & operator=(const zMAT3 &matrix)
    {
        XCALL(0x00513A00);
    }
        
    zMAT3 & operator+=(const zMAT3 &matrix)
    {
        XCALL(0x00513A50);
    }
        
    zMAT3 & operator-=(const zMAT3 &matrix)
    {
        XCALL(0x00513AB0);
    }
        
    zMAT3 & operator*=(float arg)
    {
        XCALL(0x00513B10);
    }
        
    zMAT3 & operator/=(float arg)
    {
        XCALL(0x00513B70);
    }        
};

zMAT3 operator-(const zMAT3 &arg);
zMAT3 operator+(const zMAT3 &arg1, const zMAT3 &arg2);
zMAT3 operator-(const zMAT3 &arg1, const zMAT3 &arg2);
zMAT3 operator*(const zMAT3 &arg1, const  zMAT3 &arg2);
zMAT3 operator*(const zMAT3 &matrix, float unknown);
zMAT3 operator*(float unknown, const zMAT3 &matrix);
zMAT3 operator/(const zMAT3 &arg1, float unknown);
int operator==(const zMAT3 &arg1, const zMAT3 &arg2);
zMAT3 operator!=(const zMAT3 &arg1, const zMAT3 &arg2);
