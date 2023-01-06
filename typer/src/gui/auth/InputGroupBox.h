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
