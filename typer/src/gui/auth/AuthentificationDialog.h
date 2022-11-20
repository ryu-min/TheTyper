#pragma once

#include <QWidget>
#include <QLineEdit>

namespace typer
{
    namespace gui
    {
        class AuthentificationDialog : public QWidget
        {
            Q_OBJECT

        public:
            struct AuthentificationInfo {
                QString userName;
                QString password;
            };

        public:
            AuthentificationDialog( QWidget * parent = nullptr );

        signals:
            void accepted( const typer::gui::AuthentificationDialog::AuthentificationInfo & info );
            void canceled();

        private:
            void buildForm();

        private:
            QLineEdit * m_userNameLineEdit;
            QLineEdit * m_passwordLineEdit;

        };
    }
}

