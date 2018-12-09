#include "jsonFile.hpp"
#include <json/json.hpp>
#include <ZenLib/utils/logger.h>
#include <QStandardPaths>
#include <QFile>
#include <QString>

using namespace std;
using namespace OpenGMP;
using namespace nlohmann;

JsonFile::JsonFile(const QString &filename)
    : filename(filename)
    , configDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
{}

JsonFile::~JsonFile()
{
    Save();
}

bool JsonFile::Save() const
{
    QString filepath = configDir.absoluteFilePath(filename);
    if(!configDir.exists())
        configDir.mkpath(".");
    QFile file(filepath);
    if(!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        LogError() << "Cannot write to file: " << filepath.toStdString();
        return false;
    }
    string jsonOutput = j.dump(4);
    file.write(jsonOutput.c_str(), jsonOutput.length());
    file.close();
    return true;
}

bool JsonFile::Load()
{
    QString filepath = configDir.absoluteFilePath(filename);
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly))
    {
        LogInfo() << "Can't read file: " << filepath.toStdString();
        return false;
    }
    QByteArray jsonData = file.readAll();
    j = json::parse(jsonData.toStdString());
    file.close();
    return true;
}

void JsonFile::Clear()
{
    j.clear();
}

void JsonFile::WriteString(const std::string &key, const std::string &value)
{
    j[key] = value;
}

void JsonFile::WriteInt(const std::string &key, const int value)
{
    j[key] = value;
}

void JsonFile::WriteDouble(const std::string &key, const double value)
{
    j[key] = value;
}

void JsonFile::WriteBool(const std::string &key, const bool value)
{
    j[key] = value;
}

bool JsonFile::ReadString(const std::string &key, std::string &value)
{
    try
    {
        value = j[key].get<string>();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool JsonFile::ReadInt(const std::string &key, int &value)
{
    try
    {
        value = j[key].get<int>();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool JsonFile::ReadDouble(const std::string &key, double &value)
{
    try
    {
        value = j[key].get<double>();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool JsonFile::ReadBool(const std::string &key, bool &value)
{
    try
    {
        value = j[key].get<bool>();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

json JsonFile::ReadJson() const
{
    return j;
}

void JsonFile::WriteJson(json &j)
{
    this->j.clear();
    this->j = j;
}
