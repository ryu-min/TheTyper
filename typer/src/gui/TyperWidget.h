#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QDebug>
#include <QKeyEvent>

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
            TyperWidget( QWidget * parent = nullptr);

        signals:
            void exit();

        protected:
            void hideEvent(QHideEvent *event) override {
                m_previousTypedText.clear();
                m_wordTyped = 0;
                QWidget::hideEvent(event);
            }

        private:
            void buildForm();

        private:

            enum class WordPrintMode {
                CorrectTypedWord,
                IncorrectTypedWord,
                NotTypedWord
            };

            QString m_previousTypedText;
            QStringList m_textToType;
            QMap<int, WordPrintMode> m_textToTypeInfo;
            int m_wordTyped;
        };
    }
}


