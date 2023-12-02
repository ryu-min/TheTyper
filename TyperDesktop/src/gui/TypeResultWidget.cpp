#include "TypeResultWidget.h"
#include "ui_TypeResultWidget.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

#include "../common/Constants.h"

typer::gui::TypeResultWidget::TypeResultWidget(const typer::common::TypeResults &results, QWidget *parent) :
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

typer::gui::TypeResultWidget::~TypeResultWidget()
{
    delete ui;
}

void typer::gui::TypeResultWidget::keyPressEvent(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_Escape )
    {
        emit exit();
    }
    else if ( event->key() == Qt::Key_Space)
    {
        emit repeat();
    }
    QWidget::keyPressEvent(event);
}

void typer::gui::TypeResultWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    setFocus();
}

void typer::gui::TypeResultWidget::fillWPMChart(const typer::common::TypeResults &results)
{
    QChart *chart = new QChart();
    QChartView * view = ui->wmpPlot;
    view->setChart(chart);
    QLineSeries *series = new QLineSeries();
    for ( int i = 0; i < results.size(); i++ )
    {
        series->append(i * typer::common::CALC_SPEED_TIMEOUT_S,
                       results[i].wpmSpeed);
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

void typer::gui::TypeResultWidget::fillAccuracyChart(const typer::common::TypeResults &results)
{
    QChart *chart = new QChart();
    QChartView * view = ui->accuracyPlot;
    view->setChart(chart);
    QLineSeries *series = new QLineSeries();    
    for ( int i = 0; i < results.size(); i++ )
    {
        series->append(i * typer::common::CALC_SPEED_TIMEOUT_S,
                       results[i].accuracy);
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

void typer::gui::TypeResultWidget::setTypeResult(const typer::common::TypeResults &results)
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

void typer::gui::TypeResultWidget::configuringQuestionButton()
{
    ui->questionButton->setIcon(QIcon("://icons/question-mark-24.png"));
    ui->questionButton->setStyleSheet("QPushButton { border-radius: 1px; }");
}


