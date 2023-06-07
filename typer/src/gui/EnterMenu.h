#pragma once

#include <QWidget>
#include <QComboBox>

namespace typer
{
    namespace gui
    {
        class EnterMenu : public QWidget
        {
            Q_OBJECT
        public:
            EnterMenu( const QStringList & wordTypes,
                       QWidget * parent = nullptr);

        signals:
            void start(const QString & wordType);
            void settings();

        protected:
            void keyReleaseEvent(QKeyEvent *event) override;
            void resizeEvent(QResizeEvent *event) override;
            void showEvent(QShowEvent *event) override;

        protected slots:
            void emitStart();

        private:
            void buildForm(const QStringList & wordTypes);

        private:
            QComboBox * m_wordTypeComboBox;
        };
    }
}

