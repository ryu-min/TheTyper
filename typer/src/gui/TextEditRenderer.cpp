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
    , inChanging(false)
    , m_typedText()
    , m_wordsToType(wordsToType)
    , m_textToTypeInfo()
    , m_wordTyped()
    , m_currentLine(0)
    , m_typedWordInLine(0)
{

    // @todo separate line

//     int maxSymbolWidth = textEdit->fontMetrics().maxWidth();
//    qDebug() << textEdit->width();
//    qDebug() << maxSymbolWidth;
//    qDebug() << "symbols in line edit can be" << textEdit->width() / maxSymbolWidth;
//    qDebug() << "horizonal adv is" << textEdit->fontMetrics().horizontalAdvance("some text some text some text some text");

    Q_ASSERT(m_textEdit);
    connect(m_textEdit, &QTextEdit::textChanged, this, &typer::gui::TextEditRenderer::textChanged);

    int line = 0;
    const int textEditWidth = textEdit->width();

    QFontMetrics fontMetrics = textEdit->fontMetrics();
    int scrollBarWidth = m_textEdit->verticalScrollBar()->sizeHint().width();
    for ( const QString & word : m_wordsToType )
    {
        QString currentLine = m_lines[line];
        QString newLine = currentLine.isEmpty() ? ( word ) : (currentLine + ' ' + word);
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

    QString firstText = m_lines[0];
    if ( m_lines.size() > 1 )
    {
        firstText += ' ' + m_lines[1];
    }

    inChanging = true;
    m_textEdit->setTextColor(m_notTypedWord);
//    for ( int key : m_lines.keys() )
//    {
//    }
    m_textEdit->insertPlainText(firstText);
    inChanging = false;
}

void typer::gui::TextEditRenderer::textChanged()
{
    //@todo handle tab input (skip)

    if ( inChanging ) return;
    inChanging = true;

    m_textEdit->moveCursor( QTextCursor::End);

    const QString allText = m_textEdit->toPlainText();
    QString joinedText = m_wordsToType.join(' ');

    joinedText = m_lines[m_currentLine];
    if ( m_currentLine + 1 < m_lines.size() )
    {
        joinedText += ' ' + m_lines[m_currentLine + 1];
    }

    QChar currentChar = allText.isEmpty() ? QChar(' ') : allText.back();
    QStringList splitedPreviousText = m_typedText.split(' ');
    if ( currentChar == ' ' )
    {
        // compare words in line and written

        /// fix first type bag
        if ( m_typedText.isEmpty() )
        {
            return;
        }
        else
        {
            if ( splitedPreviousText.size() != 0 )
            {
                QString currentWord = splitedPreviousText.last();
                Q_ASSERT(m_wordsToType.size() > m_wordTyped);
                WordTypeMode currentWordMode;
                if ( m_wordsToType[m_wordTyped] == currentWord )
                {
                    currentWordMode = WordTypeMode::CorrectTypedWord;
                }
                else
                {
                    currentWordMode = WordTypeMode::IncorrectTypedWord;
                }
                m_textToTypeInfo[m_wordTyped] = currentWordMode;

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
                m_typedText.append( m_wordsToType[m_wordTyped] + ' ' );
                m_wordTyped++;
                m_typedWordInLine++;
//                qDebug() << m_lines[m_currentLine].split(' ').size();
//                qDebug() << m_typedWordInLine;
                if ( m_lines[m_currentLine].split(' ').size() == m_typedWordInLine )
                {
//                    qDebug() << "new line";
                    //m_typedWordInLine = 0;

                    m_typedText.clear();
                }
            }
        }
    }
    else
    {
        if ( allText.size() < joinedText.size() )
        {
            qDebug() << "backspace";

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
    if ( m_wordsToType.size() == m_wordTyped )
    {
        qDebug() << "all";
//        emit exit();
    }


    m_textEdit->clear();
    m_textEdit->setTextColor(Qt::black);

    int writtenSize = 0;
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
        qDebug() << "insert word" << word;
        writtenSize += word.size() + 1;
    }

    bool newLineMove = m_lines[m_currentLine].split(' ').size() == m_typedWordInLine ;
    if ( newLineMove )
    {
        m_typedWordInLine = 0;
        m_textEdit->clear();
        m_currentLine++;
    }


//    for ( int i = 0; i < m_wordTyped; ++i)
//    {
//        WordTypeMode wordMode = m_textToTypeInfo[i];
//        if ( wordMode == WordTypeMode::CorrectTypedWord)
//        {
//            m_textEdit->setTextColor(m_correctWordColor);
//        }
//        else
//        {
//            m_textEdit->setTextColor(m_incorrectWordColor);
//        }
//        QString word = m_wordsToType[i];
//        m_textEdit->insertPlainText(word + " ");
//        writtenSize += word.size() + 1;
//    }

    /// has not fully typed word
    ///
    ///
    if ( m_typedText.size() != writtenSize  )
    {
        QString notPrintedWord =  m_typedText.right( m_typedText.size() - writtenSize /*- m_wordTyped*/);
        QString fullWord = m_wordsToType[m_wordTyped];

        if ( fullWord.startsWith(notPrintedWord) )
        {
            m_textEdit->setTextColor(m_correctWordColor);
        }
        else
        {
            m_textEdit->setTextColor(m_incorrectWordColor);
        }
        m_textEdit->insertPlainText(notPrintedWord);
        qDebug() << "insert not printed part" << notPrintedWord;
        writtenSize  += notPrintedWord.size();
    }

    qDebug() << joinedText << writtenSize;
    QString textToAdd = joinedText.right( joinedText.size() - writtenSize );
    m_textEdit->setTextColor(m_notTypedWord);
    m_textEdit->insertPlainText(textToAdd);
    qDebug() << "insert text to add" << textToAdd;

    if ( newLineMove && m_lines.size() > m_currentLine + 1)
    {
        qDebug() << "insetrt extenderd " <<  m_lines[m_currentLine + 1 ];
        m_textEdit->insertPlainText( ' ' + m_lines[m_currentLine + 1 ] );
    }

    inChanging = false;
}
