#pragma once

#include <QWidget>
#include "RegistrationDialog.h"

namespace typer
{
    namespace gui
    {
        class RegistrationWidget : public QWidget
        {
            Q_OBJECT

        public:
            RegistrationWidget( QWidget * parent = nullptr );

        signals:
            void accepted( const typer::gui::RegistrationDialog::RegistrationInfo & info );
            void canceled();

        private:
            void buildForm();

        };

    }
}

