#pragma once

#include <QString>
#include <QVariant>

namespace typer
{
    namespace common
    {
        namespace settings
        {
            void setGeneralSetting(const QString & valueKey,
                                   const QVariant & value);

            QVariant getGeneralSetting(const QString & valueKey);


            void setTestSetting(const QString & valueKey,
                                   const QVariant & value);

            QVariant getTestSetting(const QString & valueKey);


        }
    }
}
