#pragma once

namespace cpgf
{
    struct GMetaVariadicParam;
}

namespace OpenGMP
{
    namespace Systems
    {
        class MySqlSystem
        {
        public:
            MySqlSystem();
            void TestFunctionVariadic(cpgf::GMetaVariadicParam *params);
        };
    }
}
