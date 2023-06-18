#pragma once

#include <QWidget>

#include "../common/TypeResult.h"

namespace Ui {
    class TypeResultWidget;
}


namespace typer
{
    namespace gui
    {
        class TypeResultWidget : public QWidget
        {
            Q_OBJECT

        public:
            explicit TypeResultWidget(const typer::common::TypeResults & results,
                                      QWidget *parent = nullptr);
            ~TypeResultWidget();

        signals:
            void exit();
            void repeat();

        protected:
            void keyPressEvent(QKeyEvent *event) override;
            void showEvent(QShowEvent *event);

        private:
            void fillWPMChart(const typer::common::TypeResults & results);
            void fillAccuracyChart(const typer::common::TypeResults & results);
            void setTypeResult(const typer::common::TypeResults &results);
            void configuringQuestionButton();

        private:
            Ui::TypeResultWidget *ui;
        };
    }
}

