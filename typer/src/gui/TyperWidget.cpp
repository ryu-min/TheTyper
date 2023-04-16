#include "TyperWidget.h"
#include "../common/Network.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QPlainTextEdit>
#include <QTextEdit>
#include <QToolTip>

#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

typer::gui::TyperWidget::TyperWidget(QWidget *parent)
    : QWidget( parent )
{
    buildForm();
}

void typer::gui::TyperWidget::buildForm()
{
    QPushButton * exitButton = new QPushButton(this);
    exitButton->setGeometry(20, 20, 40, 40);
    exitButton->setIcon(QIcon(":/icons/home.png"));
    exitButton->setIconSize(QSize(40, 40));
    exitButton->setToolTip("Go home");
    exitButton->setStyleSheet("QPushButton {"
                             "border: 0px;}");
    connect(exitButton, &QPushButton::clicked,
            this, &TyperWidget::exit);

    QVBoxLayout * labelLayout = new QVBoxLayout();
    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    TyperTextEdit * textEdit = new TyperTextEdit();
    textEdit->setMaximumWidth(500);
    textEdit->setMaximumHeight(80);
    auto font = textEdit->font();
    font.setPointSize(18);
    textEdit->setFont(font);

    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Base, QColor(255, 255, 255, 0));
    textEdit->setPalette(palette);

    QString textToType = typer::common::requestWords("ru_5000").unwrapOr(QString("error"));
    typer::common::WordsTypes wordsTypes = typer::common::requestWordTypes().unwrapOr(typer::common::WordsTypes());
    qDebug() << "words types" << wordsTypes;

    textEdit->setTextColor(Qt::gray);
    textEdit->setTextColor(Qt::black);
    textEdit->setAutoFillBackground(false);
    textEdit->setStyleSheet("border:0;");

    QStringList wordsToType = textToType.split(' ');
    std::random_shuffle(wordsToType.begin(), wordsToType.end());
    m_textRenderer = new TextEditRenderer(wordsToType, textEdit, this);
    m_textRenderer->setIncorrectWordColor(Qt::red);
    m_textRenderer->setCorrectWordColor(Qt::darkCyan);


    labelLayout->addWidget( textEdit );

    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );


    mainLayout->addLayout( labelLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    setLayout( mainLayout );
}
