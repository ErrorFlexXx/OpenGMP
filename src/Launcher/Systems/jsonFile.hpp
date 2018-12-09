#pragma once

#include <QDir>
#include <json/json.hpp>
#include <string>

namespace OpenGMP
{
    /**
     * @brief The JsonFile class storage of data parsed in json.
     */
    class JsonFile
    {
    public:
        /**
         * @brief JsonFile creates a configuration object.
         * @param filename to store the config.
         */
        JsonFile(const QString &filename);

        /**
         * @brief ~JsonFile
         *   Deallocates ressources. Saves all values to file.
         */
        ~JsonFile();

        /**
         * @brief Save saves all json values to file.
         * @return true, if file could be written, false otherwise.
         */
        bool Save() const;

        /**
         * @brief Load reloads all contents from json file.
         * @return true, if file could be parsed successfully, false otherwise.
         */
        bool Load();

        /**
         * @brief Clear clears the whole json memory.
         */
        void Clear();

        /**
         * @brief WriteString stores a string into a json object under a specified key.
         * @param key to store the value in.
         * @param value to be written.
         */
        void WriteString(const std::string &key, const std::string &value);

        /**
         * @brief WriteInt stores an int into a json object under a specified key.
         * @param key to store the value in.
         * @param value to be written.
         */
        void WriteInt(const std::string &key, const int value);

        /**
         * @brief WriteDouble stores a double into a json object under a specified key.
         * @param key to store the value in.
         * @param value to be written.
         */
        void WriteDouble(const std::string &key, const double value);

        /**
         * @brief WriteBool stores a bool into a json object under specified key.
         * @param key to store the value in.
         * @param value to be written.
         */
        void WriteBool(const std::string &key, const bool value);

        /**
         * @brief ReadString reads a string from the json file.
         * @param key of the value, to get.
         * @param value to read the value in.
         * @return true, if successfully read the value, false otherwise.
         */
        bool ReadString(const std::string &key, std::string &value);

        /**
         * @brief ReadInt reads an int from the json file.
         * @param key of the value, to get.
         * @param value to read the value in.
         * @return true, if successfully read the value, false otherwise.
         */
        bool ReadInt(const std::string &key, int &value);

        /**
         * @brief ReadDouble reads a double from the json file.
         * @param key of the value, to get.
         * @param value to read the value in.
         * @return true, if successfully read the value, false otherwise.
         */
        bool ReadDouble(const std::string &key, double &value);

        /**
         * @brief ReadBool reads a bool from the json file.
         * @param key of the value, to get.
         * @param value to read the value in.
         * @return true, if successfully read the value, false otherwise.
         */
        bool ReadBool(const std::string &key, bool &value);

        /**
         * @brief ReadJson reads a json object from file.
         * @return the json object.
         */
        nlohmann::json ReadJson() const;

        /**
         * @brief WriteJson writes a json object to file.
         * @param j the json object.
         */
        void WriteJson(nlohmann::json &j);

        const QString filename; //!< File, which is used as storage.
        const QDir configDir;   //!< Directory, where the file is stored.
        nlohmann::json j;       //!< Json object.
    };
}
