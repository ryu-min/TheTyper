#include "gui/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    typer::gui::MainWindow w;
    w.show();
    w.resize(800, 500);
    return a.exec();
}
