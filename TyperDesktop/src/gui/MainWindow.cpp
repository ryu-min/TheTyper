#include "MainWindow.h"

#include "EnterMenu.h"
#include "SettingsWidget.h"

// @todo typer, typing.. naming is pain
#include "TyperWidget.h"
#include "TypeResultWidget.h"

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
    if (!m_prevTypeSettings.wordType.isEmpty()) {
        enterMenu->setCurentSettings(m_prevTypeSettings.wordType,
                                     m_prevTypeSettings.timeS);
    }
    setCentralWidget( enterMenu );
    connect( enterMenu, &EnterMenu::start, this, &MainWindow::showTyperWidget );
    connect( enterMenu, &EnterMenu::settings, this, &MainWindow::showSettingsWidget );
}

void typer::gui::MainWindow::showTyperWidget(const QString &wordType, int timeS)
{
    m_prevTypeSettings = MainWindow::TypeSettings { wordType, timeS };
    TyperWidget * typerWidget = new TyperWidget(wordType, timeS, this);
    setCentralWidget( typerWidget );
    connect( typerWidget, &TyperWidget::exit, this, &MainWindow::showEnterWidget);
    connect( typerWidget, &TyperWidget::finish, this, &MainWindow::showResultWidget);
}

void typer::gui::MainWindow::showSettingsWidget()
{
    SettingsWidget * settingsWidget = new SettingsWidget(this);
    setCentralWidget( settingsWidget );
    connect( settingsWidget, &SettingsWidget::exit, this, &MainWindow::showEnterWidget);
}

void typer::gui::MainWindow::showResultWidget(const common::TypeResults &typeResults)
{
    TypeResultWidget * resultWidget = new TypeResultWidget(typeResults);
    connect(resultWidget, &TypeResultWidget::exit, this, &MainWindow::showEnterWidget);
    connect(resultWidget, &TypeResultWidget::repeat, this, [this]() {
        showTyperWidget(m_prevTypeSettings.wordType, m_prevTypeSettings.timeS);
    });
    setCentralWidget(resultWidget);
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


