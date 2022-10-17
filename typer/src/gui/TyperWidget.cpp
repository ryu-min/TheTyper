#include "TyperWidget.h"


#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QPlainTextEdit>
#include <QTextEdit>

#include <QDebug>


typer::gui::TyperWidget::TyperWidget(QWidget *parent)
    : QWidget( parent )
    , m_previousTypedText()
    , m_wordTyped(0)

{

    buildForm();
}

void typer::gui::TyperWidget::buildForm()
{
    QPushButton * exitButton = new QPushButton(this);
    exitButton->setGeometry(20, 20, 40, 40);
    connect(exitButton, &QPushButton::clicked,
            this, &TyperWidget::exit);
    exitButton->setText("X");

    QVBoxLayout * labelLayout = new QVBoxLayout();
    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    TyperTextEdit * textEdit = new TyperTextEdit();
    textEdit->setMaximumWidth(300);
    textEdit->setMaximumHeight(60);

    textEdit->setOverwriteMode(true);

    m_textToType = QString("some text some text some text some text "
                           "some text some text some text some text").split(" ");


    textEdit->setTextColor(Qt::gray);
    textEdit->insertPlainText(m_textToType.join(' '));
    textEdit->setTextColor(Qt::black);


    int maxSymbolWidth = textEdit->fontMetrics().maxWidth();
    qDebug() << textEdit->width();
    qDebug() << maxSymbolWidth;
    qDebug() << "symbols in line edit can be" << textEdit->width() / maxSymbolWidth;
    qDebug() << "horizonal adv is" << textEdit->fontMetrics().horizontalAdvance("some text some text some text some text");

    m_textRenderer = new TextEditRenderer(m_textToType,
                                              textEdit,
                                              this);

//    connect( textEdit, &QTextEdit::textChanged, [textEdit, this](){

////        static QString m_previousTypedText = "";

//        static bool inChanging = false;
//        if ( inChanging ) return;
//        inChanging = true;

//        textEdit->moveCursor( QTextCursor::End);

//        const QString allText = textEdit->toPlainText();
//        QString joinedText = m_textToType.join(' ');
////        int charWritten = backgroundText.size() - allText.size();
////        if ( charWritten <= 0 )
////        {
////            qDebug() << "all text typed";
////        }


//        QChar currentChar = allText.isEmpty() ? QChar(' ') : allText.back();
//        QStringList splitedPreviousText = m_previousTypedText.split(' ');
//        if ( currentChar == ' ' )
//        {
//            /// fix first type bag
//            if ( m_previousTypedText.isEmpty() )
//            {
//                return;
//            }
//            else
//            {
//                if ( splitedPreviousText.size() != 0 )
//                {
//                    QString currentWord = splitedPreviousText.last();
//                    Q_ASSERT(m_textToType.size() > m_wordTyped);
//                    WordPrintMode currentWordMode;
//                    if ( m_textToType[m_wordTyped] == currentWord )
//                    {
//                        currentWordMode = WordPrintMode::CorrectTypedWord;
//                    }
//                    else
//                    {
//                        currentWordMode = WordPrintMode::IncorrectTypedWord;
//                    }
//                    m_textToTypeInfo[m_wordTyped] = currentWordMode;
//                    int lastSpace = m_previousTypedText.lastIndexOf(' ');
//                    if ( lastSpace == -1 )
//                    {
//                        m_previousTypedText.clear();
//                    }
//                    else
//                    {
//                        m_previousTypedText.remove(lastSpace, m_previousTypedText.size() - lastSpace);
//                        if ( m_previousTypedText.back() != ' ') m_previousTypedText.append(' ');
//                    }
//                    m_previousTypedText.append( m_textToType[m_wordTyped] + ' ' );
//                    m_wordTyped++;
//                }
//            }
//        }
//        else
//        {

//            qDebug() << "size should be" << joinedText.size();
//            qDebug() << "size in edit" << allText.size();
//            //qDebug() << previosAllText.size();
////            if ( allText.size() < previosAllText.size() || allText == previosAllText )
//            if ( allText.size() < joinedText.size() )
//            {
//                qDebug() << "backspace";

//                if ( !splitedPreviousText.last().isEmpty())
//                {
////                    qDebug() << "return from backspace";
////                    return;
//                    m_previousTypedText.remove( m_previousTypedText.size() - 1, 1);
//                }

//            }
//            else
//            {
//                m_previousTypedText.append(currentChar);
//            }
//        }
//        if ( m_textToType.size() == m_wordTyped )
//        {
//            qDebug() << "all";
//            emit exit();
//        }


//        textEdit->clear();
//        textEdit->setTextColor(Qt::black);
//        int writtenSize = 0;
//        for ( int i = 0; i < m_wordTyped; ++i)
//        {
//            WordPrintMode wordMode = m_textToTypeInfo[i];
//            if ( wordMode == WordPrintMode::CorrectTypedWord)
//            {
//                textEdit->setTextColor(Qt::green);
//            }
//            else
//            {
//                textEdit->setTextColor(Qt::red);
//            }
//            QString word = m_textToType[i];
//            textEdit->insertPlainText(word + " ");
//            writtenSize += word.size() + 1;
//        }

//        /// has not fully typed word
//        if ( m_previousTypedText.size() != writtenSize  )
//        {
//            QString notPrintedWord =  m_previousTypedText.right( m_previousTypedText.size() - writtenSize /*- m_wordTyped*/);
//            QString fullWord = m_textToType[m_wordTyped];

//            if ( fullWord.startsWith(notPrintedWord) )
//            {
//                textEdit->setTextColor(Qt::green);
//            }
//            else
//            {
//                textEdit->setTextColor(Qt::red);
//            }
//            textEdit->insertPlainText(notPrintedWord);
//            writtenSize  += notPrintedWord.size();
//        }

//        QString textToAdd = joinedText.right( joinedText.size() - writtenSize );
//        textEdit->setTextColor(Qt::gray);
//        textEdit->insertPlainText(textToAdd);

//        inChanging = false;
//    });

    labelLayout->addWidget( textEdit );

    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );


    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );


    mainLayout->addLayout( labelLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    setLayout( mainLayout );
}
