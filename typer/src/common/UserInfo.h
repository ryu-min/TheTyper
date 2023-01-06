#pragma once

#include <QString>

namespace typer
{
    namespace common
    {
        /**
         * @brief The AuthentificationInfo class
         */
        struct AuthentificationInfo {
            QString userName;
            QString password;
        };

        /**
         * @brief The RegistrationInfo class
         */
        struct RegistrationInfo {
            QString userName;
            QString password;
            QString confirmedPassword;
        };

        inline QString encriptString( QString toEncript ) {
            return toEncript;
        }
    }
}
