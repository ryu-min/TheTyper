#pragma once

#include <QWidget>

namespace typer
{
    namespace gui
    {
        class SettingsWidget : public QWidget
        {
            Q_OBJECT
        public:
            SettingsWidget( QWidget * parent = nullptr );

        signals:
            void exit();

        private:
            void buildForm();
        };
    }
}

