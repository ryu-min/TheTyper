#include "MainWindow.h"
#include "EnterMenu.h"

#include <QDebug>

typer::gui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow( parent )
{
    setEnterMenu();
}

void typer::gui::MainWindow::setEnterMenu()
{
    EnterMenu * enterMenu = new EnterMenu;
    setCentralWidget(  enterMenu );

    connect( enterMenu, &EnterMenu::start, [this](){
        TyperWidget * typerWidget = new TyperWidget;
        setCentralWidget( typerWidget );
        connect( typerWidget, &TyperWidget::exit,
                 this, &MainWindow::setEnterMenu);
    });

    connect( enterMenu, &EnterMenu::settings, [this](){
        SettingsWidget * settingsWidget = new SettingsWidget;
        setCentralWidget( settingsWidget );
        connect( settingsWidget, &SettingsWidget::exit,
                 this, &MainWindow::setEnterMenu);
    });

//    connect( enterMenu, &EnterMenu::start, [this](){
//        TyperWidget * typerWidget = new TyperWidget;
//        setCentralWidget( typerWidget );
//    });
}
