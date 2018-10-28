#pragma once

namespace OpenGMP
{
    class ForbiddenException
    {
    public:
        ForbiddenException(const char* pStr = "Forbidden: ") : m_message(pStr) {}
        const char* What() const {return m_message;}

    private:
        const char* m_message;
    };
}
