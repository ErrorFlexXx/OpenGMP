#pragma once

#include <string>

//Forward declaration:
namespace httplib
{
    class Client;
}

namespace OpenGMP
{
    class GameClient;
    class Server;

    /**
     * @brief WebStatusSystem
     *   System to get informations from the gameserver.
     *   Used in first instance, to get connect data informations.
     */
    class WebStatusSystem
    {
    public:
        WebStatusSystem(GameClient &gameClient);
        
        /**
         * @brief ~WebStatusSystem frees allocated resources.
         */
        ~WebStatusSystem();

        /**
         * @brief Startup 
         *   Reads connect informations from environment vars and creates required objects.
         * @param OpenGMP::Server server object to store webStatus connect informations in.
         * @return true, if all required informations could be found, false otherwise.
         */
        bool Startup(OpenGMP::Server &server);
        
        /**
         * @brief Shutdown destroys allocated resources.
         */
        void Shutdown();
        
        /**
         * @brief GetConnectData retrieves game server connect informations via http.
         * @param Server the server object to store the informations in.
         * @return true, if the http request succeeded and informations could be read, false otherwise.
         */
        bool GetConnectData(Server &server);

        GameClient &gameClient;           //!< GameClient instance this system acts for.
        httplib::Client *webStatusClient; //!< http client object for web communication.
    };
}