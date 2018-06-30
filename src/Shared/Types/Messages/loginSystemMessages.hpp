#pragma once

namespace OpenGMP
{
    namespace Types
    {        
        enum LoginSystemMessages : unsigned char
        {
            LOGIN,
            LOGIN_OK,
            BAD_PASSWORD,
            BANNED,
			LOGOUT,
			REGISTER,
			REGISTER_OK,
        };
    }
}
