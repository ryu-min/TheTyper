#pragma once

#include <QWidget>

#include "AuthentificationDialog.h"

namespace typer
{
    namespace gui
    {
        class AuthentificationWidget : public QWidget
        {
            Q_OBJECT
        public:
            AuthentificationWidget( QWidget * parent = nullptr);

        signals:
            void accepted( const typer::gui::AuthentificationDialog::AuthentificationInfo & info );
            void canceled();

        private:
            void buildForm();
        };
    }

}


