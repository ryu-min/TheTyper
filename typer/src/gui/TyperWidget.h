#pragma once

#include <QWidget>

namespace typer
{
    namespace gui
    {
        class TyperWidget : public QWidget
        {
            Q_OBJECT
        public:
            TyperWidget( QWidget * parent = nullptr);

        signals:
            void exit();

        private:
            void buildForm();
        };
    }
}


