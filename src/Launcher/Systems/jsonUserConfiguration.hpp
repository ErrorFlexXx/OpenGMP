#pragma once

#include <QDir>

namespace OpenGMP
{
    /**
     * @brief The JsonUserConfiguration class storage of configurations for current logged in user.
     */
    class JsonUserConfiguration
    {
    public:
        /**
         * @brief JsonUserConfiguration creates a configuration object.
         * @param filename to store the config.
         */
        JsonUserConfiguration(const QString &filename);

        bool WriteString(const std::string &key, const std::string &value);
        bool WriteInt(const std::string &key, const int value);
        bool WriteDouble(const std::string &key, const double value);
        bool ReadString(const std::string &key, std::string &value);
        bool ReadInt(const std::string &key, int &value);
        bool ReadDouble(const std::string &key, double &value);

        const QString filename; //!< File, which is used as storage.
        const QDir configDir;   //!< Directory, where the file is stored.
    };
}
