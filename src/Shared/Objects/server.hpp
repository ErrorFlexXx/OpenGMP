#pragma once

#include <string>
#include <vector>

namespace OpenGMP
{
    class Server
    {
    public:
        std::string hostname;           //!< Hostname of the server.
        unsigned short port;            //!< Port to connect to.
        std::vector<char> publicKey;    //!< Public encryption key.
    };
}