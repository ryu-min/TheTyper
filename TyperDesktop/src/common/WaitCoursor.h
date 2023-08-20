#pragma once

#include <QApplication>

namespace typer
{
    namespace common
    {
        class WaitCoursor : public QObject
        {
        public:
            WaitCoursor( QObject * parent = nullptr ) {
                QApplication::setOverrideCursor(Qt::WaitCursor);
            }

            ~WaitCoursor() {
                QApplication::restoreOverrideCursor();
            }
        };
    }
}
