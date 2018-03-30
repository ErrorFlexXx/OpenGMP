#pragma once

#include "../xcall.h"
#include "zVEC3.hpp"
#include "zVEC4.hpp"
#include "zMAT3.hpp"
#include "zSTRING.hpp"

class zMAT4
{
public:
    //zVEC4 components[4]; //Estimation
    float matrix[4 * 4];

    zMAT4(float arg)
    {
        XCALL(0x00514C10);
    }

    zMAT4(const zVEC4 &vec1, const zVEC4 &vec2, const zVEC4 &vec3, const zVEC4 &vec4)
    {
        XCALL(0x00514B90);
    }

    zMAT4(const zMAT4 &mat)
    {
        XCALL(0x00487C90);
    }

    static zMAT4 *GetIdentity()
    {
        return (zMAT4*)((unsigned char)(0x008D45E8));
    }

    zVEC3 GetTranslation() const
    {
        XCALL(0x00408EE0);
    }

    zVEC3 GetAtVector() const
    {
        XCALL(0x00431D20);
    }

    zMAT4 & SetTranslation(const zVEC3 &vec)
    {
        XCALL(0x00487C50);
    }

    void GetTranslation(zVEC3 &vec) const
    {
        XCALL(0x00487C70);
    }

    zVEC3 GetUpVector() const
    {
        XCALL(0x00490DD0);
    }

    zVEC3 GetRightVector(void) const
    {
        XCALL(0x00490DF0);
    }

    void SetUpVector(const zVEC3 &vec)
    {
        XCALL(0x004B9D90);
    }

    void SetRightVector(const zVEC3 &vec)
    {
        XCALL(0x004B9DB0);
    }

    zMAT4 Transpose() const
    {
        XCALL(0x00515080);
    }

    zMAT4 TransposeLinTrafo() const
    {
        XCALL(0x00515180);
    }

    zMAT4 InverseLinTrafo() const
    {
        XCALL(0x00515340);
    }

    zMAT4 Inverse() const
    {
        XCALL(0x00515500);
    }

    zMAT4 & Apply(float(__cdecl*function)(float))
    {
        XCALL(0x00515990);
    }

    int IsUpper3x3Orthonormal() const
    {
        XCALL(0x00515A50);
    }

    zSTRING GetDescriptionRot() const
    {
        XCALL(0x00515CA0);
    }

    zSTRING GetDescriptionPos() const
    {
        XCALL(0x00515EE0);
    }

    void SetByDescriptionRot(zSTRING &description)
    {
        XCALL(0x005160E0);
    }

    void SetByDescriptionPos(zSTRING &description)
    {
        XCALL(0x00516240);
    }

    zVEC3 GetEulerAngles() const
    {
        XCALL(0x00516390);
    }

    void SetByEulerAngles(zVEC3 vec)
    {
        XCALL(0x005163D0);
    }

    zVEC3 ExtractScaling() const
    {
        XCALL(0x00517170);
    }

    zMAT3 ExtractRotation()
    {
        XCALL(0x005171F0);
    }

    void MakeOrthonormal()
    {
        XCALL(0x00517330);
    }

    void PostRotateX(float rotX)
    {
        XCALL(0x00517730);
    }

    void PostRotateY(float rotY)
    {
        XCALL(0x00517780);
    }

    void PostRotateZ(float rotZ)
    {
        XCALL(0x005177D0);
    }

    void PostScale(const zVEC3 &scaleVec)
    {
        XCALL(0x00517820);
    }

    void PreScale(const zVEC3 &preScaleVec)
    {
        XCALL(0x00517840);
    }

    zVEC3 Rotate(const zVEC3 &rotVec) const
    {
        XCALL(0x00549290);
    }

    zMAT4 & Translate(const zVEC3 &translateVec)
    {
        XCALL(0x0054DE60);
    }

    void SetAtVector(const  zVEC3 &setVector)
    {
        XCALL(0x0056B960);
    }

    zVEC4 operator[](int index) const
    {
        XCALL(0x004BAED0);
    }

    zMAT4 & operator=(zMAT3 &rhs)
    {
        XCALL(0x00514C80);
    }

    zMAT4 & operator=(const zMAT4 &rhs)
    {
        XCALL(0x00514D80);
    }

    zMAT4 & operator+=(const zMAT4 &rhs)
    {
        XCALL(0x00514E00);
    }

    zMAT4 & operator-=(const zMAT4 &rhs)
    {
        XCALL(0x00514EA0);
    }

    zMAT4 & operator*=(float rhs)
    {
        XCALL(0x00514F40);
    }

    zMAT4 & operator/=(float rhs)
    {
        XCALL(0x00514FF0);
    }
};

zMAT4 __cdecl Alg_Translation3D(const zVEC3 &vec);