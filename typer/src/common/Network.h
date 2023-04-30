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

        /// @todo think about combine all this error times
        enum class AuthError {
            CONNECTION_ERROR,
            USER_INFO_ERROR
        };

        enum class WordsRequestError
        {
            CONNECTION_ERROR,
            UNEXPECTED_RESULT
        };

        enum class WordsTypesRequestError
        {
            CONNECTION_ERROR,
            UNEXPECTED_RESULT
        };

        using JwtToken = QString;

        using AuthResult = Result<JwtToken, AuthError>;

        using WordsRequestResult = Result<QString, WordsRequestError>;

        using WordsType = QString;

        using WordsTypes = QStringList;

        using WordsTypesRequestResult = Result<WordsTypes, WordsTypesRequestError>;

        AuthResult authUser( const AuthentificationInfo & info );

        WordsRequestResult requestWords( const WordsType & wordsType );

        WordsTypesRequestResult requestWordTypes();

        JwtToken registerUser( const RegistrationInfo & info );

        bool checkToken(JwtToken token);

    }
}
