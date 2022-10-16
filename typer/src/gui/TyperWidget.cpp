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

    QTextEdit * textEdit = new QTextEdit();
    textEdit->setMaximumWidth(300);
    textEdit->setMaximumHeight(60);

    textEdit->setOverwriteMode(true);

    textEdit->setTextColor(Qt::gray);
    textEdit->append("text text text text");
    textEdit->setTextColor(Qt::black);

    connect( textEdit, &QTextEdit::textChanged, [textEdit](){

        static bool inChanging = false;
        if ( inChanging )
        {
            return;
        }

        inChanging = true;

//        static int counter = 0;

        QString placeHolder = "text text text text";
        QString allText = textEdit->toPlainText();
        QString realText = allText.right(allText.size() - placeHolder.size());

        qDebug() << "clear";
        textEdit->clear();



        textEdit->setTextColor(Qt::black);
        textEdit->append(realText);
        qDebug() << "appen" << realText;

        textEdit->setTextColor(Qt::gray);
        textEdit->append(placeHolder);
        qDebug() << "appen" << placeHolder;


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
