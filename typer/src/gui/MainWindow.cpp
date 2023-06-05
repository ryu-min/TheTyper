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
    showEnterWidget();
}

void typer::gui::MainWindow::showEnterWidget()
{
    EnterMenu * enterMenu = new EnterMenu(this);
    setCentralWidget( enterMenu );
    connect( enterMenu, &EnterMenu::start, this, &MainWindow::showTyperWidget );
    connect( enterMenu, &EnterMenu::settings, this, &MainWindow::showSettingsWidget );
    connect( enterMenu, &EnterMenu::registration, this, &MainWindow::showRegistrationWidget );
    connect( enterMenu, &EnterMenu::auth, this, &MainWindow::showAuthWidget);
    //enterMenu->setFocus();
}

void typer::gui::MainWindow::showTyperWidget()
{
    TyperWidget * typerWidget = new TyperWidget(this);
    setCentralWidget( typerWidget );
    connect( typerWidget, &TyperWidget::exit, this, &MainWindow::showEnterWidget);
}

void typer::gui::MainWindow::showSettingsWidget()
{
    SettingsWidget * settingsWidget = new SettingsWidget(this);
    setCentralWidget( settingsWidget );
    connect( settingsWidget, &SettingsWidget::exit, this, &MainWindow::showEnterWidget);
}

void typer::gui::MainWindow::showAuthWidget()
{
    AuthentificationWidget * authWidget = new AuthentificationWidget(this);
    setCentralWidget( authWidget );
    connect( authWidget, &AuthentificationWidget::accepted,
             this, [this](const typer::common::AuthentificationInfo & info) {
        common::JwtToken token = common::authUser( info )
                .unwrapOr(common::JwtToken(""));
        qDebug() << "recieve tokent" << token;
        if ( token.isEmpty() ) {
            QMessageBox::warning(this, "Authentification error", "some error");
        }
        else {
            //bool checkToken = common::checkToken(token);
            QMessageBox::information(this, "Success", "Success");
            showEnterWidget();
        }
    });
    connect( authWidget, &AuthentificationWidget::canceled, this, &MainWindow::showEnterWidget);
}

void typer::gui::MainWindow::showRegistrationWidget()
{
    RegistrationWidget * registrationWidget = new RegistrationWidget(this);
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
            showEnterWidget();
        }
    });
    connect( registrationWidget, &RegistrationWidget::canceled,
             this, &MainWindow::showEnterWidget);
}
