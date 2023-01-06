#include "MainWindow.h"

#include "EnterMenu.h"
#include "SettingsWidget.h"
#include "TyperWidget.h"

#include "../common/Network.h"

#include "auth/RegistrationWidget.h"
#include "auth/AuthentificationWidget.h"

#include <QApplication>
#include <QPushButton>
#include <QMessageBox>


typer::gui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow( parent )
{
    openEnterMenu();
}

void typer::gui::MainWindow::openEnterMenu()
{
    EnterMenu * enterMenu = new EnterMenu;
    setCentralWidget( enterMenu );

    connect( enterMenu, &EnterMenu::start, this, [this](){
        TyperWidget * typerWidget = new TyperWidget;
        setCentralWidget( typerWidget );
        connect( typerWidget, &TyperWidget::exit,
                 this, &MainWindow::openEnterMenu);
    });

    connect( enterMenu, &EnterMenu::settings, this, [this](){
        SettingsWidget * settingsWidget = new SettingsWidget;
        setCentralWidget( settingsWidget );
        connect( settingsWidget, &SettingsWidget::exit,
                 this, &MainWindow::openEnterMenu);
    });

    connect( enterMenu, &EnterMenu::auth, this, [this](){
        AuthentificationWidget * authWidget = new AuthentificationWidget;
        setCentralWidget( authWidget );
        connect( authWidget, &AuthentificationWidget::accepted,
                 this, [this](const typer::common::AuthentificationInfo & info) {
            common::JwtToken token = common::authUser( info );
            qDebug() << "recieve tokent" << token;
            if ( token.isEmpty() ) {
                QMessageBox::warning(this, "Authentification error", "some error");
            }
            else {
                QMessageBox::information(this, "Success", "Success");
                openEnterMenu();
            }

        });
        connect( authWidget, &AuthentificationWidget::canceled,
                 this, &MainWindow::openEnterMenu);
    });

    connect( enterMenu, &EnterMenu::registration, this, [this](){
        RegistrationWidget * registrationWidget = new RegistrationWidget;
        setCentralWidget( registrationWidget );
        connect( registrationWidget, &RegistrationWidget::accepted,
                 [this](const typer::common::RegistrationInfo & info)
        {
            common::JwtToken token = common::registerUser( info );
            qDebug() << "recieve tokent" << token;
            if ( token.isEmpty() ) {
                QMessageBox::warning(this, "Registration error", "some error");
            }
            else {
                QMessageBox::information(this, "Success", "Success");
                openEnterMenu();
            }
        });
        connect( registrationWidget, &RegistrationWidget::canceled,
                 this, &MainWindow::openEnterMenu);
    });
}
