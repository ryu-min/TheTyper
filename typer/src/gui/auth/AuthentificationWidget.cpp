#include "AuthentificationWidget.h"

#include "AuthentificationDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

typer::gui::AuthentificationWidget::AuthentificationWidget(QWidget *parent)
    : QWidget( parent )
{
    buildForm();
}

void typer::gui::AuthentificationWidget::buildForm()
{
    AuthentificationDialog * authDialog = new AuthentificationDialog;
    connect(authDialog, &AuthentificationDialog::accepted,
            this, &AuthentificationWidget::accepted);
    connect(authDialog, &AuthentificationDialog::canceled,
            this, &AuthentificationWidget::canceled);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );
    vLayout->addWidget( authDialog );
    vLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );
    mainLayout->addLayout( vLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding) );
}
