#pragma once

#include <Shared/Objects/client.hpp>

namespace OpenGMP
{    
    namespace Objects
    {
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
