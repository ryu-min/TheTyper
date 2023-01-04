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

            /**
             * @brief The AuthentificationInfo class - @todo move out of class ?
             */
            struct AuthentificationInfo {
                QString userName;
                QString password;
            };

        public:
            AuthentificationDialog( QWidget * parent = nullptr );

        signals:
            void accepted( const typer::gui::AuthentificationDialog::AuthentificationInfo & info );
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

