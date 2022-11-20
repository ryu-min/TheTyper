#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>


namespace typer
{
    namespace gui
    {
        class RegistrationDialog : public QWidget
        {
        public:
            RegistrationDialog( QWidget * parent = nullptr);

        private:
            void buildForm();
            QGroupBox * createGroupBox( QLineEdit * lineEdit,
                                     const QString & title = QString(),
                                     const QString & tooltip = QString(),
                                     bool passwordMode = false);

        private:
            QLineEdit * m_userNameLineEdit;
            QLineEdit * m_passwordLineEdit;
            QLineEdit * m_confirmPassowordLineEdit;
        };
    }
}


