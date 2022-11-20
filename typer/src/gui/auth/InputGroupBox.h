#pragma once

#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>

namespace typer
{
    namespace gui
    {
        namespace InputGroupBox
        {
            inline QGroupBox * create(QLineEdit * lineEdit,
                               const QString & title = QString(),
                               const QString & tooltip = QString(),
                               bool passwordMode = false)
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
                QFont lineEditFont = lineEdit->font();
                lineEditFont.setPixelSize(12);
                lineEdit->setFont(lineEditFont);
                lineEdit->setStyleSheet("border:0; background-color: rgba(0, 0, 0, 0);");
                gbLayout->addWidget( lineEdit );
                gb->setLayout( gbLayout );

                return gb;
            }
        }
    }
}
