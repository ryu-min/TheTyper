#include "SettingsFile.h"

typer::common::settings::SettingsFile::SettingsFile(const QString &fileName,
                                                    const QDir &baseDir,
                                                    QObject *parent)
    : QObject(parent)
    , m_settings(baseDir.absolutePath() + QDir::separator() + fileName, QSettings::IniFormat)
{
    qDebug() << baseDir.absolutePath() + QDir::separator() + fileName;
}

void typer::common::settings::SettingsFile::setValue(const QString &valueKey, const QVariant &value)
{
    m_settings.setValue(valueKey, value);
    m_settings.sync();
}

QVariant typer::common::settings::SettingsFile::getValue(const QString &valueKey)
{
    return m_settings.value(valueKey);
}
