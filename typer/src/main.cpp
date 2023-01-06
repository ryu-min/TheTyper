#include "gui/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "hello";

    typer::gui::MainWindow w;
    w.resize(800, 500);

    w.show();
    return a.exec();
}
