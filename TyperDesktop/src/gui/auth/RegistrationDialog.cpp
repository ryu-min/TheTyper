#include "RegistrationDialog.h"
#include "InputGroupBox.h"

#include <QPushButton>

typer::gui::RegistrationDialog::RegistrationDialog(QWidget *parent)
    : QWidget( parent )
    , m_userNameLineEdit( new QLineEdit() )
    , m_passwordLineEdit( new QLineEdit() )
    , m_confirmPassowordLineEdit( new QLineEdit() )
{
    buildForm();
}

void typer::gui::RegistrationDialog::showEvent(QShowEvent *event)
{
    m_userNameLineEdit->setFocus();
    QWidget::showEvent( event );
}

void typer::gui::RegistrationDialog::buildForm()
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget( InputGroupBox::create(m_userNameLineEdit, "&User name") );
    mainLayout->addWidget( InputGroupBox::create( m_passwordLineEdit, "&Password", true));
    mainLayout->addWidget( InputGroupBox::create(m_confirmPassowordLineEdit, "&Confirmed password", true));

    QHBoxLayout * buttonsLayout = new QHBoxLayout;
    QPushButton * acceptButton = new QPushButton("Accept");
    QPushButton * cancelButton = new QPushButton("Cancel");
    connect(acceptButton, &QPushButton::pressed, this, [this]() {
        typer::common::RegistrationInfo info;
        info.userName = m_userNameLineEdit->text();
        info.password = m_passwordLineEdit->text();
        info.confirmedPassword = m_confirmPassowordLineEdit->text();
        emit accepted( info );
    });
    connect(cancelButton, &QPushButton::pressed, this, &RegistrationDialog::canceled);
    acceptButton->setFixedWidth(70);
    cancelButton->setFixedWidth(70);
    buttonsLayout->addWidget( acceptButton, 0, Qt::AlignRight);
    buttonsLayout->addWidget( cancelButton);
    mainLayout->addLayout( buttonsLayout );

    setLayout(mainLayout);
}
