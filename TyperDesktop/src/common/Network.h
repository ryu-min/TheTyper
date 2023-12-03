#pragma once

#include "UserInfo.h"

#include <QString>
#include <stdexcept>

#include "result/result.h"

namespace typer
{
    namespace common
    {
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

        using WordsRequestResult = Result<QString, WordsRequestError>;
        using WordsType = QString;
        using WordsTypes = QStringList;

        using WordsTypesRequestResult = Result<WordsTypes, WordsTypesRequestError>;

        WordsRequestResult requestWords( const WordsType & wordsType );
        WordsTypesRequestResult requestWordTypes();

    }
}
