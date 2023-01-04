#include "MainWindow.h"

#include "EnterMenu.h"
#include "SettingsWidget.h"
#include "TyperWidget.h"

#include "auth/RegistrationWidget.h"
#include "auth/AuthentificationWidget.h"

#include <QPushButton>

typer::gui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow( parent )
{
    setEnterMenu();
}

void typer::gui::MainWindow::setEnterMenu()
{
    EnterMenu * enterMenu = new EnterMenu;
    setCentralWidget(  enterMenu );

    connect( enterMenu, &EnterMenu::start, this, [this](){
        TyperWidget * typerWidget = new TyperWidget;
        setCentralWidget( typerWidget );
        connect( typerWidget, &TyperWidget::exit,
                 this, &MainWindow::setEnterMenu);
    });

    connect( enterMenu, &EnterMenu::settings, this, [this](){
        SettingsWidget * settingsWidget = new SettingsWidget;
        setCentralWidget( settingsWidget );
        connect( settingsWidget, &SettingsWidget::exit,
                 this, &MainWindow::setEnterMenu);
    });

    connect( enterMenu, &EnterMenu::auth, this, [this](){
        AuthentificationWidget * authWidget = new AuthentificationWidget;
        setCentralWidget( authWidget );
        connect( authWidget, &AuthentificationWidget::accepted,
                 this, &MainWindow::setEnterMenu);
        connect( authWidget, &AuthentificationWidget::canceled,
                 this, &MainWindow::setEnterMenu);
    });

    connect( enterMenu, &EnterMenu::registration, this, [this](){
        RegistrationWidget * registrationWidget = new RegistrationWidget;
        setCentralWidget( registrationWidget );
        connect( registrationWidget, &RegistrationWidget::accepted,
                 this, &MainWindow::setEnterMenu);
        connect( registrationWidget, &RegistrationWidget::canceled,
                 this, &MainWindow::setEnterMenu);
    });
}
