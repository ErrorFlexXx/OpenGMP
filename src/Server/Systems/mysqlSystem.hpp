#pragma once

namespace cpgf
{
    struct GMetaVariadicParam;
}

namespace OpenGMP
{
    namespace Systems
    {
        class MysqlSystem
        {
        public:
            MysqlSystem();
            void TestFunctionVariadic(cpgf::GMetaVariadicParam *params);
        };
    }
}
