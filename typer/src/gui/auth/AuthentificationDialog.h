#pragma once

#include <QWidget>
#include <QLineEdit>

#include "../../common/UserInfo.h"

namespace typer
{
    namespace gui
    {
        class AuthentificationDialog : public QWidget
        {
            Q_OBJECT

        public:
            AuthentificationDialog( QWidget * parent = nullptr );

        signals:
            void accepted( const typer::common::AuthentificationInfo & info );
            void canceled();

        protected:
            void showEvent(QShowEvent *event) override;

        private:
            void buildForm();

        private:
            QLineEdit * m_userNameLineEdit;
            QLineEdit * m_passwordLineEdit;


        };
    }
}

