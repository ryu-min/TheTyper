#include "TyperSettings.h"

#include "SettingsFile.h"

static typer::common::settings::SettingsFile generalSettingsFile("general.typer");
static typer::common::settings::SettingsFile GUISettingsFile("gui.typer");


void typer::common::settings::setGeneralSetting(const QString &valueKey, const QVariant &value)
{
    generalSettingsFile.setValue(valueKey, value);
}

QVariant typer::common::settings::getGeneralSetting(const QString &valueKey, const QVariant &defaultValue)
{
    return generalSettingsFile.getValue(valueKey, defaultValue);
}

void typer::common::settings::setGUISetting(const QString &valueKey, const QVariant &value)
{
    GUISettingsFile.setValue(valueKey, value);
}

QVariant typer::common::settings::getGUISetting(const QString &valueKey, const QVariant &defaultValue)
{
    return GUISettingsFile.getValue(valueKey, defaultValue);
}
