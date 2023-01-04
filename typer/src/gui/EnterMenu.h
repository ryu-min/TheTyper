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
            void auth();
            void registration();

        private:
            void buildForm();
        };
    }
}

