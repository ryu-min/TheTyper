#include "TypingFinishWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>

typer::gui::TypingFinishWidget::TypingFinishWidget(int result,
                                                   QWidget *parent)
    : QWidget(parent)
{
    buildForm(result);
    setFocusPolicy(Qt::StrongFocus);
}

void typer::gui::TypingFinishWidget::keyPressEvent(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_Escape )
    {
        emit exit();
    }
    else if ( event->key() == Qt::Key_Space )
    {
        emit repeat();
    }
    QWidget::keyPressEvent(event);
}

void typer::gui::TypingFinishWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    setFocus();
}

void typer::gui::TypingFinishWidget::buildForm(int result)
{
    QHBoxLayout * mainLayout = new QHBoxLayout();
    QVBoxLayout * vLayout = new QVBoxLayout;
    QLabel * resultLabel = new QLabel(QString("Your result is %1").arg(result));
    resultLabel->setStyleSheet("font-size: 18px; color: gray;");
    vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    vLayout->addWidget(resultLabel, 0, Qt::AlignCenter);
    vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(vLayout);
    setLayout(mainLayout);
}
