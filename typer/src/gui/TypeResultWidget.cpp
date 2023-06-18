#include "TypeResultWidget.h"
#include "ui_TypeResultWidget.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

TypeResultWidget::TypeResultWidget(const typer::common::TypeResults &results, QWidget *parent) :
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


    fillWPMChart(results);
    fillAccuracyChart(results);
    configuringQuestionButton();
    setTypeResult(results);

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

void TypeResultWidget::fillWPMChart(const typer::common::TypeResults &results)
{
    QChart *chart = new QChart();
    QChartView * view = ui->wmpPlot;
    view->setChart(chart);
    QLineSeries *series = new QLineSeries();
    for ( int i = 0; i < results.size(); i++ )
    {
        series->append(i * 2, results[i].wpmSpeed);
    }
    series->setColor(Qt::blue);
    series->setPointLabelsVisible(false);
    chart->addSeries(series);


    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%is");
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

void TypeResultWidget::fillAccuracyChart(const typer::common::TypeResults &results)
{
    QChart *chart = new QChart();
    QChartView * view = ui->accuracyPlot;
    view->setChart(chart);
    QLineSeries *series = new QLineSeries();    
    for ( int i = 0; i < results.size(); i++ )
    {
        series->append(i * 2, results[i].accuracy);
    }

    series->setColor(Qt::red);
    series->setPointLabelsVisible(false);
    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis();
    axisX->setLabelFormat("%is");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    view->setRenderHint(QPainter::Antialiasing);
    chart->setTitle("Accuracy");
    chart->legend()->hide();
}

void TypeResultWidget::setTypeResult(const typer::common::TypeResults &results)
{
    typer::common::TypeResult result = results.size()
                                       ? results.last()
                                       : typer::common::TypeResult{0, 0};

    ui->resultLabel->setText(QString("Your result is: \n"
                                     "Speed: %1 WPM \n"
                                     "Accuracy: %2%")
                             .arg(result.wpmSpeed)
                             .arg(result.accuracy) );
}

void TypeResultWidget::configuringQuestionButton()
{
    ui->questionButton->setIcon(QIcon("://icons/question-mark-24.png"));
    ui->questionButton->setStyleSheet("QPushButton { border-radius: 1px; }");
}


