#include "Network.h"
#include "WaitCoursor.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace
{

QString getWordServiceUrlString()
{
    return "http://127.0.0.1:8080";
}


QString getAuthServiceUrlString() {
    return "http://127.0.0.1:8080";
}

}

typer::common::AuthResult
typer::common::authUser(const AuthentificationInfo &info)
{
    WaitCoursor wc;
    Q_UNUSED(wc);

    const QString ecripterPass = encriptString( info.password );
    const QString requestString = QString("%1/auth?user_name='%2'&user_password='%3")
            .arg(getAuthServiceUrlString(), info.userName, ecripterPass);

    JwtToken token;

    QNetworkAccessManager manager;
    bool requestFinished = false;
    QObject::connect(&manager, &QNetworkAccessManager::finished, &manager,
                     [&token, &requestFinished](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError ) {
            token = reply->readAll();
            if ( reply->hasRawHeader("jwt") ) {
                qDebug() << "has header";
                token = reply->rawHeader("jwt");
            }
            else
            {
                qDebug() << "has not jwt token";
            }
        }
        else {
            qDebug() << "recieve error" << reply->error();
        }
        reply->deleteLater();
        requestFinished = true;
    });

    manager.get( QNetworkRequest(requestString) );
    while ( !requestFinished ) qApp->processEvents();

    return Ok(token);
}

typer::common::JwtToken
typer::common::registerUser(const RegistrationInfo &info)
{
    WaitCoursor wc;
    Q_UNUSED(wc);

    const QString ecripterPass = encriptString( info.password );
    const QString requestString = QString("%1/register?user_name='%2'&user_password='%3")
            .arg(getAuthServiceUrlString(), info.userName, ecripterPass);

    JwtToken token;

    QNetworkAccessManager manager;
    bool requestFinished = false;
    bool registered      = false;

    QObject::connect(&manager, &QNetworkAccessManager::finished, &manager,
                     [&token, &requestFinished, &registered](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError ) {
            registered = true;
        }
        else {
            qDebug() << "recieve error" << reply->error();
        }
        reply->deleteLater();
        requestFinished = true;
    });

    manager.get( QNetworkRequest(requestString) );
    while ( !requestFinished ) qApp->processEvents();

    if ( registered ) {
        // enctipt twice, shoul i care ?
        token = authUser( AuthentificationInfo {
                              info.userName,
                              info.password
                          }).unwrapOr(JwtToken(""));
    }

    return token;
}

bool typer::common::checkToken(JwtToken token)
{
    const QString requestString = QString("%1/check_token").arg(getAuthServiceUrlString());

    QNetworkAccessManager manager;
    bool requestFinished = false;
    bool success = false;

    QObject::connect(&manager, &QNetworkAccessManager::finished, &manager,
                     [&requestFinished, &success](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError ) {
            success = true;
        }
        qDebug() << reply->readAll();
        reply->deleteLater();
        requestFinished = true;
    });

    QNetworkRequest request( requestString );
    request.setRawHeader("jwt_token", token.toUtf8());

    manager.get( request );
    while ( !requestFinished ) qApp->processEvents();

    return success;
}

typer::common::WordsRequestResult typer::common::requestWords(const WordsType &wordsType)
{
    QString stringUrl = getWordServiceUrlString()  + "/words/" + wordsType;
    QNetworkRequest textRequest( stringUrl);
    QString textToType;

    QNetworkAccessManager manager;
    bool requestFinished = false;
    bool result = false;
    QObject::connect(&manager, &QNetworkAccessManager::finished,
            [&textToType, &requestFinished, &result](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError )
        {
            textToType = QString(reply->readAll());
            result = true;
        }
        requestFinished = true;
    });
    manager.get(textRequest);
    while ( !requestFinished ) qApp->processEvents();
    if ( result )
    {
        return Ok(textToType);
    }
    else
    {
        /// @todo another error handling
        return Err( WordsRequestError::CONNECTION_ERROR );
    }
}

typer::common::WordsTypesRequestResult typer::common::requestWordTypes()
{
    QString stringUrl = getWordServiceUrlString()  + "/supported";
    QNetworkRequest textRequest( stringUrl);
    QString wordTypesRaw;

    QNetworkAccessManager manager;
    bool requestFinished = false;
    bool result = false;
    QObject::connect(&manager, &QNetworkAccessManager::finished,
            [&wordTypesRaw, &requestFinished, &result](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError )
        {
            wordTypesRaw = QString(reply->readAll());
            result = true;
        }
        requestFinished = true;
    });
    manager.get(textRequest);
    while ( !requestFinished ) qApp->processEvents();
    if ( result )
    {
        return Ok(wordTypesRaw.split(" "));
    }
    else
    {
        /// @todo another error handling
        return Err( WordsTypesRequestError::CONNECTION_ERROR );
    }
}
