#include "TypeResultWidget.h"
#include "ui_TypeResultWidget.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

TypeResultWidget::TypeResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TypeResultWidget)
{
    ui->setupUi(this);
    QFont font = ui->resultLabel->font();
    font.setPointSize(18);
    setFont(font);

    QPalette p = ui->resultLabel->palette();
    p.setColor( QPalette::WindowText, Qt::gray );
    setPalette(p);

    ui->resultLabel->setText("Your result is: \n"
                             "Speed: 80 WPM \n"
                             "Accuracy: 90%");
    fillWPMChart();
    fillAccuracyChart();
    configuringQuestionButton();
    setFocusPolicy(Qt::StrongFocus);

}

TypeResultWidget::~TypeResultWidget()
{
    delete ui;
}

void TypeResultWidget::keyPressEvent(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_Escape )
    {
        emit exit();
    }
    else if ( event->key() == Qt::Key_Space && (event->modifiers() & Qt::ControlModifier) )
    {
        emit repeat();
    }
    QWidget::keyPressEvent(event);
}

void TypeResultWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    setFocus();
}

void TypeResultWidget::fillWPMChart()
{
    QChart *chart = new QChart();
    QChartView * view = ui->wmpPlot;
    view->setChart(chart);
    QLineSeries *series = new QLineSeries();
    series->append(0, 40);
    series->append(1, 50);
    series->append(2, 54);
    series->append(3, 60);
    series->append(4, 44);
    series->setColor(Qt::blue);
    series->setPointLabelsVisible(false);
    chart->addSeries(series);


    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    view->setRenderHint(QPainter::Antialiasing);
    chart->setTitle("WMP");
    chart->legend()->hide();
}

void TypeResultWidget::fillAccuracyChart()
{
    QChart *chart = new QChart();
    QChartView * view = ui->accuracyPlot;
    view->setChart(chart);
    QLineSeries *series = new QLineSeries();
    series->append(0, 40);
    series->append(1, 50);
    series->append(2, 54);
    series->append(3, 60);
    series->append(4, 44);
    series->setColor(Qt::red);
    series->setPointLabelsVisible(false);
    chart->addSeries(series);


    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    view->setRenderHint(QPainter::Antialiasing);
    chart->setTitle("Accuracy");
    chart->legend()->hide();
}

void TypeResultWidget::configuringQuestionButton()
{
    ui->questionButton->setIcon(QIcon("://icons/question-mark-24.png"));
    ui->questionButton->setStyleSheet("QPushButton { border-radius: 1px; }");
}


