#include "TyperSettings.h"

#include "SettingsFile.h"

static typer::common::settings::SettingsFile generalSettingsFile("general.txt");
static typer::common::settings::SettingsFile testSettingsFile("test.txt");


void typer::common::settings::setGeneralSetting(const QString &valueKey, const QVariant &value)
{
    generalSettingsFile.setValue(valueKey, value);
}

QVariant typer::common::settings::getGeneralSetting(const QString &valueKey)
{
    return generalSettingsFile.getValue(valueKey);
}

void typer::common::settings::setTestSetting(const QString &valueKey, const QVariant &value)
{
    testSettingsFile.setValue(valueKey, value);
}

QVariant typer::common::settings::getTestSetting(const QString &valueKey)
{
    return testSettingsFile.getValue(valueKey);
}
