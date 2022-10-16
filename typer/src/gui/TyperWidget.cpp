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

    const QString backgroundText = "some new text here should"
                                   "be available to do something";


    textEdit->setTextColor(Qt::gray);
    textEdit->insertPlainText(backgroundText);
    textEdit->setTextColor(Qt::black);

    textEdit->setFocus();

    connect( textEdit, &QTextEdit::textChanged, [textEdit, backgroundText, this](){

//        static QString m_previousTypedText = "";

        static bool inChanging = false;
        if ( inChanging ) return;
        inChanging = true;

        textEdit->moveCursor( QTextCursor::End);

        QString allText = textEdit->toPlainText();
//        int charWritten = backgroundText.size() - allText.size();
//        if ( charWritten <= 0 )
//        {
//            qDebug() << "all text typed";
//        }


        QChar currentChar = allText.isEmpty() ? QChar(' ') : allText.back();
        if ( currentChar == '\n')
        {
            qDebug() << currentChar << "is back";
        }

        qDebug() << currentChar;


        /// fix first type bag
        if ( currentChar == ' ' && m_previousTypedText.isEmpty() )
        {
            return;
        }

        m_previousTypedText.append(currentChar);

        QString currentWord;
        QStringList splitedPreviousText = m_previousTypedText.split(' ');
        if ( splitedPreviousText.size() != 0 )
        {
            currentWord = splitedPreviousText.last();
        }
        qDebug() << "current word is" << currentWord;


        textEdit->clear();
        textEdit->setTextColor(Qt::black);

        /// !todo loop thltow splited to correct showing and check
        /// was it correct typed word or not


        textEdit->insertPlainText( m_previousTypedText );

        qDebug() << "previous" << m_previousTypedText;

        textEdit->setTextColor(Qt::gray);
        const int newBackgrountTextSize = backgroundText.size() - m_previousTypedText.size();
        textEdit->insertPlainText( backgroundText.right( newBackgrountTextSize ) );



//        textEdit->append(allText);
//        qDebug() << "appen" << allText;

//        textEdit->append(backgroundText);
//        qDebug() << "appen" << backgroundText;



        inChanging = false;
    });

    labelLayout->addWidget( textEdit );

    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );


    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );


    mainLayout->addLayout( labelLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    setLayout( mainLayout );
}
