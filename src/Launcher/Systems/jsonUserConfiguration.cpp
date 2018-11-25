#include "jsonUserConfiguration.hpp"
#include <QStandardPaths>

using namespace OpenGMP;

JsonUserConfiguration::JsonUserConfiguration(const QString &filename)
    : filename(filename)
    , configDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
{}

bool JsonUserConfiguration::WriteString(const std::string &key, const std::string &value)
{
    return false;
}

bool JsonUserConfiguration::WriteInt(const std::string &key, const int value)
{
    return false;
}

bool JsonUserConfiguration::WriteDouble(const std::string &key, const double value)
{
    return false;
}

bool JsonUserConfiguration::ReadString(const std::string &key, std::string &value)
{
    return false;
}

bool JsonUserConfiguration::ReadInt(const std::string &key, int &value)
{
    return false;
}

bool JsonUserConfiguration::ReadDouble(const std::string &key, double &value)
{
    return false;
}
