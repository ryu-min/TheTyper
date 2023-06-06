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

typer::gui::TyperWidget::TyperWidget(const QString &wordType,
                                     QWidget *parent)
    : QWidget( parent )
{
    buildForm(wordType);
}

void typer::gui::TyperWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QSizeF wSize = size();
    QSizeF sSize = m_speedLabel->size();
    qDebug() << sSize;
    m_speedLabel->move( wSize.width() / 2 - sSize.width() / 2,
                        wSize.height()/2 - 80);
}

void typer::gui::TyperWidget::speedCalculated(int speed)
{
    m_speedLabel->setText(QString("%1 WPM").arg(speed));
    repaint();
}

void typer::gui::TyperWidget::buildForm(const QString &wordType)
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

    /// min widht - width of parent widget with offset
    int minWidth = window() ? ( window()->width() - 150 ) : 600;
    textEdit->setFixedWidth(minWidth);
    textEdit->setMaximumHeight(80);

    auto font = textEdit->font();
    font.setPointSize(18);
    textEdit->setFont(font);

    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Base, QColor(255, 255, 255, 0));
    textEdit->setPalette(palette);

    QString textToType = typer::common::requestWords(wordType)
                         .unwrapOr(QString("error"));

    textEdit->setTextColor(Qt::gray);
    textEdit->setTextColor(Qt::black);
    textEdit->setAutoFillBackground(false);
    textEdit->setStyleSheet("border:0;");

    QStringList wordsToType = textToType.split(' ');
    std::random_shuffle(wordsToType.begin(), wordsToType.end());
    m_textRenderer = new TextEditRenderer(wordsToType, textEdit, this);
    m_textRenderer->setIncorrectWordColor(Qt::red);
    m_textRenderer->setCorrectWordColor(Qt::darkCyan);
    connect(m_textRenderer, &TextEditRenderer::speedCaclulated,
            this, &TyperWidget::speedCalculated);

    labelLayout->addWidget( textEdit );

    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    mainLayout->addLayout( labelLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    setLayout( mainLayout );

    m_speedLabel = new QLabel(this);

    QPalette speedLablePallete;
    speedLablePallete.setColor(QPalette::WindowText, Qt::gray);
    m_speedLabel->move(0, 0);
    font.setPointSize(24);
    m_speedLabel->setFont(font);
    m_speedLabel->setPalette(speedLablePallete);

    m_speedLabel->setText("  0 WPM");
    m_speedLabel->adjustSize();
}
