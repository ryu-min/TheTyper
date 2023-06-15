#pragma once

#include <QTextEdit>
#include <QColor>
#include <QTimer>
#include <QElapsedTimer>

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
                             int sTime,
                             QObject * parent = nullptr);

            TextEditRenderer(const QStringList & wordsToType,
                             QTextEdit * textEdit,
                             int sTime,
                             QObject * parent = nullptr);

            void setCorrectWordColor( const QColor & color) {
                m_correctWordColor = color;
            }

            void setIncorrectWordColor( const QColor & color) {
                m_incorrectWordColor = color;
            }

            void setNotTypedWordColor( const QColor & color) {
                m_notTypedWord = color;
            }

        signals:
            void speedCaclulated( int speed );
            void finish( int speed );

        protected slots:
            void textChanged();

        protected:
            void startRendering();
            void stopRendering();
            bool isRendering();
            void splitLines( const QStringList & words);
            void setInitText();
            int calcSpeed();

        protected:
            QTextEdit * m_textEdit;
            // @todo trouble with naming here
            QColor m_correctWordColor;
            QColor m_incorrectWordColor;
            QColor m_notTypedWord;


        private:

            enum class WordTypeMode {
                CorrectTypedWord,
                IncorrectTypedWord,
                NotTypedWord
            };

            using LineNumber = int;
            using WordNumber = int;
            using LineText   = QString;
            using WordIndex  = QPair<LineNumber, WordNumber>;

            friend class RendereeGuard;
            struct RendererGuard {
                RendererGuard(TextEditRenderer * renderer) : m_renderer(renderer) {
                    if ( m_renderer ) m_renderer->startRendering();
                }
                ~RendererGuard() {
                    if ( m_renderer ) m_renderer->stopRendering();
                }

            private:
                TextEditRenderer * m_renderer;
            };

        private:

            bool m_isRendering;
            QMap<WordIndex, WordTypeMode> m_typedWordInfo;
            QMap<LineNumber, LineText> m_lines;
            LineNumber m_currentLine;
            WordNumber m_typedWordInLine;
            LineText m_typedText;
            QTimer m_calcSpeedTimer;
            QTimer m_finishTimer;
            int m_sFihishTime;
            QElapsedTimer m_typeTimer;
            QStringList m_typedTextToCalcSpeed;
            QStringList m_correctTextToCalcSpeed;
        };
    }
}
