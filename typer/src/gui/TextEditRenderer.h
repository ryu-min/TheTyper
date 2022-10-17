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

            bool inChanging;

        private:

            enum class WordTypeMode {
                CorrectTypedWord,
                IncorrectTypedWord,
                NotTypedWord
            };

            QString m_typedText;
            QStringList m_wordsToType;
            QMap<int, WordTypeMode> m_textToTypeInfo;
            int m_wordTyped;

            using LineNumber = int;
            using WordNumber = int;
            using LineText   = QString;
            using WordIndex  = QPair<LineNumber, WordNumber>;

            QMap<WordIndex, WordTypeMode> m_typedWordInfo;
            QMap<LineNumber, LineText> m_lines;
            LineNumber m_currentLine;
        };
    }
}


