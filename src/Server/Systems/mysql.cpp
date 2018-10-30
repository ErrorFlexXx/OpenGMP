#include "mysql.hpp"
#include <cstring>
#include <cstdio>

using namespace std;
using namespace OpenGMP;

Mysql::Mysql(const string &hostname, unsigned int port,
             const string &database,
             const string &username, const string &password)
    : handle(nullptr)
    , hostname(hostname)
    , port(port)
    , database(database)
    , username(username)
    , password(password)
{
}

Mysql::~Mysql()
{
    Close();
}

bool Mysql::Connect()
{
    if(handle)
        Close();
    handle = mysql_init(nullptr);
    if(!handle)
    {
        LogError() << "Out of memory! mysql_init failed!";
        return false;
    }
    if(!mysql_real_connect(handle, hostname.c_str(), username.c_str(), password.c_str(), database.c_str(), port, nullptr, 0))
    {
        LogError() << mysql_error(handle);
        return false;
    }

    if(!handle)
    {
        LogInfo() << "Mysql connect failed Host: " << hostname << " Port: " << port << " Database: " << database;
        return false;
    }
    if(0 != mysql_options(handle, MYSQL_OPT_RECONNECT, (void*)"1"))
    {
        LogWarn() << "Mysql option MYSQL_OPT_RECONNECT cannot be set!";
    }

    return true;
}

bool Mysql::Close()
{
    if(handle)
    {
        mysql_close(handle);
        handle = nullptr;
        return true;
    }

    return false;
}

bool Mysql::IsConnected()
{
    return (0 == mysql_ping(handle));
}

std::string Mysql::RealEscapeString(const string &in)
{
    char escapedString[in.length() * 2 + 1];
    mysql_real_escape_string(handle, escapedString, in.c_str(), in.length());
    return string(escapedString);
}

std::string Mysql::FetchRowElement(MYSQL_ROW row, int index)
{
    if(row[index])
    {
        return std::string(row[index]);
    }
    LogError() << "Invalid index - out of range.";
    return std::string();
}
