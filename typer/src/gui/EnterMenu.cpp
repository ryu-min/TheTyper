#include "EnterMenu.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QKeyEvent>

typer::gui::EnterMenu::EnterMenu(QWidget *parent)
    : QWidget( parent )
{
    buildForm();
    setFocusPolicy(Qt::StrongFocus);
}

void typer::gui::EnterMenu::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);
    if ( (event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return) )
    {
        emit start();
    }
}

void typer::gui::EnterMenu::buildForm()
{
    QVBoxLayout * buttonLayout = new QVBoxLayout();
    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 50;

    QPushButton * startButton = new QPushButton("Press enter to start", this);
    startButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); color: gray;}");

    startButton->setFixedWidth( BUTTON_WIDTH );
    startButton->setFixedHeight( BUTTON_HEIGHT );
    connect( startButton, &QPushButton::clicked, this, &EnterMenu::start);

    QPalette startButtonPallete = startButton->palette();
    startButtonPallete.setColor(QPalette::WindowText, Qt::gray);
    startButton->setPalette(startButtonPallete);

    QFont font = startButton->font();
    font.setPointSize(18);
    startButton->setFont(font);

    QPushButton * settingsButton = new QPushButton(this);
    settingsButton->setGeometry(20, 20, 40, 40);
    settingsButton->setIcon(QIcon(":/icons/settings.png"));
    settingsButton->setIconSize(QSize(40, 40));
    settingsButton->setToolTip("Go to settings");
    settingsButton->setStyleSheet("QPushButton { border: 0px; }");

    connect( settingsButton, &QPushButton::clicked, this, &EnterMenu::settings);


    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    buttonLayout->addWidget( startButton );
    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    mainLayout->addLayout( buttonLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    setLayout( mainLayout );
}
