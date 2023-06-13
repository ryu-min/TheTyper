#pragma once

#include <QMainWindow>


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
            void showEnterWidget();
            void showTyperWidget(const QString & wordType);
            void showSettingsWidget();
            void updateWordTypes();

        private:
            QStringList m_wordTypes;
        };
    }
}
