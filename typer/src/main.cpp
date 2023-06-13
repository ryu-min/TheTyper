#include "gui/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/typer.png"));
    typer::gui::MainWindow w;

    w.setWindowTitle("The Typer");
    w.show();
    return a.exec();
}
