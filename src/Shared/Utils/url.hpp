#pragma once

#include <string>
#include "logger.hpp"

namespace OpenGMP
{
    /**
     * @brief The Url class is a support class to deal with urls.
     */
    class Url
    {
    public:
        /**
         * @brief Url constructs an url object from a full url.
         * @param url string that represents an url.
         */
        inline Url(const std::string &url)
        {
            Set(url); //Extract informations.
        }

        /**
         * @brief Url constructs an url object from components.
         * @param protocol protocol component.
         * @param host host component.
         * @param port port component.
         * @param path paths component.
         */
        inline Url(const std::string &protocol, const std::string &host, int port, const std::string &path)
            : protocol(protocol)
            , host(host)
            , port(port)
            , path(path)
        {}

        /**
         * @brief Set extracts all given informations and stores it in this url obj.
         * @param url the full url.
         */
        inline void Set(const std::string &url)
        {
            size_t it = url.find("//");

            //Protocol
            if(it != std::string::npos) //Protocol found
            {
                it += 2; //Set iterator behind //
                protocol = url.substr(0, it);
            }
            else //No protocol found - no problem.
                it = 0;
            //Host
            size_t hostIt = url.find(":", it);
            if(hostIt != std::string::npos)
            {
                host = url.substr(it, hostIt - it);
                hostIt++; //Set behind :
                size_t portIt = url.find("/", hostIt);
                if(portIt != std::string::npos)
                {
                    port = atoi(url.substr(hostIt, portIt - hostIt).c_str());
                    it = portIt;
                }
                else
                {
                    port = atoi(url.substr(hostIt).c_str());
                    return;
                }
            }
            else //No port in link
            {
                //Set some default port for known protocols
                if(protocol.find("http://") != std::string::npos) port = 80;
                if(protocol.find("https://") != std::string::npos) port = 443;

                hostIt = url.find("/", it);
                if(hostIt != std::string::npos)
                {
                    host = url.substr(it, hostIt - it);
                    it = hostIt;
                }
                else
                {
                    host = url.substr(it);
                    return; //Finished
                }
            }
            path = url.substr(it);
        }

        /**
         * @brief Get assembles a full url with all informations.
         * @return a std::string representing this url.
         */
        inline std::string Get() const
        {
            std::string fullUrl;
            fullUrl.append(protocol);
            fullUrl.append(host);
            if(port != 0)
                fullUrl.append(":").append(std::to_string(port));
            fullUrl.append(path);
            return fullUrl;
        }

        std::string protocol;   //!< The protocol if any.
        std::string host;       //!< The host part.
        int port;               //!< The port (0 if unset)
        std::string path;       //!< The path
    };
}
