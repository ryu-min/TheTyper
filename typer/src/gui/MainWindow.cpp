#include "MainWindow.h"

#include "EnterMenu.h"
#include "SettingsWidget.h"
#include "TyperWidget.h"

#include "../common/Network.h"

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
    auto wordTypes = common::requestWordTypes().unwrapOr(common::WordsTypes());
    EnterMenu * enterMenu = new EnterMenu(wordTypes, this);
    setCentralWidget( enterMenu );
    connect( enterMenu, &EnterMenu::start, this, &MainWindow::showTyperWidget );
    connect( enterMenu, &EnterMenu::settings, this, &MainWindow::showSettingsWidget );
}

void typer::gui::MainWindow::showTyperWidget(const QString &wordType)
{
    TyperWidget * typerWidget = new TyperWidget(wordType, this);
    setCentralWidget( typerWidget );
    connect( typerWidget, &TyperWidget::exit, this, &MainWindow::showEnterWidget);
}

void typer::gui::MainWindow::showSettingsWidget()
{
    SettingsWidget * settingsWidget = new SettingsWidget(this);
    setCentralWidget( settingsWidget );
    connect( settingsWidget, &SettingsWidget::exit, this, &MainWindow::showEnterWidget);
}
