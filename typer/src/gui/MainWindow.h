#pragma once

#include <QMainWindow>

#include "SettingsWidget.h"
#include "TyperWidget.h"
#include "EnterMenu.h"

namespace typer
{
    namespace gui
    {
        class MainWindow : public QMainWindow
        {
            Q_OBJECT
        public:
            MainWindow(QWidget *parent = nullptr);


        private slots:
            void setEnterMenu();

        };
    }
}
