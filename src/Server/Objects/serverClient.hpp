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

            Components::AuthData &GetAuthData();
            void SetAuthData(Components::AuthData authData);
        };
    }
}
