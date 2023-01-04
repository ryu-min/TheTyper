#pragma once

#include <QWidget>

#include "../../common/UserInfo.h"

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
            void accepted( const typer::common::RegistrationInfo & info );
            void canceled();

        private:
            void buildForm();
        };
    }
}

