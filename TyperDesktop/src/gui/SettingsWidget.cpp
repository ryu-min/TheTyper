#include "SettingsWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QToolTip>

typer::gui::SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget( parent )
{
    buildForm();
}

void typer::gui::SettingsWidget::buildForm()
{
    QPushButton * exitButton = new QPushButton(this);
    exitButton->setGeometry(20, 20, 40, 40);
    exitButton->setIcon(QIcon(":/icons/home.png"));
    exitButton->setIconSize(QSize(40, 40));
    exitButton->setToolTip("Go home");
    exitButton->setStyleSheet("QPushButton {"
                             "border: 0px;}");
    connect(exitButton, &QPushButton::clicked,
            this, &SettingsWidget::exit);

    QVBoxLayout * labelLayout = new QVBoxLayout();
    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );
    labelLayout->addWidget( new QLabel("Тут будут настройки"));
    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );


    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );
    mainLayout->addLayout( labelLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    setLayout( mainLayout );
}
