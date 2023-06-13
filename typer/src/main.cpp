#include "gui/MainWindow.h"

#include <QApplication>
#include <QScreen>
#include <QStandardPaths>
#include <QDir>
#include <QSettings>

#include <QDebug>

#include "common/settings/TyperSettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/icons/typer.png"));


    typer::common::settings::setGeneralSetting("value 1", "stored 1");
    qDebug() << "readed from " << typer::common::settings::getGeneralSetting("value 1");


    typer::common::settings::setTestSetting("value 1", "stored 2");
    qDebug() << "readed from " << typer::common::settings::getTestSetting("value 1");



    typer::gui::MainWindow w;
    w.setWindowTitle("The Typer");
    QRect screenRect = QApplication::primaryScreen()->geometry();
    w.resize(screenRect.width() * 0.7, screenRect.height() * 0.5);

    w.show();
    return a.exec();
}
