#pragma once

#include <Shared/Objects/client.hpp>

namespace OpenGMP
{    
    namespace Objects
    {
        /**
         * @defgroup scriptObject
         * @brief ScriptObjects Elements exposed to scripts
         */

        /**
         * @brief The ServerClient object
         * @ingroup scriptObject
         */
        class ServerClient : public Client
        {
        public:
            ServerClient();

            //Getter and setter for script interface:
            Components::AuthData &GetAuthData();
            void SetAuthData(Components::AuthData authData);
        };
    }
}
