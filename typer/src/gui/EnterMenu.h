#pragma once

#include <QWidget>

namespace typer
{
    namespace gui
    {
        class EnterMenu : public QWidget
        {
            Q_OBJECT
        public:
            EnterMenu( QWidget * parent = nullptr);

        signals:
            void start();
            void settings();

        private:
            void buildForm();
        };
    }
}

