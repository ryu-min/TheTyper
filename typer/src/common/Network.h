#pragma once

#include "UserInfo.h"

#include <QString>
#include <stdexcept>

#include "result/result.h"

namespace typer
{
    /**
     * move all of it from common to network namespace ?
     */
    namespace common
    {
        enum class AuthError {
            CONNECTION_ERROR,
            USER_INFO_ERROR
        };

        using JwtToken = QString;

        using AuthResult = Result<JwtToken, AuthError>;

        /**
         * @brief authUser
         * @param info
         * @return
         */
        AuthResult authUser( const AuthentificationInfo & info );

        /**
         * @brief registerUser
         * @param info
         * @return
         */
        JwtToken registerUser( const RegistrationInfo & info );

        /**
         * @brief checkToken - test function
         * @param token
         * @return
         */
        bool checkToken(JwtToken token);
    }
}
