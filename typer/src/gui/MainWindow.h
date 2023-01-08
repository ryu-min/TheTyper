#pragma once

#include <QMainWindow>

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
            void openEnterMenu();
        };
    }
}
