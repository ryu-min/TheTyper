#include "AuthentificationDialog.h"
#include "InputGroupBox.h"

#include <QPushButton>

typer::gui::AuthentificationDialog::AuthentificationDialog(QWidget *parent)
    : QWidget( parent )
    , m_userNameLineEdit( new QLineEdit )
    , m_passwordLineEdit( new QLineEdit )
{
    buildForm();
}

void typer::gui::AuthentificationDialog::showEvent(QShowEvent *event)
{
    m_userNameLineEdit->setFocus();
    QWidget::showEvent(event);
}

void typer::gui::AuthentificationDialog::buildForm()
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    auto userNameGroupBox = InputGroupBox::create(m_userNameLineEdit, "&User name");
    //userNameGroupBox->setFocus();

    mainLayout->addWidget( userNameGroupBox );
    mainLayout->addWidget( InputGroupBox::create( m_passwordLineEdit, "&Password", "", true));

    QHBoxLayout * buttonsLayout = new QHBoxLayout;
    QPushButton * acceptButton = new QPushButton("Accept");
    QPushButton * cancelButton = new QPushButton("Cancel");
    connect(acceptButton, &QPushButton::pressed, this, [this]() {
        AuthentificationInfo info;
        info.userName = m_userNameLineEdit->text();
        info.password = m_passwordLineEdit->text();
        emit accepted( info );
    });
    connect(cancelButton, &QPushButton::pressed, this, &AuthentificationDialog::canceled);

    acceptButton->setFixedWidth(70);
    cancelButton->setFixedWidth(70);
    buttonsLayout->addWidget( acceptButton, 0, Qt::AlignRight);
    buttonsLayout->addWidget( cancelButton);
    mainLayout->addLayout( buttonsLayout );

    setLayout(mainLayout);
}
