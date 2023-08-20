#pragma once

#include "TextEditRenderer.h"
#include "../common/TypeResult.h"

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QLabel>

namespace typer
{
    namespace gui
    {

        class TyperTextEdit : public QTextEdit
        {
        public:
            TyperTextEdit( QWidget * parent = nullptr )
                : QTextEdit( parent ) {
                setReadOnly(true);
                setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            }

            void showEvent(QShowEvent * event) override {
                setFocus();
                QTextEdit::showEvent(event);
            }

            void keyPressEvent(QKeyEvent *event) override {
                setReadOnly(false);
                QTextEdit::keyPressEvent(event);
                setReadOnly(true);
            }
        };

        class TyperWidget : public QWidget
        {
            Q_OBJECT
        public:
            TyperWidget( const QString & wordType,
                         int sTime,
                         QWidget * parent = nullptr);

        signals:
            void exit();
            void finish(const common::TypeResults & speed);

        protected:
            void resizeEvent(QResizeEvent *event) override;
            void keyPressEvent(QKeyEvent *event);

        protected slots:
            void typeResultCalculated(const common::TypeResult & typeResult);

        private:
            void buildForm(const QString & wordType, int sTime);

        private:
            TextEditRenderer * m_textRenderer;
            QLabel * m_speedLabel;
            common::TypeResults m_typeResults;
        };
    }
}


