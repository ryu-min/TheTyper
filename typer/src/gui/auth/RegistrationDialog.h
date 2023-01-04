#pragma once

#include <QWidget>
#include <QLineEdit>

namespace typer
{
    namespace gui
    {
        class RegistrationDialog : public QWidget
        {
            Q_OBJECT

        public:
            struct RegistrationInfo {
                QString userName;
                QString password;
                QString confirmedPassword;
            };

        public:
            RegistrationDialog( QWidget * parent = nullptr);

        signals:
            void accepted( const typer::gui::RegistrationDialog::RegistrationInfo & info );
            void canceled();

        protected:
            void showEvent( QShowEvent * event) override;

        private:
            void buildForm();

        private:
            QLineEdit * m_userNameLineEdit;
            QLineEdit * m_passwordLineEdit;
            QLineEdit * m_confirmPassowordLineEdit;
        };
    }
}


