#include "Network.h"
#include "WaitCoursor.h"

#include "json/json.hpp"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>

using json = nlohmann::json;

namespace
{

QString getWordServiceUrlString()
{
    return "http://31.129.109.221:8080";
}


QString getAuthServiceUrlString() {
    return "http://127.0.0.1:8080";
}

}

typer::common::WordsRequestResult typer::common::requestWords(const WordsType &wordsType)
{
    WaitCoursor wc;
    Q_UNUSED(wc);

    QString stringUrl = getWordServiceUrlString()  + "/words/" + wordsType;
    QNetworkRequest textRequest( stringUrl);
    QString wordsRequestResult;

    QNetworkAccessManager manager;
    bool requestFinished = false;
    bool result = false;
    QObject::connect(&manager, &QNetworkAccessManager::finished,
            [&wordsRequestResult, &requestFinished, &result](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError )
        {
            wordsRequestResult = QString(reply->readAll());
            result = true;
        }
        requestFinished = true;
    });
    manager.get(textRequest);
    while ( !requestFinished ) qApp->processEvents();
    if ( result )
    {
        auto j = json::parse(wordsRequestResult.toStdString());
        if ( j.contains("words") )
        {
            auto wordsString = j["words"].get<std::string>();
            return Ok(QString::fromStdString(wordsString));
        }
        else
        {
            return Err( WordsRequestError::UNEXPECTED_RESULT );
        }
    }
    else
    {
        /// @todo another error handling
        return Err( WordsRequestError::CONNECTION_ERROR );
    }
}

typer::common::WordsTypesRequestResult typer::common::requestWordTypes()
{
    WaitCoursor wc; Q_UNUSED(wc);

    QString stringUrl = getWordServiceUrlString()  + "/supported";
    QNetworkRequest textRequest( stringUrl);
    QString wordTypesRequestResul;

    QNetworkAccessManager manager;
    bool requestFinished = false;
    bool result = false;
    QObject::connect(&manager, &QNetworkAccessManager::finished,
            [&wordTypesRequestResul, &requestFinished, &result](QNetworkReply * reply) {
        if ( reply->error() == QNetworkReply::NoError )
        {
            wordTypesRequestResul = QString(reply->readAll());
            result = true;
        }
        requestFinished = true;
    });
    manager.get(textRequest);
    while ( !requestFinished ) qApp->processEvents();
    if ( result )
    {
        auto j = json::parse(wordTypesRequestResul.toStdString());
        if ( j.contains("types") )
        {
            auto typesString = j["types"].get<std::string>();
            auto typesQString = QString::fromStdString(typesString);
            return Ok(typesQString.split(" "));
        }
        else
        {
            return Err( WordsTypesRequestError::UNEXPECTED_RESULT );
        }
    }

    else
    {
        /// @todo another error handling
        return Err( WordsTypesRequestError::CONNECTION_ERROR );
    }
}
