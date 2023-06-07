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
{
    buildForm(wordTypes);
    setFocusPolicy(Qt::StrongFocus);
}

void typer::gui::EnterMenu::keyReleaseEvent(QKeyEvent *event)
{
    QWidget::keyReleaseEvent(event);
    if ( (event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return) )
    {
        emitStart();
    }
}

void typer::gui::EnterMenu::resizeEvent(QResizeEvent *event)
{
    int widgetWidth = size().width();
    int cbWidth     = m_wordTypeComboBox->size().width();
    m_wordTypeComboBox->move(widgetWidth - cbWidth - 20, 20);
    QWidget::resizeEvent(event);
}

void typer::gui::EnterMenu::showEvent(QShowEvent *event)
{
    setFocus();
    QWidget::showEvent(event);
}

void typer::gui::EnterMenu::emitStart()
{
     emit start(m_wordTypeComboBox->currentText());
}

void typer::gui::EnterMenu::buildForm(const QStringList &wordTypes)
{
    QVBoxLayout * buttonLayout = new QVBoxLayout();
    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 50;

    QPushButton * startButton = new QPushButton("Press enter to start", this);
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

    QPushButton * settingsButton = new QPushButton(this);
    settingsButton->setGeometry(20, 20, 40, 40);
    settingsButton->setIcon(QIcon(":/icons/settings.png"));
    settingsButton->setIconSize(QSize(40, 40));
    settingsButton->setToolTip("Go to settings");
    settingsButton->setStyleSheet("QPushButton { border: 0px; }");

    connect( settingsButton, &QPushButton::clicked, this, &EnterMenu::settings);


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
}
