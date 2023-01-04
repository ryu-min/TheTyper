#include "RegistrationWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

typer::gui::RegistrationWidget::RegistrationWidget(QWidget *parent)
    : QWidget( parent )
{
    buildForm();
}

void typer::gui::RegistrationWidget::buildForm()
{
    RegistrationDialog * registrationDialog = new RegistrationDialog;
    connect(registrationDialog, &RegistrationDialog::accepted,
            this, &RegistrationWidget::accepted);
    connect(registrationDialog, &RegistrationDialog::canceled,
            this, &RegistrationWidget::canceled);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );
    vLayout->addWidget( registrationDialog );
    vLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );
    mainLayout->addLayout( vLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );
}
