#pragma once

#include <QWidget>
#include <QLineEdit>

#include "../../common/UserInfo.h"

namespace typer
{
    namespace gui
    {
        class RegistrationDialog : public QWidget
        {
            Q_OBJECT

        public:
            RegistrationDialog( QWidget * parent = nullptr);

        signals:
            void accepted( const typer::common::RegistrationInfo & info );
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


