#include "TextEditRenderer.h"

#include <QDebug>

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
    , m_typedText()
    , m_wordsToType(wordsToType)
    , m_textToTypeInfo()
    , m_wordTyped()
{

    // @todo separate line

//     int maxSymbolWidth = textEdit->fontMetrics().maxWidth();
//    qDebug() << textEdit->width();
//    qDebug() << maxSymbolWidth;
//    qDebug() << "symbols in line edit can be" << textEdit->width() / maxSymbolWidth;
//    qDebug() << "horizonal adv is" << textEdit->fontMetrics().horizontalAdvance("some text some text some text some text");

    Q_ASSERT(m_textEdit);
    connect(m_textEdit, &QTextEdit::textChanged, this, &typer::gui::TextEditRenderer::textChanged);

}

void typer::gui::TextEditRenderer::textChanged()
{

    static bool inChanging = false;
    if ( inChanging ) return;
    inChanging = true;

    m_textEdit->moveCursor( QTextCursor::End);

    const QString allText = m_textEdit->toPlainText();
    QString joinedText = m_wordsToType.join(' ');
    QChar currentChar = allText.isEmpty() ? QChar(' ') : allText.back();
    QStringList splitedPreviousText = m_typedText.split(' ');
    if ( currentChar == ' ' )
    {
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
                WordPrintMode currentWordMode;
                if ( m_wordsToType[m_wordTyped] == currentWord )
                {
                    currentWordMode = WordPrintMode::CorrectTypedWord;
                }
                else
                {
                    currentWordMode = WordPrintMode::IncorrectTypedWord;
                }
                m_textToTypeInfo[m_wordTyped] = currentWordMode;
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
    for ( int i = 0; i < m_wordTyped; ++i)
    {
        WordPrintMode wordMode = m_textToTypeInfo[i];
        if ( wordMode == WordPrintMode::CorrectTypedWord)
        {
            m_textEdit->setTextColor(m_correctWordColor);
        }
        else
        {
            m_textEdit->setTextColor(m_incorrectWordColor);
        }
        QString word = m_wordsToType[i];
        m_textEdit->insertPlainText(word + " ");
        writtenSize += word.size() + 1;
    }

    /// has not fully typed word
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
        writtenSize  += notPrintedWord.size();
    }

    QString textToAdd = joinedText.right( joinedText.size() - writtenSize );
    m_textEdit->setTextColor(m_notTypedWord);
    m_textEdit->insertPlainText(textToAdd);

    inChanging = false;
}
