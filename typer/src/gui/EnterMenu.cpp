#include "EnterMenu.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

typer::gui::EnterMenu::EnterMenu(QWidget *parent)
    : QWidget( parent )
{
    buildForm();
}

void typer::gui::EnterMenu::buildForm()
{
    QVBoxLayout * buttonLayout = new QVBoxLayout();
    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 50;

    QPushButton * startButton = new QPushButton("Старт", this);
    startButton->setFixedWidth( BUTTON_WIDTH );
    startButton->setFixedHeight( BUTTON_HEIGHT );
    connect( startButton, &QPushButton::clicked, this, &EnterMenu::start);

    QPushButton * settingsButton = new QPushButton("Настройки", this);
    settingsButton->setFixedWidth(BUTTON_WIDTH);
    settingsButton->setFixedHeight(BUTTON_HEIGHT);
    connect( settingsButton, &QPushButton::clicked, this, &EnterMenu::settings);

    QPushButton * authButton = new QPushButton("Авторизация", this);
    authButton->setFixedWidth(BUTTON_WIDTH);
    authButton->setFixedHeight(BUTTON_HEIGHT);
    connect( authButton, &QPushButton::clicked, this, &EnterMenu::auth);

    QPushButton * registrationButton = new QPushButton("Регистрация", this);
    registrationButton->setFixedWidth(BUTTON_WIDTH);
    registrationButton->setFixedHeight(BUTTON_HEIGHT);
    connect( registrationButton, &QPushButton::clicked, this, &EnterMenu::registration);

    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    buttonLayout->addWidget( startButton );
    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum) );
    buttonLayout->addWidget( settingsButton );
    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum) );
    buttonLayout->addWidget( authButton );
    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum) );
    buttonLayout->addWidget( registrationButton );
    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    mainLayout->addLayout( buttonLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    setLayout( mainLayout );
}
