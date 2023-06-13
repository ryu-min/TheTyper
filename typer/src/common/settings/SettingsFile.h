#pragma once

#include <QObject>
#include <QStandardPaths>
#include <QSettings>
#include <QDir>

namespace typer
{
    namespace common
    {
        namespace settings
        {
            class SettingsFile : public QObject
            {
                Q_OBJECT

            public:

                static QString getDefaultSettingFolderPath()
                {
                    static QString AppDataDir = QStandardPaths::writableLocation(
                                             QStandardPaths::QStandardPaths::AppLocalDataLocation);
                    return AppDataDir + QDir::separator() + "TheTyper";
                }

            public:

                SettingsFile(const QString & fileName,
                             const QDir & baseDir = QDir(getDefaultSettingFolderPath()),
                             QObject * parent = nullptr);

                QVariant getValue( const QString & valueKey);

            public slots:

                void setValue(const QString & valueKey, const QVariant & value);

            protected:
                QSettings m_settings;
            };
        }
    }
}
