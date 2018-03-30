#include "zMAT3.hpp"

zMAT3 operator-(const zMAT3 &arg)
{
    XCALL(0x00513E10);
}

zMAT3 operator+(const zMAT3 &arg1, const zMAT3 &arg2)
{
    XCALL(0x00513EC0);
}

zMAT3 operator-(const zMAT3 &arg1, const zMAT3 &arg2)
{
    XCALL(0x00513F70);
}

zMAT3 operator*(const zMAT3 &arg1, const  zMAT3 &arg2)
{
    XCALL(0x00514020);
}

zMAT3 operator*(const zMAT3 &matrix, float unknown)
{
    XCALL(0x00514160);
}

zMAT3 operator*(float unknown, const zMAT3 &matrix)
{
    XCALL(0x00514220);
}

zMAT3 operator/(const zMAT3 &arg1, float unknown)
{
    XCALL(0x005142E0);
}

int operator==(const zMAT3 &arg1, const zMAT3 &arg2)
{
    XCALL(0x00514390);
}

zMAT3 operator!=(const zMAT3 &arg1, const zMAT3 &arg2)
{
    XCALL(0x00514420);
}
