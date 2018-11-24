#pragma once

#include <string>
#include <vector>
#include <json/json.hpp>

namespace OpenGMP
{
    /**
     * @brief The Server class
     *   represents all data to connect to a server.
     */
    class Server
    {
    public:
        /**
         * @brief ToJson parse this object to a json string.
         * @return a std::string json string.
         */
        inline std::string ToJson() const
        {
            nlohmann::json j = {
                {"hostname", hostname},
                {"port", port},
                {"pubKey", PublicKeyToHexString()},
                {"password", password}
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
            port = j["port"].get<int>(); //Required may not fail
            try { PublicKeyFromHexString(j["pubKey"].get<std::string>()); } catch(...) { publicKey.clear(); } //May fail
            try { password = j["password"].get<std::string>(); } catch(...) { password.clear(); } //May fail
        }

        /**
         * @brief ToString creates a string representation of this object.
         * @return std::string representation of this object.
         */
        inline std::string ToString() const
        {
            std::string output;
            output.append(hostname).append(":").append(std::to_string(port)).append(
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
            for(const char &c : publicKey)
            {
                char part[3];
                sprintf(part, "%02X", c);
                part[2] = 0;
                pubKeyString.append(part, 2);
            }
            return pubKeyString;
        }

        std::string servername;         //!< The name of the server.
        std::string hostname;           //!< Hostname of the server.
        unsigned short port;            //!< Port to connect to.
        std::vector<char> publicKey;    //!< Public encryption key.
        std::string password;           //!< RakNet password, if used.
    };
}
