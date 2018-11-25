#pragma once

#include <string>
#include <vector>
#include <json/json.hpp>
#include <Shared/Components/version.hpp>
#include <Shared/Systems/versionSystem.hpp>

namespace OpenGMP
{
    /**
     * @brief The Server class
     *   represents all data to connect to a server.
     */
    class Server
    {
    public:
        Server()
            : version(VersionSystem::version)
        {}

        /**
         * @brief ToJson parse this object to a json string.
         * @return a std::string json string.
         */
        inline std::string ToJson() const
        {
            nlohmann::json j = {
                {"servername", servername},
                {"hostname", hostname},
                {"gamePort", gamePort},
                {"webPort" , webPort},
                {"pubKey"  , PublicKeyToHexString()},
                {"password", password},
                {"version", version.version}
            };
            return j.dump();
        }

        /**
         * @brief FromJson setup this object from a json string.
         * @param json std::string json input
         */
        inline void FromJson(const std::string &json)
        {
            nlohmann::json j = nlohmann::json::parse(json);
            hostname = j["hostname"].get<std::string>(); //Required may not fail
            webPort  = j["webPort"].get<int>(); //Required may not fail
            try { servername = j["servername"].get<std::string>(); } catch(...) { servername.clear(); } //May fail
            try { gamePort = j["gamePort"].get<int>(); } catch(...) { gamePort = 0; } //May fail
            try { PublicKeyFromHexString(j["pubKey"].get<std::string>()); } catch(...) { publicKey.clear(); } //May fail
            try { password = j["password"].get<std::string>(); } catch(...) { password.clear(); } //May fail
            try { version = j["version"].get<uint32_t>(); } catch(...) { } //May fail
        }

        /**
         * @brief ToString creates a string representation of this object.
         * @return std::string representation of this object.
         */
        inline std::string ToString() const
        {
            std::string output;
            output.append(hostname).append(":").append(std::to_string(gamePort)).append(
                        " PW: ").append(password).append(" Key: ").append(PublicKeyToHexString());
            return output;
        }

        /**
         * @brief PublicKeyFromHexString sets the public key from an hex string.
         * @param hexString 2char per byte hex string.
         */
        inline void PublicKeyFromHexString(const std::string &hexString)
        {
            publicKey.clear();
            for(size_t i = 0; i <= hexString.length() - 2; i += 2)
            {
                std::string substr = hexString.substr(i, 2);
                publicKey.push_back(static_cast<char>(strtol(substr.c_str(), nullptr, 16)));
            }
        }

        /**
         * @brief PublicKeyToHexString creates a hex string from the public key attribute.
         * @return an 2 chars per byte hex string.
         */
        inline std::string PublicKeyToHexString() const
        {
            std::string pubKeyString;
            char part[3];   //Buffer to create hex output.
            part[2] = 0;    //Zero terminate

            for(const char &c : publicKey)
            {
                sprintf(part, "%02X", static_cast<unsigned char>(c));
                pubKeyString.append(part);
            }
            return pubKeyString;
        }

        std::string servername;         //!< The name of the server.
        std::string hostname;           //!< Hostname of the server.
        unsigned short gamePort;        //!< Port to connect to RakNet.
        int webPort;                    //!< WebStatus port.
        std::vector<char> publicKey;    //!< Public encryption key.
        std::string password;           //!< RakNet password, if used.
        Version version;                //!< The version of the server.
    };
}
