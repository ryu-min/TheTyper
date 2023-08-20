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

            QVariant getGeneralSetting(const QString & valueKey,
                                       const QVariant & defaultValue = QVariant());

            void setGUISetting(const QString & valueKey,
                               const QVariant & value);

            QVariant getGUISetting(const QString & valueKey,
                                   const QVariant & defaultValue = QVariant());
        }
    }
}
