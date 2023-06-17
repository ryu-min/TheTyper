#ifndef TYPERESULTWIDGET_H
#define TYPERESULTWIDGET_H

#include <QWidget>

namespace Ui {
    class TypeResultWidget;
}

class TypeResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TypeResultWidget(QWidget *parent = nullptr);
    ~TypeResultWidget();

signals:
    void exit();
    void repeat();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void showEvent(QShowEvent *event);

private:
    void fillWPMChart();
    void fillAccuracyChart();
    void configuringQuestionButton();

private:
    Ui::TypeResultWidget *ui;
};

#endif // TYPERESULTWIDGET_H
