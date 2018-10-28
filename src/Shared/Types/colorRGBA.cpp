#include "colorRGBA.hpp"

using namespace OpenGMP;

const ColorRGBA ColorRGBA::White = ColorRGBA(255, 255, 255, 255);
const ColorRGBA ColorRGBA::Black = ColorRGBA(0, 0, 0, 255);
const ColorRGBA ColorRGBA::Red = ColorRGBA(255, 0, 0, 255);
const ColorRGBA ColorRGBA::Green = ColorRGBA(0, 255, 0, 255);
const ColorRGBA ColorRGBA::Blue = ColorRGBA(0, 0, 255, 255);
const ColorRGBA ColorRGBA::Grey = ColorRGBA(155, 155, 155, 255);
const ColorRGBA ColorRGBA::Yellow = ColorRGBA(255, 255, 0, 255);
const ColorRGBA ColorRGBA::Orange = ColorRGBA(255, 165, 0, 255);

ColorRGBA::ColorRGBA(const unsigned char r, const unsigned char g, const unsigned char b)
{
    ColorRGBA(r, g, b, 255);
}

ColorRGBA::ColorRGBA(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
    : m_r(r)
    , m_g(g)
    , m_b(b)
    , m_a(a)
{
}

void ColorRGBA::set(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

unsigned char ColorRGBA::r() const
{
    return m_r;
}

unsigned char ColorRGBA::g() const
{
    return m_g;
}

unsigned char ColorRGBA::b() const
{
    return m_b;
}

unsigned char ColorRGBA::a() const
{
    return m_a;
}
