#include "RegistrationDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>


typer::gui::RegistrationDialog::RegistrationDialog(QWidget *parent)
    : QWidget( parent )
    , m_userNameLineEdit( new QLineEdit() )
    , m_passwordLineEdit( new QLineEdit() )
    , m_confirmPassowordLineEdit( new QLineEdit() )
{
    buildForm();
}

void typer::gui::RegistrationDialog::buildForm()
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget( createGroupBox(m_userNameLineEdit, "&User name") );
    mainLayout->addWidget( createGroupBox( m_passwordLineEdit, "", "password", true));
    mainLayout->addWidget( createGroupBox(m_confirmPassowordLineEdit, "", "confirm password", true));
    setLayout(mainLayout);
}

QGroupBox * typer::gui::RegistrationDialog::createGroupBox(QLineEdit *lineEdit,
                                                           const QString &title,
                                                           const QString &tooltip,
                                                           bool passwordMode)
{
    QGroupBox * gb = new QGroupBox(title);
    // @todo use colors from pallete
    gb->setStyleSheet(" QGroupBox { "
                            "border: 1px solid #a3a3a3; "
                            "border-radius: 3px; "
                            "margin-top: 2ex;  /*leave space at the top for the title */ "
                            "font-size: 12px;"
                        "}"
                        "QGroupBox::title {"
                        "    subcontrol-origin: margin;"
                        "    subcontrol-position: top left;    /* position at the top center */"
                        "    padding: 5 0px;"
                        "    font-size: 13px;"
                        "    color: white;"
                        "}");
    QVBoxLayout * gbLayout = new QVBoxLayout();
    if ( passwordMode ) lineEdit->setEchoMode( QLineEdit::Password );
    lineEdit->setPlaceholderText(tooltip);
    lineEdit->setAutoFillBackground(false);
    QFont f = lineEdit->font();
    f.setPixelSize(12);
    lineEdit->setFont(f);
    lineEdit->setStyleSheet("border:0; background-color: rgba(0, 0, 0, 0);");
    gbLayout->addWidget( lineEdit );
    gb->setLayout( gbLayout );

    return gb;
}
