#pragma once

#include <QWidget>

#include "../../common/UserInfo.h"

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
            void accepted( const typer::common::AuthentificationInfo & info );
            void canceled();

        private:
            void buildForm();
        };
    }

}


