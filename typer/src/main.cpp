#include "gui/MainWindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/icons/typer.png"));

    typer::gui::MainWindow w;
    w.setWindowTitle("The Typer");
    QRect screenRect = QApplication::primaryScreen()->geometry();
    w.resize(screenRect.width() * 0.7, screenRect.height() * 0.5);

    w.show();
    return a.exec();
}
