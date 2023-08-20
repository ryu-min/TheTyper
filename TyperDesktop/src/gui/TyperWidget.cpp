#include "TyperWidget.h"
#include "../common/Network.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QPlainTextEdit>
#include <QTextEdit>
#include <QToolTip>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

typer::gui::TyperWidget::TyperWidget(const QString &wordType, int sTime,
                                     QWidget *parent)
    : QWidget( parent )
{
    buildForm(wordType, sTime);
}

void typer::gui::TyperWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QSizeF wSize = size();
    QSizeF sSize = m_speedLabel->size();
    m_speedLabel->move( wSize.width() / 2 - sSize.width() / 2,
                        wSize.height()/2 - 80);
}

void typer::gui::TyperWidget::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    if ( event->key() == Qt::Key_Escape )
    {
        emit exit();
    }
}

void typer::gui::TyperWidget::typeResultCalculated(const common::TypeResult &typeResult)
{
    m_speedLabel->setText(QString("%1 WPM").arg(typeResult.wpmSpeed));
    m_typeResults.push_back(typeResult);
    repaint();
}

void typer::gui::TyperWidget::buildForm(const QString &wordType, int sTime)
{
    QLabel * exitLabel = new QLabel(this);

    auto labelFont = exitLabel->font();
    labelFont.setPointSize(14);
    exitLabel->setFont(labelFont);

    auto labelPalette = exitLabel->palette();
    labelPalette.setColor( QPalette::WindowText, Qt::gray );
    exitLabel->setPalette(labelPalette);

    exitLabel->setText("ESC to exit");
    exitLabel->move(20, 20);
    exitLabel->adjustSize();

    QTimer::singleShot(3000, this, [exitLabel]()
    {
        exitLabel->deleteLater();
    });


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
    m_textRenderer = new TextEditRenderer(wordsToType, textEdit, sTime, this);
    m_textRenderer->setIncorrectWordColor(Qt::red);
    m_textRenderer->setCorrectWordColor(Qt::darkCyan);
    connect(m_textRenderer, &TextEditRenderer:: typeResultCalculated,
            this, &TyperWidget::typeResultCalculated);
    connect(m_textRenderer, &TextEditRenderer::finish, this,
            [this](const common::TypeResult & result ){
        m_typeResults.push_back(result);
        emit finish(m_typeResults);
    });

    labelLayout->addWidget( textEdit );

    labelLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    mainLayout->addLayout( labelLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Maximum) );

    setLayout( mainLayout );

    m_speedLabel = new QLabel(this);

    QPalette speedLablePallete;
    speedLablePallete.setColor( QPalette::WindowText, Qt::gray );

    m_speedLabel->move(0, 0);
    font.setPointSize(24);
    m_speedLabel->setFont(font);
    m_speedLabel->setPalette(speedLablePallete);

    m_speedLabel->setText("  0 WPM");
    m_speedLabel->adjustSize();
}
