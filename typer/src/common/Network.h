#pragma once

#include "UserInfo.h"

#include <QString>
#include <stdexcept>

namespace typer
{
    namespace common
    {
        struct TyperNetworkError : std::runtime_error
        {
            TyperNetworkError( QString errorMessage )
                : std::runtime_error( errorMessage.toStdString() )
            {}
        };

        struct ConnectionError : TyperNetworkError
        {
            ConnectionError( QString errorMessage )
                : TyperNetworkError( errorMessage )
            {}
        };

        struct RegistrationError : TyperNetworkError
        {
            RegistrationError( QString errorMessage )
                : TyperNetworkError( errorMessage )
            {}
        };

        struct AuthError : TyperNetworkError
        {
            AuthError( QString errorMessage )
                : TyperNetworkError( errorMessage )
            {}
        };

        using JwtToken = QString;

        /**
         * @brief authUser
         * @param info
         * @return
         */
        JwtToken authUser( const AuthentificationInfo & info );

        /**
         * @brief registerUser
         * @param info
         * @return
         */
        JwtToken registerUser( const RegistrationInfo & info );

    }
}
