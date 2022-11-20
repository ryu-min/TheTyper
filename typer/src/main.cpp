#include "gui/MainWindow.h"
#include "gui/auth/RegistrationDialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    typer::gui::MainWindow w;
    w.show();
    typer::gui::RegistrationDialog rd;
    rd.show();

    w.resize(800, 500);
   return a.exec();
}
