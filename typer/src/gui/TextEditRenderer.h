#pragma once

#include <QTextEdit>
#include <QColor>

namespace typer
{
    namespace gui
    {
        class TextEditRenderer : public QObject
        {
            Q_OBJECT
        public:
            TextEditRenderer(const QString & textToType,
                                 QTextEdit * textEdit,
                                 QObject * parent);

            TextEditRenderer(const QStringList & wordsToType,
                                 QTextEdit * textEdit,
                                 QObject * parent);

            void setCorrectWordColor( const QColor & color) {
                m_correctWordColor = color;
            }

            void setIncorrectWordColor( const QColor & color) {
                m_incorrectWordColor = color;
            }

            void setNotTypedWordColor( const QColor & color) {
                m_notTypedWord = color;
            }

        protected slots:
            void textChanged();

        protected:
            QTextEdit * m_textEdit;
            // @todo trouble with naming here
            QColor m_correctWordColor;
            QColor m_incorrectWordColor;
            QColor m_notTypedWord;

        private:

            enum class WordPrintMode {
                CorrectTypedWord,
                IncorrectTypedWord,
                NotTypedWord
            };

            QString m_typedText;
            QStringList m_wordsToType;
            QMap<int, WordPrintMode> m_textToTypeInfo;
            int m_wordTyped;
        };
    }
}


