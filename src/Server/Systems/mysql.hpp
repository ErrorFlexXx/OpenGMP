#pragma once

#include <string>
#include <vector>
#include <mysql/mysql.h>
#include <utils/logger.h>

namespace OpenGMP
{
    /**
     * @brief The Mysql class
     *  Helper class for database tasks exposed to scripts.
     */
    class Mysql
    {
    public:
        Mysql(const std::string &hostname, unsigned int port,
              const std::string &database,
              const std::string &username, const std::string &password);
        ~Mysql();
        bool Connect();
        bool Close();
        bool IsConnected();
        std::string RealEscapeString(const std::string &in);
        std::string FetchRowElement(MYSQL_ROW result, int index);

        MYSQL *handle;
        std::string hostname;
        unsigned int port;
        std::string database;
        std::string username;
        std::string password;
    };
}
