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
    textEdit->setMaximumWidth(300);
    textEdit->setMaximumHeight(60);

    textEdit->setOverwriteMode(true);

    QStringList textToType = QString("some text some text some text some text "
                           "some text some text some text some text").split(" ");


    textEdit->setTextColor(Qt::gray);
    textEdit->insertPlainText(textToType.join(' '));
    textEdit->setTextColor(Qt::black);

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
