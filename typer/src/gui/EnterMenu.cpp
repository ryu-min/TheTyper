#include "EnterMenu.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QKeyEvent>
#include <QAbstractItemView>

typer::gui::EnterMenu::EnterMenu(const QStringList & wordTypes,
                                 QWidget *parent)
    : QWidget( parent )
    , m_wordTypeComboBox(new QComboBox(this))
    , m_timeComboBox( new QComboBox(this) )
{
    buildForm(wordTypes);
    setFocusPolicy(Qt::StrongFocus);
}

void typer::gui::EnterMenu::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);
    bool enterPressed = (    (event->key() == Qt::Key_Enter)
                          || (event->key() == Qt::Key_Return) );
    bool ctrlPressed = ( event->modifiers() & Qt::ControlModifier );

    if ( enterPressed && ctrlPressed )
    {
        emitStart();
    }
}

void typer::gui::EnterMenu::resizeEvent(QResizeEvent *event)
{
    updateComboBoxesPos();
    QWidget::resizeEvent(event);
}

void typer::gui::EnterMenu::showEvent(QShowEvent *event)
{
    setFocus();
    updateComboBoxesPos();
    QWidget::showEvent(event);
}

void typer::gui::EnterMenu::emitStart()
{
    QStringList splitedTime = m_timeComboBox->currentText().split(' ');
    Q_ASSERT(splitedTime.size());
    int time = splitedTime.size() ? splitedTime[0].toInt() : 60;
    emit start(m_wordTypeComboBox->currentText(), time );
}

void typer::gui::EnterMenu::buildForm(const QStringList &wordTypes)
{
    QVBoxLayout * buttonLayout = new QVBoxLayout();
    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 50;

    QPushButton * startButton = new QPushButton("Ctrl + Enter to start", this);
    startButton->setStyleSheet("QPushButton {background-color: rgba(255, 255, 255, 0); color: gray;}");

    startButton->setFixedWidth( BUTTON_WIDTH );
    startButton->setFixedHeight( BUTTON_HEIGHT );
    connect( startButton, &QPushButton::clicked, this, &EnterMenu::emitStart);

    QPalette startButtonPallete = startButton->palette();
    startButtonPallete.setColor(QPalette::WindowText, Qt::gray);
    startButton->setPalette(startButtonPallete);

    QFont font = startButton->font();
    font.setPointSize(18);
    startButton->setFont(font);

    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    buttonLayout->addWidget( startButton );
    buttonLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );
    mainLayout->addLayout( buttonLayout );
    mainLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding) );

    setLayout( mainLayout );

    font.setPointSize(14);
    m_wordTypeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    m_wordTypeComboBox->setFont(font);
    m_wordTypeComboBox->setPalette(startButtonPallete);
    m_wordTypeComboBox->move(0, 0);
    m_wordTypeComboBox->addItems(wordTypes);

    m_timeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    m_timeComboBox->setFont(font);
    m_timeComboBox->setPalette(startButtonPallete);
    //m_timeComboBox->move(0, 0);
    const QStringList times = QStringList()
                              << "15 s"
                              << "30 s"
                              << "60 s"
                              << "120 s";
    m_timeComboBox->addItems(times);

    m_timeComboBox->setStyleSheet("QComboBox { background-color: transparent; color: gray;}");

    m_timeComboBox->view()->setStyleSheet("QComboBox QAbstractItemView { background-color: transparent;  color: white; } "
                                          " QComboBox QAbstractItemView::item:selected { background-color: rgb(40, 40, 40); }"
                                          " QComboBox QAbstractItemView::item {background-color: gray; } ");

    m_wordTypeComboBox->setStyleSheet("QComboBox { background-color: transparent; color: gray;}");
    m_wordTypeComboBox->view()->setStyleSheet("QComboBox QAbstractItemView { background-color: transparent;  color: white; } "
                                          " QComboBox QAbstractItemView::item:selected { background-color: rgb(40, 40, 40); }"
                                          " QComboBox QAbstractItemView::item {background-color: gray; }");


    connect(m_timeComboBox, &QComboBox::currentTextChanged, m_timeComboBox, [startButton]() {
        startButton->setFocus();
    });

    connect(m_wordTypeComboBox, &QComboBox::currentTextChanged, m_timeComboBox, [startButton]() {
        startButton->setFocus();
    });
    m_wordTypeComboBox->adjustSize();

    updateComboBoxesPos();
}

void typer::gui::EnterMenu::updateComboBoxesPos()
{
    int widgetWidth = size().width();
    int cbWidth     = m_timeComboBox->sizeHint().width();
    m_timeComboBox->move(widgetWidth - cbWidth - 10, 10);
    m_wordTypeComboBox->move(QPoint(10, 10));
}
