#include "MainWindow.h"

#include "EnterMenu.h"
#include "SettingsWidget.h"
#include "TyperWidget.h"

#include "../common/Network.h"
#include "../common/settings/TyperSettings.h"

#include <QApplication>

static const QString WINDOW_SIZE_SETTINGS_KEY   = "window_size";
static const QString WINDOW_POS_SETTINGS_KEY    = "window_pos";

typer::gui::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow( parent )
    , m_wordTypes()
{
    updateWordTypes();
    showEnterWidget();
    restoreWindowSettings();
}

typer::gui::MainWindow::~MainWindow()
{
    storeWindowSettings();
}

void typer::gui::MainWindow::showEnterWidget()
{
    if ( m_wordTypes.isEmpty() ) updateWordTypes();
    EnterMenu * enterMenu = new EnterMenu(m_wordTypes, this);
    setCentralWidget( enterMenu );
    connect( enterMenu, &EnterMenu::start, this, &MainWindow::showTyperWidget );
    connect( enterMenu, &EnterMenu::settings, this, &MainWindow::showSettingsWidget );
}

void typer::gui::MainWindow::showTyperWidget(const QString &wordType, int sTime)
{
    TyperWidget * typerWidget = new TyperWidget(wordType, sTime, this);
    setCentralWidget( typerWidget );
    connect( typerWidget, &TyperWidget::exit, this, &MainWindow::showEnterWidget);
    connect( typerWidget, &TyperWidget::finish, this, [this](int speed) {
       qDebug() << "finish with result " << speed;
       showEnterWidget();
    });
}

void typer::gui::MainWindow::showSettingsWidget()
{
    SettingsWidget * settingsWidget = new SettingsWidget(this);
    setCentralWidget( settingsWidget );
    connect( settingsWidget, &SettingsWidget::exit, this, &MainWindow::showEnterWidget);
}

void typer::gui::MainWindow::updateWordTypes()
{
    m_wordTypes = common::requestWordTypes().unwrapOr(common::WordsTypes());
}

void typer::gui::MainWindow::restoreWindowSettings()
{
    QSize windowSize = common::settings::getGUISetting( WINDOW_SIZE_SETTINGS_KEY,
                                                        QSize(600, 400) )
                       .toSize();
    resize( windowSize );

    QPoint windowPos = common::settings::getGUISetting( WINDOW_POS_SETTINGS_KEY,
                                                        getDefaultWindowPos() )
                       .toPoint();

    move( windowPos );
}

void typer::gui::MainWindow::storeWindowSettings()
{
    common::settings::setGUISetting( WINDOW_SIZE_SETTINGS_KEY, size() );
    common::settings::setGUISetting( WINDOW_POS_SETTINGS_KEY, pos() );
}

QPoint typer::gui::MainWindow::getDefaultWindowPos()
{
    return QApplication::primaryScreen()->geometry().center() - rect().center();
}


