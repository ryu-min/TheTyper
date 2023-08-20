#pragma once

#include <QList>

namespace typer
{
    namespace common
    {
        struct TypeResult
        {
            int wpmSpeed;
            int accuracy;
        };

        using TypeResults = QList<TypeResult>;
    }
}
