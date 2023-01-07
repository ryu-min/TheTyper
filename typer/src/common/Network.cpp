#include "Network.h"
#include "WaitCoursor.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace
{

QString getWordServiceUrlString()
{
    return "http://127.0.0.1:8000";
}


QString getAuthServiceUrlString() {
    return "http://127.0.0.1:8080";
}

}

typer::common::JwtToken
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

    return token;
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
                          });
    }

    return token;
}

bool typer::common::checkToken(JwtToken token)
{
    qDebug() << "send check token" << token;

    const QString requestString = QString("%1/check_token").arg(getAuthServiceUrlString());

    QNetworkAccessManager manager;
    bool requestFinished = false;
    bool success = false;

    QObject::connect(&manager, &QNetworkAccessManager::finished, &manager,
                     [&requestFinished, &success](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError ) {
            qDebug() << "return succus";
            success = true;
        }
        else {
            qDebug() << "return error";
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
