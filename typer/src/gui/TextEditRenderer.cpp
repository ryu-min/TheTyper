#include "TextEditRenderer.h"

#include <QScrollBar>
#include <QApplication>
#include <QElapsedTimer>

typer::gui::TextEditRenderer::TextEditRenderer(const QString &textToType,
                                               QTextEdit *textEdit,
                                               int sTime,
                                               QObject *parent)
    : typer::gui::TextEditRenderer(textToType.split(' '),
                                   textEdit, sTime, parent)
{}

typer::gui::TextEditRenderer::TextEditRenderer(const QStringList &wordsToType,
                                               QTextEdit *textEdit,
                                               int sTime,
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
    m_sFihishTime = sTime;
    splitLines(wordsToType);
    setInitText();
    connect(m_textEdit, &QTextEdit::textChanged, this, &typer::gui::TextEditRenderer::textChanged);

    connect(&m_calcSpeedTimer, &QTimer::timeout, this, [this]() {
        emit speedCaclulated( calcSpeed() );
    });
    connect(&m_finishTimer, &QTimer::timeout, this, [this]() {
       emit finish( calcSpeed() );
    });
}

void typer::gui::TextEditRenderer::textChanged()
{
    //@todo handle tab input (skip)
    if ( !m_calcSpeedTimer.isActive() )
    {
        m_calcSpeedTimer.start(1500);
        m_typeTimer.start();
        m_finishTimer.start( m_sFihishTime * 1000 );
    }

    if ( isRendering() ) return;
    RendererGuard rg(this); Q_UNUSED(rg);

    m_textEdit->moveCursor( QTextCursor::End);

    const QString textFromWidget = m_textEdit->toPlainText();
    QString textToType = m_lines[m_currentLine];
    if ( m_currentLine + 1 < m_lines.size() )
    {
        textToType += ' ' + m_lines[m_currentLine + 1];
    }

    const QChar currentChar = textFromWidget.isEmpty() ? QChar(' ') : textFromWidget.back();
    const QStringList splitedPreviousText = m_typedText.split(' ');

    // actualy do not understand this bag
    static bool firstTypeBagFixed = false;
    if ( !firstTypeBagFixed )
    {
        firstTypeBagFixed = true;
        return;
    }
    QString currentWord = splitedPreviousText.last();

    /// not allow space all the time
    if ( currentChar == ' ' && currentWord.isEmpty() )
    {
        return;
    }

    /// new word typed
    if ( currentChar == ' ' )
    {
        if ( !m_typedText.isEmpty() )
        {
            const QString correctWord = m_lines[m_currentLine].split(' ')[m_typedWordInLine];
            WordTypeMode currentWordMode = ( correctWord == currentWord )
                                           ? WordTypeMode::CorrectTypedWord
                                           : WordTypeMode::IncorrectTypedWord;

            m_correctTextToCalcSpeed.append( correctWord );
            m_typedTextToCalcSpeed.append( currentWord );

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
                m_typedText.append(' ');
            }
            m_typedText.append( currentWord + ' ' );
            m_typedWordInLine++;
        }
    }
    else
    {
        /// backspace typed
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
    QStringList typiedWords = m_typedText.split(" ");
    for ( int i = 0; i < m_typedWordInLine; ++i)
    {
        WordIndex index = qMakePair(m_currentLine, i);
        WordTypeMode mode = m_typedWordInfo[index];
        QColor wordColor = ( mode == WordTypeMode::CorrectTypedWord )
                           ? m_correctWordColor
                           : m_incorrectWordColor;
        m_textEdit->setTextColor(wordColor);
        const QString correctWord = m_lines[m_currentLine].split(' ')[i];
        const QString typiedWord = typiedWords.size() <= i ? " " :  typiedWords[i];
        int minSize = std::min(correctWord.size(), typiedWord.size());

        for ( int i = 0; i < minSize; i++ )
        {
            QColor col = correctWord[i] == typiedWord[i] ? m_correctWordColor : m_incorrectWordColor;
            m_textEdit->setTextColor(col);
            m_textEdit->insertPlainText( correctWord[i] );
        }
        /// not typied part of word
        int sizeDiff = correctWord.size() - minSize;
        int correctSize = correctWord.size();
        m_textEdit->setTextColor(m_incorrectWordColor);
        for ( int i = correctSize - sizeDiff; i < correctWord.size(); i++ )
        {
            m_textEdit->insertPlainText( correctWord[i] );
        }
        m_textEdit->insertPlainText(" ");
        typedWordSize += correctWord.size() + 1;
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
    if ( currentChar != ' ' )
    {
        const QString partOfWord =  m_typedText.split(" ").last();
        const QString fullWord = m_lines[m_currentLine].split(' ')[m_typedWordInLine];
        const int len = std::min(partOfWord.size(), fullWord.size() );
        for ( int i = 0; i < len; i++ )
        {
            QColor charColor = ( partOfWord[i] == fullWord[i] ) ? m_correctWordColor : m_incorrectWordColor;
            m_textEdit->setTextColor(charColor);
            m_textEdit->insertPlainText(partOfWord[i]);
        }
        typedWordSize  += len;
    }

    /// adding not tiped text
    const QString textToAdd = textToType.right( textToType.size() - typedWordSize );
    m_textEdit->setTextColor(m_notTypedWord);
    m_textEdit->insertPlainText(textToAdd);
    if ( newLineMove && m_lines.size() > m_currentLine + 1)
    {
        m_textEdit->insertPlainText( ' ' + m_lines[m_currentLine + 1 ] );
    }
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

int typer::gui::TextEditRenderer::calcSpeed()
{
    double msElapsed = m_typeTimer.elapsed();
    qsizetype wordCount = std::min( m_typedTextToCalcSpeed.size(),
                                    m_correctTextToCalcSpeed.size());
    quint64 charTyped = 0;
    for ( int i = 0; i < wordCount; ++i )
    {
        QString typed = m_typedTextToCalcSpeed[i];
        QString correct = m_correctTextToCalcSpeed[i];
        int size =  std::min( typed.size(), correct.size() );
        int typedInWord = 0;
        for ( int j = 0; j < size; ++j )
        {
            typedInWord += ( typed[j] == correct[j] ) ? 1 : 0;
        }
        /// add space
        typedInWord = ( typedInWord > 0 ) ? typedInWord + 1 : 0;
        charTyped += typedInWord;
    }
    ///  to the upper bound
    int speed = int( ( charTyped  / msElapsed ) * 1000 * 60 + 0.5) / 5 + 0.5;
    return speed;
}
