#pragma once

#include <string>
#include <vector>
#include <mysql/mysql.h>
#include <utils/logger.h>

namespace OpenGMP
{
    namespace Systems
    {
        /**
         * @brief The ScriptMysqlBindHelper class
         *   Temporary class to implement mysql bind struct usage in scripts.
         *   Remove, if cpgf core library is bound to scripts and cpgf.createByteArray can be used.
         *   But we can live with this workaround, too.
         */
        class ScriptMysqlBindHelper
        {
        public:
            ~ScriptMysqlBindHelper();
            void AddString(std::string &value);
            void AddInt(int &value);
            void AddDouble(double &value);
            void ResetBinds();
            char Bind(MYSQL_STMT &stmt);

        private:
            std::vector<MYSQL_BIND> binds;
            std::vector<char*> texts;
            std::vector<unsigned long*> lengths;
        };
    }
}
