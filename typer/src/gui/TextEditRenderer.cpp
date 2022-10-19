#include "TextEditRenderer.h"

#include <QDebug>
#include <QScrollBar>

typer::gui::TextEditRenderer::TextEditRenderer(const QString &textToType,
                                               QTextEdit *textEdit,
                                               QObject *parent)
    : typer::gui::TextEditRenderer(textToType.split(' '),
                                   textEdit, parent)
{}

typer::gui::TextEditRenderer::TextEditRenderer(const QStringList &wordsToType,
                                               QTextEdit *textEdit,
                                               QObject *parent)
    : QObject(parent)
    , m_textEdit( textEdit )
    , m_correctWordColor(Qt::green)
    , m_incorrectWordColor(Qt::red)
    , m_notTypedWord(Qt::gray)
    , m_isRendering(false)
    , m_typedWordInfo()
    , m_lines()
    , m_currentLine(0)
    , m_typedWordInLine(0)
    , m_typedText()
{
    Q_ASSERT(m_textEdit);
    connect(m_textEdit, &QTextEdit::textChanged, this, &typer::gui::TextEditRenderer::textChanged);
    splitLines(wordsToType);
    setInitText();
}

void typer::gui::TextEditRenderer::textChanged()
{
    //@todo handle tab input (skip)

    if ( isRendering() ) return;
    startRendering();

    m_textEdit->moveCursor( QTextCursor::End);

    const QString textFromWidget = m_textEdit->toPlainText();
    QString textToType = m_lines[m_currentLine];
    if ( m_currentLine + 1 < m_lines.size() )
    {
        textToType += ' ' + m_lines[m_currentLine + 1];
    }

    const QChar currentChar = textFromWidget.isEmpty() ? QChar(' ') : textFromWidget.back();
    const QStringList splitedPreviousText = m_typedText.split(' ');

    // new word typed
    if ( currentChar == ' ' )
    {
        if ( !m_typedText.isEmpty() )
        {
            if ( splitedPreviousText.size() != 0 )
            {
                QString currentWord = splitedPreviousText.last();
                //Q_ASSERT(m_wordsToType.size() > m_wordTyped);
                WordTypeMode currentWordMode;
                const QString correctWord = m_lines[m_currentLine].split(' ')[m_typedWordInLine];
                if ( correctWord == currentWord )
                {
                    currentWordMode = WordTypeMode::CorrectTypedWord;
                }
                else
                {
                    currentWordMode = WordTypeMode::IncorrectTypedWord;
                }
                WordIndex index = qMakePair(m_currentLine, m_typedWordInLine);
                m_typedWordInfo[index] = currentWordMode;

                int lastSpaceIndex = m_typedText.lastIndexOf(' ');
                if ( lastSpaceIndex == -1 )
                {
                    m_typedText.clear();
                }
                else
                {
                    m_typedText.remove(lastSpaceIndex, m_typedText.size() - lastSpaceIndex);
                    if ( m_typedText.back() != ' ') m_typedText.append(' ');
                }
                m_typedText.append( correctWord + ' ' );
                m_typedWordInLine++;
            }
            // fix first type bag
            else
            {
                return;
            }
        }
    }
    else
    {
        // backspace typed
        if ( textFromWidget.size() < textToType.size() )
        {
            if ( !splitedPreviousText.last().isEmpty())
            {
                m_typedText.remove( m_typedText.size() - 1, 1);
            }
        }
        else
        {
            m_typedText.append(currentChar);
        }
    }

    m_textEdit->clear();
    m_textEdit->setTextColor(Qt::black);

    int typedWordSize = 0;
    for ( int i = 0; i < m_typedWordInLine; ++i)
    {
        WordIndex index = qMakePair(m_currentLine, i);
        WordTypeMode mode = m_typedWordInfo[index];
        if ( mode == WordTypeMode::CorrectTypedWord)
        {
            m_textEdit->setTextColor(m_correctWordColor);
        }
        else
        {
            m_textEdit->setTextColor(m_incorrectWordColor);
        }
        QString word = m_lines[m_currentLine].split(' ')[i];
        m_textEdit->insertPlainText(word + " ");
        typedWordSize += word.size() + 1;
    }

    bool newLineMove = m_lines[m_currentLine].split(' ').size() == m_typedWordInLine;
    if ( newLineMove )
    {
        m_typedWordInLine = 0;
        m_textEdit->clear();
        m_currentLine++;
        m_typedText.clear();
    }

    /// only part of word typed
    if ( m_typedText.size() != typedWordSize  )
    {
        const QString partOfWord =  m_typedText.right( m_typedText.size() - typedWordSize );
        //const QString fullWord = m_wordsToType[m_wordTyped];
        const QString fullWord = m_lines[m_currentLine].split(' ')[m_typedWordInLine];


        if ( fullWord.startsWith(partOfWord) )
        {
            m_textEdit->setTextColor(m_correctWordColor);
        }
        else
        {
            m_textEdit->setTextColor(m_incorrectWordColor);
        }
        m_textEdit->insertPlainText(partOfWord);
        typedWordSize  += partOfWord.size();
    }

    const QString textToAdd = textToType.right( textToType.size() - typedWordSize );
    m_textEdit->setTextColor(m_notTypedWord);
    m_textEdit->insertPlainText(textToAdd);
    if ( newLineMove && m_lines.size() > m_currentLine + 1)
    {
        m_textEdit->insertPlainText( ' ' + m_lines[m_currentLine + 1 ] );
    }

    stopRendering();
}

void typer::gui::TextEditRenderer::startRendering()
{
    m_isRendering = true;
}

void typer::gui::TextEditRenderer::stopRendering()
{
    m_isRendering = false;
}

bool typer::gui::TextEditRenderer::isRendering()
{
    return m_isRendering;
}

void typer::gui::TextEditRenderer::splitLines(const QStringList &words)
{
    int line = 0;
    const int textEditWidth = m_textEdit->width();
    const QFontMetrics fontMetrics = m_textEdit->fontMetrics();
    const int scrollBarWidth = m_textEdit->verticalScrollBar()->sizeHint().width();
    for ( const QString & word : words )
    {
        const QString currentLine = m_lines[line];
        const QString newLine = currentLine.isEmpty() ? ( word ) : (currentLine + ' ' + word);
        const int lineWidth = fontMetrics.horizontalAdvance(newLine) + scrollBarWidth;
        if ( lineWidth < textEditWidth )
        {
            m_lines[line] = newLine;
        }
        else
        {
            m_lines[++line] = word;
        }
    }
}

void typer::gui::TextEditRenderer::setInitText()
{
    QString initText = m_lines[0];
    if ( m_lines.size() > 1 )
    {
        initText += ' ' + m_lines[1];
    }

    startRendering();
    m_textEdit->setTextColor(m_notTypedWord);
    m_textEdit->insertPlainText(initText);
    stopRendering();
}
