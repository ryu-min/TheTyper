#include "TyperWidget.h"


#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QPlainTextEdit>
#include <QTextEdit>

#include <QDebug>


typer::gui::TyperWidget::TyperWidget(QWidget *parent)
    : QWidget( parent )
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
    textEdit->setMaximumWidth(500);
    textEdit->setMaximumHeight(80);
    auto font = textEdit->font();
    font.setPointSize(18);
    textEdit->setFont(font);
    qDebug() << font.pointSize() << font.pixelSize();

    auto p = palette();
    p.setColor( backgroundRole(), Qt::yellow);
    setAutoFillBackground(true);
    setPalette(p);

    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Base, QColor(255, 255, 255, 0));
    textEdit->setPalette(palette);

    QStringList textToType = QString("Words are the basic building blocks of grammar. "
                                     "Words are combinations of letters and sounds, individual words are separated by spaces. "
                                     "Some words contain more than one part, such as hyphenated words and other compound words. "
                                     "Some words are pronounced in the same way but carry different meanings. "
//                                     "line5 line5 line5 line5 line5 line5 line5 line5 "
//                                     "line6 line6 line6 line6 line6 line6 line6 line6 "
//                                     "line7 line7 line7 line7 line7 line7 line7 line7 "
//                                     "line8 line8 line8 line8 line8 line8 line8 line8 ")
            ).split(" ");


    textEdit->setTextColor(Qt::gray);
//    textEdit->insertPlainText(textToType.join(' '));
    textEdit->setTextColor(Qt::black);
    textEdit->setAutoFillBackground(false);
    textEdit->setStyleSheet("border:0;");

    m_textRenderer = new TextEditRenderer(textToType, textEdit, this);
    m_textRenderer->setIncorrectWordColor(Qt::darkMagenta);
    m_textRenderer->setCorrectWordColor(Qt::darkCyan);
//    m_textRenderer->setNotTypedWordColor(Qt::lightGray);


    labelLayout->addWidget( textEdit );

    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );


    mainLayout->addLayout( labelLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    setLayout( mainLayout );
}
