#include "gui/MainWindow.h"
#include "gui/auth/RegistrationDialog.h"
#include "gui/auth/AuthentificationDialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    typer::gui::MainWindow w;
    w.show();
    typer::gui::RegistrationDialog rd;
    rd.show();

    QObject::connect(&rd, &typer::gui::RegistrationDialog::canceled, []() {
        qDebug() << "canceled";
    });
    QObject::connect(&rd, &typer::gui::RegistrationDialog::accepted, []( const typer::gui::RegistrationDialog::RegistrationInfo & info ) {
        qDebug() << "accepted";
        qDebug() << "user name" << info.userName;
        qDebug() << "password" << info.password;
        qDebug() << "confirmed password" << info.confirmedPassword;
    });

    typer::gui::AuthentificationDialog ad;
    ad.show();

    QObject::connect(&ad, &typer::gui::AuthentificationDialog::canceled, []() {
        qDebug() << "canceled";
    });
    QObject::connect(&ad, &typer::gui::AuthentificationDialog::accepted,
                     []( const typer::gui::AuthentificationDialog::AuthentificationInfo & info ) {
        qDebug() << "accepted";
        qDebug() << "user name" << info.userName;
        qDebug() << "password" << info.password;
    });


    w.resize(800, 500);
    return a.exec();
}
