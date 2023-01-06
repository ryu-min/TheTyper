#pragma once

#include <QString>

#include <QCryptographicHash>

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
            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData( toEncript.toUtf8() );
            return hash.result();
        }
    }
}
